//
// Created by dayan3847 on 3/28/23.
//

#ifndef CASCADECLASSIFICATIONKMEANS_IMAGEREPO_H
#define CASCADECLASSIFICATIONKMEANS_IMAGEREPO_H

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

class ImageRepo {
public:

    void byName(Mat &image, Mat &imageOriginal,const string &name);

    void arcoiris_3x3(Mat &image,Mat &imageOriginal);

    void corazon_3x3(Mat &image,Mat &imageOriginal);

    void corazon_10x10(Mat &image,Mat &imageOriginal);

    void jaguarcito(Mat &image,Mat &imageOriginal);


};


#endif //CASCADECLASSIFICATIONKMEANS_IMAGEREPO_H
