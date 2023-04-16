//
// Created by dayan3847 on 4/11/23.
//

#ifndef CASCADECLASSIFICATIONKMEANS_MAIN_H
#define CASCADECLASSIFICATIONKMEANS_MAIN_H

#include "opencv2/opencv.hpp"
#include "ImageStats.h"

using namespace std;
using namespace cv;

class Main {
private:

    /**
     * Image BGR2Lab
     */
    Mat image;

    /**
     * Original image
     */
    Mat imageOriginal;

    /**
     * Mask
     */
    Mat mask;

    /**
     * Estadisticas de cada clase
     */
    map<int, ImageStats> stats;

    string imagePath;

public:
    explicit Main(string imagePath);

    void run();
};


#endif //CASCADECLASSIFICATIONKMEANS_MAIN_H
