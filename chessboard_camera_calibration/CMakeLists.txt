cmake_minimum_required(VERSION 3.25)
project(chessboard_camera_calibration)

set(CMAKE_CXX_STANDARD 17)

# vcpkg install opencv2
#set(OpenCV_DIR "${VCPKG_INSTALLED_DIR}/x64-linux/share/opencv2")
#find_package(OpenCV REQUIRED)

set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)


set(
        SOURCE_FILES
        src/MyClass.cpp
        src/MyClass.h
)
add_executable(chessboard_camera_calibration main.cpp ${SOURCE_FILES})
add_executable(main_test main_test.cpp ${SOURCE_FILES})
add_executable(main_test2 main_test2.cpp ${SOURCE_FILES})
add_executable(main_test3 main_test3.cpp ${SOURCE_FILES})


#target_link_libraries(main_test3 PRIVATE Eigen3::Eigen)
target_link_libraries(chessboard_camera_calibration ${OpenCV_LIBS} Eigen3::Eigen)
target_link_libraries(main_test ${OpenCV_LIBS} Eigen3::Eigen)
target_link_libraries(main_test2 ${OpenCV_LIBS} Eigen3::Eigen)
target_link_libraries(main_test3 ${OpenCV_LIBS} Eigen3::Eigen)
