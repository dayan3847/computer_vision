cmake_minimum_required(VERSION 3.25)
project(chessboard_camera_calibration)

set(CMAKE_CXX_STANDARD 17)

# vcpkg install opencv2
#set(OpenCV_DIR "${VCPKG_INSTALLED_DIR}/x64-linux/share/opencv2")

set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)


set(
        SOURCE_FILES
        functions.h
        tools.h
        config.h
)

add_executable(chessboard_camera_calibration plane_tracker_main.cpp ${SOURCE_FILES})
target_link_libraries(chessboard_camera_calibration ${OpenCV_LIBS})

add_executable(main_test tests/main_test.cpp ${SOURCE_FILES})
target_link_libraries(main_test ${OpenCV_LIBS})

add_executable(main_test2 tests/main_test2.cpp ${SOURCE_FILES})
target_link_libraries(main_test2 ${OpenCV_LIBS})

add_executable(main_test3 tests/main_test3.cpp ${SOURCE_FILES})
target_link_libraries(main_test3 ${OpenCV_LIBS})

add_executable(test_print_matriz tests/test_print_matriz.cpp ${SOURCE_FILES})
target_link_libraries(test_print_matriz ${OpenCV_LIBS})
