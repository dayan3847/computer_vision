//
// Created by dayan3847 on 3/16/23.
//

#ifndef CASCADECLASSIFICATIONKMEANS_THRESHOLDING_H
#define CASCADECLASSIFICATIONKMEANS_THRESHOLDING_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <map>
#include "ImageStats.h"

using namespace cv;
using namespace std;

class Thresholding {
public:
    /**
     * Constructor
     *
     * @param image
     * @param stats
     */
    explicit Thresholding(Mat &image);

    static int countClass(Mat &mask, int label);

    /**
     * Dividir una clase
     */
    static vector<int> divideClass(Mat &mask, int label = 0);

    static void cOutImageStats(ImageStats &imageStats);

    int toThreshold(
            Mat &mask,
            vector<int> &labels,
            map<int, ImageStats> &stats,
            bool &hasClassA,
            bool &hasClassB,
            bool covariance = true
    );

    // reorder the pixels
    int reorderPixels(
            Mat &mask,
            vector<int> &labels,
            map<int, ImageStats> &stats,
            bool &hasClassA,
            bool &hasClassB
    );

    vector<int> propagate(Mat &mask, vector<int> &labels, map<int, ImageStats> &stats);

private:
    static int lastLabel;
    Mat image;
    int iterationsLimitWithConvergence;
    int iterationsLimitWithoutConvergence;
};


#endif //CASCADECLASSIFICATIONKMEANS_THRESHOLDING_H
