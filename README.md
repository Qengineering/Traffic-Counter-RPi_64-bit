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
| STREAM | The used input source.<br>It can be a video or a `RaspiCam`, or an RTSP stream, like CCTV cameras. |
| BORDER_X1 | Left X position of the imaginary borderline. |
| BORDER_Y1 | Left Y position of the imaginary borderline. |
| BORDER_X2 | Right X position of the imaginary borderline. |
| BORDER_Y2 | Right Y position of the imaginary borderline. |
| JSON_PORT | The JSON message port number.|
| MJPEG_PORT | The thumbnail browser overview. |
| MJPEG_WIDTH | Thumbnail width |
| MJPEG_HEIGHT | Thumbnail height |
| MESSAGE_TIME | Define the interval between (MQTT) messages in seconds. Default 2. |
| PARAM_MODEL | Used nccn DNN model (parameters). |
| BIN_MODEL | Used nccn DNN model (weights). |

------------

![Screenshot from 2024-11-11 14-07-00](https://github.com/user-attachments/assets/492d8264-47e9-4437-abf0-f9c0a14778e2)

------------

## Debug.
You can use debug mode to determine the best position for the borderline.<br>
Start the app with the flag debug set.<br>
```
./Traffic --debug=true
```
Or alter command line argument in Code::Blocks with _Project -> Set programs arguments..._ <br>
Now you see the tails of every vehicle. Once the tail crosses the imaginary borderline, the car is added.<br>
At the same time, the bounding box is filled. A convenient way to determine the missed vehicles.<br>



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


