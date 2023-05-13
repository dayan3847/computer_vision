//
// Created by dayan3847 on 4/11/23.
//

#ifndef CASCADECLASSIFICATIONKMEANS_IMAGETOOLS_H
#define CASCADECLASSIFICATIONKMEANS_IMAGETOOLS_H

#include "opencv2/opencv.hpp"
#include "ImageStats.h"

using namespace std;
using namespace cv;

class ImageTools {
public:
    static void showImage(Mat &image, const string &name, bool destroy = true);

    /**
     * Imprime la imagen con los valores (a y b) promedio de cada clase
     *
     * @param mask
     * @param originalImage
     * @param stats
     * @param luminance  luminance = 0 -> no luminance
     *                   luminance = 1 -> original luminance
     *                   luminance = 2 -> mean luminance
     */
    static void printImageByMask(
            const Mat &mask,
            const Mat &originalImage,
            map<int, ImageStats> &stats,
            const int &luminance = 1
    );
};


#endif //CASCADECLASSIFICATIONKMEANS_IMAGETOOLS_H
