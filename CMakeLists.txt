cmake_minimum_required(VERSION 3.24)
project(LearningOpenCV)

set(CMAKE_CXX_STANDARD 17)

set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp src/Thresholding.cpp src/Thresholding.h src/GeometricTransformation.cpp src/GeometricTransformation.h)
add_executable(LearningOpenCV ${SOURCE_FILES})
target_link_libraries(LearningOpenCV ${OpenCV_LIBS})
