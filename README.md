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
│   ├── TMapper.h
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
│   ├── TMapper.cpp
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
Make sure you use the model fitting your system.<br><br>

More info or if you want to connect a camera to the app, follow the instructions at [Hands-On](https://qengineering.eu/deep-learning-examples-on-raspberry-32-64-os.html#HandsOn).<br/><br/>

------------


------------

## Running the app.
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


