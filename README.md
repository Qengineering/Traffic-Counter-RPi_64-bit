# Traffic counter Raspberry Pi 4
![Screenshot from 2024-11-12 12-45-17](https://github.com/user-attachments/assets/6a88bdd7-6e89-46fd-9f07-ff63798783dc)
## Traffic counter with a camera on a bare Raspberry Pi 4. <br/>
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)<br/><br/>
Specially made for a Raspberry Pi 4, see [Q-engineering deep learning examples](https://qengineering.eu/deep-learning-examples-on-raspberry-32-64-os.html)<br>

------------

## Introduction.
A fully functional traffic counter with a camera working on a bare Raspberry Pi 4.
Highlights:
- Stand alone.
- Lane selection.
- MQTT messages.
- JSON messages.
- Live web viewer.
- JSON settings.
- RTSP CCTV streaming.
- Debug screens.

------------

https://github.com/user-attachments/assets/a64cc957-4965-4afb-9077-b37b1071c08a

------------

## Dependencies.
To run the application, you have to:
- A Raspberry Pi 4 with a 64-bit _**Bullseye**_ operating system. <br/>
- The Tencent ncnn framework installed. [Install ncnn](https://qengineering.eu/install-ncnn-on-raspberry-pi-4.html) <br/>
- Optional: Code::Blocks installed. (```$ sudo apt-get install codeblocks```)

### Installing the dependencies.
Start with the usual 
```
$ sudo apt-get update 
$ sudo apt-get upgrade
$ sudo apt-get install curl libcurl4
$ sudo apt-get install cmake wget
```
#### Libcamera
```
$ sudo apt-get install libcamera-dev
```
#### OpenCV
Follow the Raspberry Pi 4 [guide](https://qengineering.eu/install-opencv-on-raspberry-64-os.html). Or:
```
$ sudo apt-get install libopencv-dev
```
#### gflags
```
$ sudo apt-get install libgflags-dev
```
#### JSON for C++
written by [Niels Lohmann](https://github.com/nlohmann).
```
$ cd ~
$ git clone --depth=1 https://github.com/nlohmann/json.git
$ cd json
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
$ sudo make install
$ sudo ldconfig
```
#### paho.mqtt (MQTT client)
```
$ cd ~
$ git clone --depth=1 https://github.com/eclipse/paho.mqtt.c.git
$ cd paho.mqtt.c
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
$ sudo make install
$ sudo ldconfig
```
#### Mosquitto (MQTT broker)
```
$ sudo apt-get install mosquitto
```

------------

## Installing the app.
Download the software.<br/>
```
$ git clone https://github.com/Qengineering/Traffic-Counter-RPi_64-bit.git
```
Your folder must now look like this: <br/> 
```
.
├── CMakeLists.txt
├── config.json
├── include
│   ├── BYTETracker.h
│   ├── dataType.h
│   ├── General.h
│   ├── kalmanFilter.h
│   ├── lapjv.h
│   ├── lccv.hpp
│   ├── libcamera_app.hpp
│   ├── libcamera_app_options.hpp
│   ├── MJPG_sender.h
│   ├── MJPGthread.h
│   ├── MQTT.h
│   ├── Numbers.h
│   ├── STrack.h
│   ├── Tjson.h
│   ├── TChannel.h
│   └── yolo-fastestv2.h
├── LICENSE
├── models
│   ├── yolo-fastestv2-opt.bin
│   └── yolo-fastestv2-opt.param
├── README.md
├── src
│   ├── BYTETracker.cpp
│   ├── kalmanFilter.cpp
│   ├── lapjv.cpp
│   ├── lccv.cpp
│   ├── libcamera_app.cpp
│   ├── libcamera_app_options.cpp
│   ├── main.cpp
│   ├── MJPG_sender.cpp
│   ├── MJPGthread.cpp
│   ├── MQTT.cpp
│   ├── STrack.cpp
│   ├── Tjson.cpp
│   ├── TChannel.cpp
│   ├── utils.cpp
│   └── yolo-fastestv2.cpp
├── Traffic.cbp
└── Traffic.mp4

3 directories, 39 files
```
------------

## Running the app.
You can use **Code::Blocks**.
- Load the project file *.cbp in Code::Blocks.
- Select _Release_, not Debug.
- Compile and run with F9.
- You can alter command line arguments with _Project -> Set programs arguments..._ 

Or use **Cmake**.
```
$ cd *MyDir*
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
```
------------

## Settings.
All important settings are stored in the `config.json`<br>
You can alter these to your liking. Please note the use of commas after each line, except the last one.<br>
```json
{
    "VERSION": "1.0.0.0",

    "MQTT_ON": true,
    "MQTT_SERVER_example": "broker.hivemq.com:1883",
    "MQTT_SERVER": "localhost:1883",
    "MQTT_CLIENT_ID": "Arrow",
    "MQTT_TOPIC": "traffic",
    "DEVICE_NAME": "highway 12",
    "ANNOTATE": true,

    "STREAM_example1": "rtsp://admin:L231C865@192.168.178.41:554/stream1",
    "STREAM_example2": "RaspiCam",
    "STREAM": "Traffic.mp4",

    "BORDER_X1": 10,
    "BORDER_Y1": 300,
    "BORDER_X2": 450,
    "BORDER_Y2": 300,

    "JSON_PORT": 8070,
    "MJPEG_PORT": 8090,
    "MJPEG_WIDTH": 640,
    "MJPEG_HEIGHT": 480,

    "MESSAGE_TIME": 2,

    "PARAM_MODEL": "./models/yolo-fastestv2-opt.param",
    "BIN_MODEL": "./models/yolo-fastestv2-opt.bin"
}
```

| Global parameter | Comment |
| ----      | ---- |
| VERSION   | Current version. |
| MQTT_ON | Enable MQTT messages. 'true-false'. |
| MQTT_SERVER | MQTT server. Default `localhost:1883` |
| MQTT_CLIENT_ID | MQTT client ID. Default `Arrow` |
| MQTT_TOPIC | MQTT topic. Default `traffic` |
| DEVICE_NAME | Name of the camera, used in the MQTT messages. |
| ANNOTATE | Show lines, boxes and numbers in live view. Default `true` |


| STREAMS_NR | Number of used streams.<br>It can be images, folders, videos or (RTSP) streams, like CCTV cameras. |
| STREAM_x | Define stream x. |
| CAM_NAME | Name of the stream, used in messages. |
| MJPEG_PORT | The current stream with the bounding boxes and the OCR outcome is shown at the set port number. |
| MQTT_TOPIC | MQTT topic name. |
| VIDEO_INPUT | Used input. In the example, you can give `video` or `IMOU`, as they are defined in the array. |
| VIDEO_INPUTS_PARAMS | Array of input streams.<br>- If you give the keyword `image` ALPR will process only one picture.<br>- With the keyword `folder`, it will process all pictures (*.jpg, *.png, *.bmp) found in the specified folder.<br>- The keyword `pipe` will open the specified GStreamer pipeline.<br>- The keyword `pipe_hw` will open the specified GStreamer pipeline with hardware acceleration.<br>- The keyword `video` will open the specified video.<br>- If not one of these three predefined keywords, the software assumes a stream, like `IMOU` or `VIGI`.
| `image` | Define the `image` location. |
| `images` | Define the folder location where images are found. |
| `video` | Define the `video` stream. |
| `pipe` | Define the `pipeline` stream. |
| `pipe_hw` | Define the `pipeline` with hardware acceleration stream.<br>It will **automatically selected** on the **Jetson** when the input is an mp4 video. Note, pause/continue will not work.|
| `mp4` | Define the `video` stream and force the Jetson to use FFmpeg, pause/continue will work. |
| `IMOU` | Define the `IMOU` stream. |
| SYNC | `true` The video is played in time.<br>`false` The video is played as fast as possible.<br>The parameter is only used with the video input.|
| CFS | Define the **C**aptured **F**rames per **S**econd.<br>The parameter is used for all input, except streams. |
| LOOP |`true` The pictures or video are replayed when reaching the end.<br>`false` The sequence stops with the last image when finished. |
| WORK_WIDTH | Width of the images |
| WORK_HEIGHT | Height of the images.<br>**All** streams are resized to `WORK_WIDTH x WORK_HEIGHT` before being processed further. Smaller frames require less resources. Please don't make them too small, the characters of the license plate still need to be recognized. |
| THUMB_WIDTH | Width to the individual thumbnail picture. |
| THUMB_HEIGHT | Height to the individual thumbnail picture. |
| JSON_PORT | The JSON message port number. In contrast to the MQTT messages containing only portal events, the JSON message describes the frame contents. |
| MJPEG_PORT | The thumbnail overview with the bounding boxes and the OCR outcome is shown at the given port number. |
| MJPEG_WIDTH | Thumbnail width |
| MJPEG_HEIGHT | Thumbnail height |
| PRINT_ON_CLI | Print the Yolo outcome to the terminal `true-false`. |
| PRINT_ON_RENDER | Show the thumbnails on the screen `true-false`. |
| PRINT_PLATE | Show the little license plate thumbnails on the bottom of the screen `true-false`. |
| VEHICLE_MODEL | Location of the used Darknet model to detect the objects. |
| LICENSE_MODEL | Location of the used Darknet license plate detection model. |
| OCR_MODEL | Location of the used Darknet character recognition model. |
| NR_CHARS_PLATE | Expected number of characters on a licence plate. |
| PLATE_RATIO | Plate width/height ratio. To prevent too square plates are investigated. |
| FoI_FOLDER | The location where the individual images are stored. Because every single frame is stored, it generates a **_massive_** bulk of data. `none` switches the storage off. |
| VEHICLES_FOLDER | The location where the individual vehicles are stored. Because every vehicle is stored, it generates a **lot** of data. `none` disables the storage. |
| PLATES_FOLDER  | The location where the individual license plate images are stored. `none` blocks the storage. |
| PLATE_TEMPLATE | Templating the license plate. See the Wiki page [Templating](https://github.com/xactai/SCALPR-01.5/wiki/Templating). |
| JSONS_FOLDER | The location where the JSON outcomes are stored. `none` prevents the storage. |
| RENDERS_FOLDER | The location where the thumbnail overviews are stored. Like the FoI, it stores every frame, generating **_massive_** data. Give `none` if you don't want to use it.|
| THRESHOLD_VERHICLE | Darknet recognition level of the vehicles. |
| THRESHOLD_PLATE | Darknet recognition level of the license plates. |
| THRESHOLD_OCR | Darknet recognition level of the OCR |

To run the application load the project file TrafficTracking.cbp in Code::Blocks.<br>
We [overclocked](https://qengineering.eu/overclocking-the-raspberry-pi-4.html) our Raspberry Pi 4 to 1950MHz to get the highest FPS.<br>
As usual, ensure good cooling!<br>

------------

## Camera.
If you want to run the app with a camera you have to uncomment line 18 in `traffictrack.cpp` and recompile the software.
```
#define CAMERA
```
We use the Bullseye [LCCV camera](https://github.com/Qengineering/LCCV) code because it is a feather-light camera code leaving most of the computer time for deep learning calculations.

------------

## Final remark.
It's a lot of room for improvement. The current NanoDet model has been trained with the COCO set. In everyday use, you don't need all 80 classes when monitoring traffic. Only a few classes could do that. It makes the model faster and more accurate.<br>
Another improvement could be the tracker. Here we use the [Byte Tracking](https://github.com/Qengineering/NanoDet-Tracking-ncnn-RPi_64-bit).
Because only traffic moves to or from the camera, tracking can be simplified. And on the other hand, be more robust. As you will experience, traffic towards the camera is harder to detect than traffic driving away.<br>

------------

[![paypal](https://qengineering.eu/images/TipJarSmall4.png)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=CPZTM5BB3FCYL) 


