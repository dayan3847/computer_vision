cmake_minimum_required(VERSION 3.25)
project(chessboard_camera_calibration)

set(CMAKE_CXX_STANDARD 17)

# vcpkg install opencv2
#set(OpenCV_DIR "${VCPKG_INSTALLED_DIR}/x64-linux/share/opencv2")
#find_package(OpenCV REQUIRED)

set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)

add_executable(chessboard_camera_calibration main.cpp)

target_link_libraries(chessboard_camera_calibration ${OpenCV_LIBS})
