cmake_minimum_required(VERSION 3.25)
project(plane_tracker)

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

add_executable(plane_tracker plane_tracker_main.cpp ${SOURCE_FILES})
target_link_libraries(plane_tracker ${OpenCV_LIBS})

add_executable(test_print_matriz tests/0_generate_matrices.cpp ${SOURCE_FILES})
target_link_libraries(test_print_matriz ${OpenCV_LIBS})

add_executable(test_get_original_corners tests/1_generate_corners_original.cpp ${SOURCE_FILES})
target_link_libraries(test_get_original_corners ${OpenCV_LIBS})

add_executable(test_fame tests/3_find_corners_fame.cpp ${SOURCE_FILES})
target_link_libraries(test_fame ${OpenCV_LIBS})
