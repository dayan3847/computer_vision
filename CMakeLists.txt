cmake_minimum_required(VERSION 3.24)
project(CascadeClassificationKMeans)

set(CMAKE_CXX_STANDARD 23)
set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)

add_executable(CascadeClassificationKMeans main.cpp)
target_link_libraries(CascadeClassificationKMeans ${OpenCV_LIBS})
