cmake_minimum_required(VERSION 3.25)
project(chessboard_camera_calibration)

set(CMAKE_CXX_STANDARD 17)

# vcpkg install opencv2
#set(OpenCV_DIR "${VCPKG_INSTALLED_DIR}/x64-linux/share/opencv2")

set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)


set(
        SOURCE_FILES
        config.h
        tools.h
        functions.h
        plane_tracker.h
)

add_executable(chessboard_camera_calibration plane_tracker_main.cpp ${SOURCE_FILES})
target_link_libraries(chessboard_camera_calibration ${OpenCV_LIBS})

add_executable(test_print_matriz tests/test_print_matriz.cpp ${SOURCE_FILES})
target_link_libraries(test_print_matriz ${OpenCV_LIBS})

add_executable(test_get_original_corners tests/1_generate_original_corners.cpp ${SOURCE_FILES})
target_link_libraries(test_get_original_corners ${OpenCV_LIBS})

add_executable(test_fame tests/test_fame.cpp ${SOURCE_FILES})
target_link_libraries(test_fame ${OpenCV_LIBS})
