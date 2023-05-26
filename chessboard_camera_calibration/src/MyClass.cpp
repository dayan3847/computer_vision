//
// Created by dayan3847 on 5/26/23.
//

#include "MyClass.h"

namespace dayan3847 {
    int MyClass::hello() {
        return 1;
    }

    void MyClass::printMat(const cv::Mat &mat, const std::string &name) {
        std::cout << name << std::endl;
        for (int i = 0; i < mat.rows; i++) {
            for (int j = 0; j < mat.cols; j++)
                std::cout << mat.at<double>(i, j) << "\t";
            std::cout << std::endl;
        }
    }
} // dayan3847