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

    int countClass(Mat &mask, int label);

    /**
     * Dividir una clase
     */
    static vector<int> divideClass(Mat &mask, int label = 0);

    static void cOutImageStats(ImageStats &imageStats);

    int toThreshold(
            Mat &mask,
            vector<int> &labels,
            bool &hasClassA,
            bool &hasClassB,
            bool covariance = true
    );

    int reorderPixels(
            Mat &mask,
            vector<int> &labels,
            bool &hasClassA,
            bool &hasClassB
    );

    vector<int> propagate(Mat &mask, vector<int> &labels);

    Thresholding(Mat &image);

private:
    static int lastLabel;
    Mat image;
    int iterationsLimitWithConvergence;
    int iterationsLimitWithoutConvergence;
};


#endif //CASCADECLASSIFICATIONKMEANS_THRESHOLDING_H
