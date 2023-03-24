//
// Created by dayan3847 on 3/16/23.
//

#ifndef CASCADECLASSIFICATIONKMEANS_THRESHOLDING_H
#define CASCADECLASSIFICATIONKMEANS_THRESHOLDING_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ImageStats.h"


using namespace cv;
using namespace std;

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

    /**
     * Dividir una clase
     */
    int divideClass(Mat &mask, int label = 1);

    int toThreshold(
            Mat &image,
            Mat &mask,
            int classA,
            int classB,
            ImageStats &imageStatsClassA,
            ImageStats &imageStatsClassB,
            bool &hasClassA,
            bool &hasClassB,
            int iterationsLimit = 100,
            int iterationsLimitWithoutConvergence = 3
    );

    vector<int> propagate(Mat &image, Mat &mask, vector<int> &labels);

private:
    static int lastLabel;
};


#endif //CASCADECLASSIFICATIONKMEANS_THRESHOLDING_H
