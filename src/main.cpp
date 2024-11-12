// 10-01-2024 Q-engineering

//uncomment if you want to use the LCCV camera
//#define CAMERA

#include "net.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <gflags/gflags.h>
#include <stdlib.h>
#include <float.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "BYTETracker.h"
#include "yolo-fastestv2.h"
#include "Tjson.h"
#include "MQTT.h"
#include "MJPGthread.h"
#include "TMapper.h"
#include <lccv.hpp>
#include <chrono>
#include <thread>

//----------------------------------------------------------------------------------------
// Define the command line flags
//----------------------------------------------------------------------------------------

DEFINE_bool(debug, false, "shows debug output");

//----------------------------------------------------------------------------------
yoloFastestv2 yoloF2;
Tjson         Js;
BYTETracker   Btrack;
size_t        FrameCnt=0;
size_t        FPS;
//----------------------------------------------------------------------------------
const char* class_names[] = {
    "background", "person", "bicycle",
    "car", "motorbike", "aeroplane", "bus", "train", "truck",
    "boat", "traffic light", "fire hydrant", "stop sign",
    "parking meter", "bench", "bird", "cat", "dog", "horse",
    "sheep", "cow", "elephant", "bear", "zebra", "giraffe",
    "backpack", "umbrella", "handbag", "tie", "suitcase",
    "frisbee", "skis", "snowboard", "sports ball", "kite",
    "baseball bat", "baseball glove", "skateboard", "surfboard",
    "tennis racket", "bottle", "wine glass", "cup", "fork",
    "knife", "spoon", "bowl", "banana", "apple", "sandwich",
    "orange", "broccoli", "carrot", "hot dog", "pizza", "donut",
    "cake", "chair", "sofa", "pottedplant", "bed", "diningtable",
    "toilet", "tvmonitor", "laptop", "mouse", "remote", "keyboard",
    "cell phone", "microwave", "oven", "toaster", "sink",
    "refrigerator", "book", "clock", "vase", "scissors",
    "teddy bear", "hair drier", "toothbrush"
};
//----------------------------------------------------------------------------------
// Message handler for the MQTT subscription for any desired control channel topic
int handleMQTTControlMessages(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("MQTT message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: %.*s\n\n", message->payloadlen, (char*)message->payload);

    return 1;
}
//----------------------------------------------------------------------------------
void DrawFrame(cv::Mat &frame,const TMapper &Map,const vector<bbox_t> &OutputTracks)
{
    if(FLAGS_debug){
        for(size_t i=0; i<Map.MapList.size(); i++){
            if(Map.MapList[i].Tframe==FrameCnt){
                Scalar s = Btrack.get_color(Map.MapList[i].Track);
                if(Map.MapList[i].Tdone){
                    rectangle(frame, Rect(Map.MapList[i].Box.l, Map.MapList[i].Box.t, Map.MapList[i].Box.r-Map.MapList[i].Box.l, Map.MapList[i].Box.b-Map.MapList[i].Box.t), s, -1);
                }
                else {
                    rectangle(frame, Rect(Map.MapList[i].Box.l, Map.MapList[i].Box.t, Map.MapList[i].Box.r-Map.MapList[i].Box.l, Map.MapList[i].Box.b-Map.MapList[i].Box.t), s, 2);
                    line(frame, Point(Map.MapList[i].Box.a, Map.MapList[i].Box.b), Point(Map.MapList[i].Box_T0.a, Map.MapList[i].Box_T0.b), cv::Scalar(0, 0, 255), 2);
                }
            }
        }
        line(frame, Point(Js.X1, Js.Y1), Point(Js.X2, Js.Y2), cv::Scalar(0, 0, 255), 2);
    }
    else{
        if(Js.Annotate){
            for(size_t i=0; i<OutputTracks.size(); i++){
                Scalar s = Btrack.get_color(OutputTracks[i].track_id);
    //                    putText(frame, format("%d", OutputTracks[i].track_id), Point(OutputTracks[i].x, OutputTracks[i].y - 5),
    //                                0, 0.6, Scalar(0, 0, 255), 2, LINE_AA);
                rectangle(frame, Rect(OutputTracks[i].x, OutputTracks[i].y, OutputTracks[i].w, OutputTracks[i].h), s, 2);
            }
            line(frame, Point(Js.X1, Js.Y1), Point(Js.X2, Js.Y2), cv::Scalar(0, 0, 255), 2);
        }
    }

    int p=0;
    for(int i=0; i<10; i++){
        if(Map.CntAr[i]>0){
            putText(frame, cv::format("%s = %i", class_names[i+1], Map.CntAr[i]),cv::Point(10,p*20+20),cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255));
            p++;
        }
    }
}
//----------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    float  fs;
    size_t FrameCnt_T1;
    size_t FPS_T1 = 15;
    int    Mcnt = 0;
    cv::Mat frame;
    MJPGthread *MJ=nullptr;
    TMapper Map;
    cv::VideoCapture cap;

    // Parse the flags
    gflags::ParseCommandLineFlags(&argc, &argv, true);

#ifdef CAMERA
    lccv::PiCamera cam;
    cam.options->video_width=640;
    cam.options->video_height=480;
    cam.options->framerate=15;
    cam.options->verbose=true;
#endif

    // Load JSON
    // Js takes care for printing errors.
    Js.LoadFromFile("./config.json");
    bool Success = Js.GetSettings();
    if(!Success){
        cout << "Error loading settings from the json file!\n\nPress <Ctrl>+<C> to quit" << endl;
        while(1) sleep(10);
        return 0;
    }
    if(Js.Version != VERSION){
        cout << "Wrong version of the json file!" << endl;
        cout << "\nSoftware version is " << VERSION << endl;
        cout << "JSON file is " << Js.Version << endl;
        cout << "\nPress <Ctrl>+<C> to quit" << endl;
        while(1) sleep(10);
        return 0;
    }
    cout << "Loaded JSON" << endl;

    //load p1 and p2 in the mapper
    Map.Init();

    //export MQTT environment
    setenv("MQTT_SERVER", Js.MQTT_Server.c_str(), 1);       // The third argument '1' specifies to overwrite if it already exists
    setenv("MQTT_CLIENT_ID", Js.MQTT_Client.c_str(), 1);

    // Connect MQTT messaging
    if(mqtt_start(handleMQTTControlMessages) != 0) {
        cout << "MQTT NOT started: have you set the ENV varables?\nPress <Ctrl>+<C> to quit" << endl;
        while(1) sleep(10);
        return 0;
    }
    mqtt_connect();
	mqtt_subscribe("traffic");

	//load MJPEG_Port
    MJ = new MJPGthread();
    if(Js.MJPEG_Port>7999){
        MJ->Init(Js.MJPEG_Port);
        cout << "Opened MJpeg port: " << Js.MJPEG_Port << endl;
    }

    yoloF2.init(false); //we have no GPU
    yoloF2.loadModel(Js.Pstr.c_str(), Js.Bstr.c_str());

#ifdef CAMERA
    if(Js.Stream == "RaspiCam"){
        cam.startVideo();
        fs = 15;
    }
    else{
        cap.open(Js.Stream);
        if (!cap.isOpened()) {
            std::cerr << "ERROR: Unable to open the stream" << std::endl;
            return 0;
        }
        fs = cap.get(CAP_PROP_FPS);
    }
#else
    if(Js.Stream == "RaspiCam"){
        cap.open(0);
    }
    else{
        cap.open(Js.Stream);
    }
    if (!cap.isOpened()) {
        std::cerr << "ERROR: Unable to open the stream" << std::endl;
        return 0;
    }
    fs = cap.get(CAP_PROP_FPS);
#endif
    std::cout << "fps : " << fs << std::endl;
    Btrack.Init(fs, 30);

    std::cout << "Start grabbing, press ESC on Live window to terminate" << std::endl;

    // Capture the start time
    auto lastRunTime = std::chrono::steady_clock::now();
    FrameCnt_T1=0;

    while (true) {
#ifdef CAMERA
        if(Js.Stream == "RaspiCam"){
            if(!cam.getVideoFrame(frame,1000)){
                std::cout<<"Timeout error"<<std::endl;
            }
        }
        else cap >> frame;
        if (frame.empty()) {
            std::cerr << "End of movie" << std::endl;
            break;
        }
#else
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "End of movie" << std::endl;
            break;
        }
#endif //CAMERA
        else{
            FrameCnt++;

            std::vector<TargetBox> objects;
            yoloF2.detection(frame, objects);

            vector<bbox_t> OutputTracks = Btrack.update(objects);

            Map.Execute(OutputTracks);

            DrawFrame(frame, Map, OutputTracks);

            // Check if 1 second has passed
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - lastRunTime).count() >= 1) {
                // get FPS
                FPS = (FrameCnt_T1<FrameCnt)? (FrameCnt-FrameCnt_T1) : FPS_T1;

                if(FLAGS_debug){
                    cout << "FPS: "<< FPS << endl;
                }

                // Update last run time
                lastRunTime = now;
                FrameCnt_T1 = FrameCnt;
                FPS_T1      = FPS;

                // Check if we must send a message
                if(++Mcnt >= Js.MesSec){
                    Map.SendMessage();
                    Mcnt = 0;
                }

                // Check if it's midnight
                auto time_t_now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
                auto localTime = *std::localtime(&time_t_now);

                if (localTime.tm_hour == 0 && localTime.tm_min == 0) {
                    // Clear the array at midnight
                    Map.ResetCntAr();
                    // Wait a minute to avoid multiple clearings within the same minute
                    std::this_thread::sleep_for(std::chrono::minutes(1));
                }
            }

            //send the overview into the world
            if(Js.MJPEG_Port>7999){
                //send the result to the socket
                cv::Mat FrameMJPEG(Js.MJPEG_Height, Js.MJPEG_Width, CV_8UC3);
                cv::resize(frame,FrameMJPEG,FrameMJPEG.size(),0,0);
                MJ->Send(FrameMJPEG);
            }

            //show output
            imshow("RPi 4 - 1,95 GHz - 2 Mb RAM", frame);
            char esc = cv::waitKey(1);
            if(esc == 27) break;
        }
    }
#ifdef CAMERA
    cam.stopVideo();
#endif // CAMERA

    std::cout << "Closing the camera" << std::endl;
    cv::destroyAllWindows();

    mqtt_disconnect();
    mqtt_close();

    // Clean up and exit
    gflags::ShutDownCommandLineFlags();

    std::cout << "Bye!" << std::endl;

    return 0;
}
