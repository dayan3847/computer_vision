//
// Created by dayan3847 on 4/11/23.
//

#ifndef CASCADECLASSIFICATIONKMEANS_CONSOLEPRINTER_H
#define CASCADECLASSIFICATIONKMEANS_CONSOLEPRINTER_H


#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

class ConsolePrinter {
public:
    static void printMask(const Mat &mask);

    static void printImage(Mat &image, const string &name);
};


#endif //CASCADECLASSIFICATIONKMEANS_CONSOLEPRINTER_H
