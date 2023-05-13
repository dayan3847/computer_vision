//
// Created by dayan3847 on 4/11/23.
//

#include "ConsolePrinter.h"
#include <iostream>

using namespace std;

void ConsolePrinter::printMask(const Mat &mask) {
    cout << "Mask: " << endl;
    cout << "\t[ " << endl;
    for (int i = 0; i < mask.cols; ++i) {
        for (int j = 0; j < mask.rows; ++j) {
            int label = mask.at<uchar>(i, j);
            cout << "\t" << label << " ";
        }
        cout << endl;
    }

    cout << "\t] " << endl;
}


void ConsolePrinter::printImage(Mat &image, const string &name) {
    cout << "Image: " << name << endl;
    cout << "\tMatrix L:" << name << endl;
    cout << "\t[ " << endl;
    for (int i = 0; i < image.cols; ++i) {
        for (int j = 0; j < image.rows; ++j) {
            cout << "\t" << image.at<Vec3f>(i, j)[0];
        }
        cout << endl;
    }

    cout << "\t] " << endl;

    cout << "\tMatrix a:" << name << endl;
    cout << "\t[ " << endl;
    for (int i = 0; i < image.cols; ++i) {
        for (int j = 0; j < image.rows; ++j) {
            cout << "\t" << image.at<Vec3f>(i, j)[1];
        }
        cout << endl;
    }

    cout << "\t] " << endl;

    cout << "\tMatrix b:" << name << endl;
    cout << "\t[ " << endl;
    for (int i = 0; i < image.cols; ++i) {
        for (int j = 0; j < image.rows; ++j) {
            cout << "\t" << image.at<Vec3f>(i, j)[2];
        }
        cout << endl;
    }

    cout << "\t] " << endl;
}
