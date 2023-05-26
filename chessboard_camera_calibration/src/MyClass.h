//
// Created by dayan3847 on 5/26/23.
//

#ifndef CHESSBOARD_CAMERA_CALIBRATION_MYCLASS_H
#define CHESSBOARD_CAMERA_CALIBRATION_MYCLASS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>

namespace dayan3847 {

    class MyClass {
    public:
        static int hello();

        static void printMat(const cv::Mat &mat, const std::string &name = "Mat");
    };

} // dayan3847

#endif //CHESSBOARD_CAMERA_CALIBRATION_MYCLASS_H
