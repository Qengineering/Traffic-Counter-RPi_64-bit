cmake_minimum_required(VERSION 3.10)
project(Traffic)

# Enable C++17 standard and set common compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Option to define CAMERA flag
option(CAMERA "Enable camera support" OFF)
if(CAMERA)
    add_compile_definitions(CAMERA)
endif()

find_package(PkgConfig REQUIRED)

pkg_check_modules(OPENCV REQUIRED opencv4)

find_package(OpenCV REQUIRED)   
find_package(gflags REQUIRED)

# Include directories
include_directories( ${OpenCV_INCLUDE_DIRS} 
		include 
		/usr/local/include/ncnn 
		/usr/local/include/eigen3
		/usr/include/libcamera
)

# Source files
set(SRC_FILES 
		src/BYTETracker.cpp 
		src/MJPG_sender.cpp 
		src/MJPGthread.cpp 
		src/MQTT.cpp 
		src/STrack.cpp 
		src/TMapper.cpp 
		src/Tjson.cpp 
		src/kalmanFilter.cpp 
		src/lapjv.cpp 
		src/main.cpp 
		src/utils.cpp 
		src/yolo-fastestv2.cpp
		src/lccv.cpp
		src/libcamera_app.cpp
		src/libcamera_app_options.cpp
)

# Apply common compiler flags
add_compile_options(${COMMON_FLAGS})

# Link libraries
set(EXTRA_LIBS ${OpenCV_LIBS} 
    /usr/lib/aarch64-linux-gnu/libcamera.so
    /usr/lib/aarch64-linux-gnu/libcamera-base.so
    /usr/local/lib/ncnn/libncnn.a
)

set(EXECUTABLE_OUTPUT_PATH "../")

# Add executable and link libraries
add_link_options(-fopenmp -s -ldl -lpthread -lgflags)

add_executable(Traffic ${SRC_FILES})
target_link_libraries(Traffic ${EXTRA_LIBS})

