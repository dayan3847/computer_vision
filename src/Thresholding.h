//
// Created by dayan3847 on 3/16/23.
//

#ifndef CASCADECLASSIFICATIONKMEANS_THRESHOLDING_H
#define CASCADECLASSIFICATIONKMEANS_THRESHOLDING_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Thresholding {
public:

    /**
     * Optimal Threshold
     *
     * @param image
     * @param limit
     * @return double
     */
    double optimalThreshold(Mat &image, int limit = 15);

};


#endif //CASCADECLASSIFICATIONKMEANS_THRESHOLDING_H
