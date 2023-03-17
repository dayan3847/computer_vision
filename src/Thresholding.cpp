//
// Created by dayan3847 on 3/16/23.
//

#include "Thresholding.h"

double Thresholding::optimalThreshold(Mat &image, int limit) {
    Scalar val = mean(image);
    double umCurrent = val[0];
    double umPrevious;
    int imageRows = image.rows;
    int imageCols = image.cols;
    int cont = 0;
    do {
        double umUp = 0;
        int contUp = 0;
        double umDown = 0;
        int contDown = 0;
        for (int i = 0; i < imageRows; i++) {
            auto *ptr = image.ptr<unsigned char>(i);
            for (int j = 0; j < imageCols; j++, ptr++)
                if (*ptr > umCurrent) {
                    umUp += *ptr;
                    contUp++;
                } else {
                    umDown += *ptr;
                    contDown++;
                }
        }
        umUp /= contUp;
        umDown /= contDown;
        umPrevious = umCurrent;
        umCurrent = (umUp + umDown) / 2;
        cont++;
    } while (umCurrent != umPrevious && cont <= limit);

    return umCurrent;
}
