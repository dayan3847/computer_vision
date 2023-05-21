cmake_minimum_required(VERSION 3.25)
project(chessboard_camera_calibration)

set(CMAKE_CXX_STANDARD 17)

# vcpkg install opencv2
#set(OpenCV_DIR "${VCPKG_INSTALLED_DIR}/x64-linux/share/opencv2")
#find_package(OpenCV REQUIRED)

set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)



add_executable(chessboard_camera_calibration main.cpp tools.h)
# main_test
add_executable(main_test main_test.cpp)
add_executable(main_test2 main_test2.cpp tools.h)
add_executable(main_test3 test_gram_schmidt_orthogonalization.cpp)


target_link_libraries(main_test ${OpenCV_LIBS})
target_link_libraries(main_test3 PRIVATE Eigen3::Eigen)

#target_link_libraries(chessboard_camera_calibration ${OpenCV_LIBS})
#target_link_libraries(chessboard_camera_calibration PRIVATE Eigen3::Eigen)
target_link_libraries(chessboard_camera_calibration ${OpenCV_LIBS} Eigen3::Eigen)
