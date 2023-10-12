# Traffic counter Raspberry Pi 4
![output image]( https://qengineering.eu/images/TrafficRpi64.webp )
## Traffic counter with a camera on a bare Raspberry Pi 4. <br/>
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)<br/><br/>
Specially made for a Raspberry Pi 4, see [Q-engineering deep learning examples](https://qengineering.eu/deep-learning-examples-on-raspberry-32-64-os.html)<br>
See [YouTube movie](https://youtu.be/kLo0sFx-sVA).<br>

------------

## Dependencies.
To run the application, you have to:
- A Raspberry Pi 4 with a 64-bit _**Bullseye**_ operating system. <br/>
- Raspbian's libcamera-apps source code installed (```$ sudo apt install libcamera-dev```)
- The Tencent ncnn framework installed. [Install ncnn](https://qengineering.eu/install-ncnn-on-raspberry-pi-4.html) <br/>
- OpenCV 64-bit installed. [Install OpenCV 4.5](https://qengineering.eu/install-opencv-4.5-on-raspberry-64-os.html) <br/>
- Code::Blocks installed. (```$ sudo apt-get install codeblocks```)

------------

## Installing the app.
To extract and run the network in Code::Blocks <br/>
$ mkdir *MyDir* <br/>
$ cd *MyDir* <br/>
$ wget https://github.com/Qengineering/Traffic-Counter-RPi_64-bit/archive/refs/heads/main.zip <br/>
$ unzip -j main.zip <br/>
Your *MyDir* folder must now look like this: <br/> 
```
.
├── include
│   ├── BYTETracker.h
│   ├── dataType.h
│   ├── kalmanFilter.h
│   ├── lapjv.h
│   ├── lccv.hpp
│   ├── libcamera_app.hpp
│   ├── libcamera_app_options.hpp
│   └── STrack.h
├── LICENSE
├── nanodet_m.bin
├── nanodet_m.param
├── README.md
├── src
│   ├── BYTETracker.cpp
│   ├── kalmanFilter.cpp
│   ├── lapjv.cpp
│   ├── lccv.cpp
│   ├── libcamera_app.cpp
│   ├── libcamera_app_options.cpp
│   ├── STrack.cpp
│   ├── traffictrack.cpp
│   └── utils.cpp
├── Traffic.mp4
└── TrafficTracking.cbp
```

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


