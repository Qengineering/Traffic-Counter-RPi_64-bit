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
```shell
$ sudo apt-get update 
$ sudo apt-get upgrade
$ sudo apt-get install curl libcurl4
$ sudo apt-get install cmake wget
```
#### Libcamera
```shell
$ sudo apt-get install libcamera-dev
```
#### OpenCV
Follow the Raspberry Pi 4 [guide](https://qengineering.eu/install-opencv-on-raspberry-64-os.html). Or:
```shell
$ sudo apt-get install libopencv-dev
```
#### Eigen3
```shell
$ sudo apt-get install libeigen3-dev
```
#### gflags
```shell
$ sudo apt-get install libgflags-dev
```
#### JSON for C++
written by [Niels Lohmann](https://github.com/nlohmann).
```shell
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
```shell
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
```shell
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
```shell
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
You can use debug mode to find the optimal position for the borderline.<br> 
To enable debug mode, start the app with the --debug flag set to true:<br>
```shell
./Traffic --debug=true
```
Alternatively, you can modify the command line argument in Code::Blocks by navigating to Project -> Set programs arguments...<br> 
In debug mode, you’ll see the tail of each vehicle. When a vehicle’s tail crosses the imaginary borderline, it is added to the count.<br> 
At this point, the bounding box is highlighted, which helps in identifying any missed vehicles.<br><br>

https://github.com/user-attachments/assets/4b67bebb-af1f-4edd-9ba6-c8217ecdcf56

------------

## MQTT messages.
You can receive MQTT messages locally at localhost:1883, the default setting. Messages are printed to the terminal.<br> 
When connected to the internet, you can send MQTT messages to any broker you choose, such as broker.hivemq.com:1883.<br> 
The app only sends messages when the MQTT_ON setting is set to true. The refresh rate, in seconds, is determined by MESSAGE_TIME.<br> 
At midnight, all cumulative counts are reset.<br><br> 
You can also follow the messages in a web browser. To do so, enter the port number after the IP address of your Raspberry Pi.<br><br>
![2024-11-11 15_22_51-192 168 178 87_8070 - Brave](https://github.com/user-attachments/assets/36d9ffcc-c66d-4da2-adaa-cbd45d19b6d6)

------------

## Preview.
If your Raspberry Pi is connected to the internet, you can view live footage in a browser.<br>
Simply combine the Raspberry Pi’s IP address with the MJPEG_PORT number specified in the settings to access the camera feed.<br><br>
![2024-11-11 15_21_32-192 168 178 87_8090 - Brave](https://github.com/user-attachments/assets/567fed46-b240-4450-b3d2-f5a07471f88d)

------------

## LCCV.
We use the Bullseye [LCCV camera](https://github.com/Qengineering/LCCV) code, which is a lightweight camera solution that leaves most computing resources available for deep learning tasks.<br> If you prefer to use GStreamer, you can build the application with the CAMERA flag set to OFF:
```shell
$ cd *MyDir*
$ mkdir build
$ cd build
$ cmake -DCAMERA=OFF ..
$ make -j4
```

------------

## Final remark.
There is plenty of room for improvement. The most obvious upgrade would be adding more computing power. The network used is very lightweight. We’ve also published this application for the Rock 5C, an affordable ($60) device with an NPU. With this setup, you’ll immediately see the impact of using a more powerful DNN model.

------------

[![paypal](https://qengineering.eu/images/TipJarSmall4.png)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=CPZTM5BB3FCYL) 


