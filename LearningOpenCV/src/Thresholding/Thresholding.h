//
// Created by dayan3847 on 1/03/23.
//

#ifndef LEARNINGOPENCV_THRESHOLDING_H
#define LEARNINGOPENCV_THRESHOLDING_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Thresholding {
public:
    void helloWorld();

    // encuentra el umbral optimo
    double optimalThreshold(Mat &image, int limit);
};


#endif //LEARNINGOPENCV_THRESHOLDING_H
