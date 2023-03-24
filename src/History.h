//
// Created by dayan3847 on 3/21/23.
//

#ifndef CASCADECLASSIFICATIONKMEANS_HISTORY_H
#define CASCADECLASSIFICATIONKMEANS_HISTORY_H

#include <vector>
#include "opencv2/opencv.hpp"
#include "ImageStats.h"

using namespace std;
using namespace cv;

class History {
public:
    vector<int> labels;
    Mat mask;
    static map<int, ImageStats> imageStatsMap;

    History(Mat &mask,  vector<int> &labels);

};


#endif //CASCADECLASSIFICATIONKMEANS_HISTORY_H
