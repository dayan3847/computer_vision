cmake_minimum_required(VERSION 3.24)
project(CascadeClassificationKMeans)

set(CMAKE_CXX_STANDARD 23)

set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)

set(
        SOURCE_FILES
        main.cpp
        src/Thresholding.h
        src/Thresholding.cpp
        src/MatTools.cpp
        src/MatTools.h
        src/ImageStats.h
        src/ImageRepo.cpp
        src/ImageRepo.h
        src/ImageTools.cpp
        src/ImageTools.h
        src/Main.cpp
        src/Main.h
        src/ConsolePrinter.cpp
        src/ConsolePrinter.h
)
add_executable(CascadeClassificationKMeans ${SOURCE_FILES})

target_link_libraries(CascadeClassificationKMeans ${OpenCV_LIBS})
