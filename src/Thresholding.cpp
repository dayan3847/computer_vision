//
// Created by dayan3847 on 3/16/23.
//

#include "Thresholding.h"

double Thresholding::optimalThreshold(Mat &image, int limit) {
    double um, umUp, umDown, umOld;
    int cont = 0;
    int contUp, contDown;
    bool run = true;
    Scalar val = mean(image);
    um = val[0];
    int imageRows = image.rows;
    int imageCols = image.cols;
    do {
        umUp = umDown = 0;
        contUp = contDown = 0;
        for (int i = 0; i < imageRows; i++) {
            unsigned char *ptr = image.ptr<unsigned char>(i);
            for (int j = 0; j < imageCols; j++, ++ptr)
                if (*ptr > um) {
                    umUp += *ptr;
                    contUp++;
                } else {
                    umDown += *ptr;
                    contDown++;
                }
        }
        umUp /= contUp;
        umDown /= contDown;
        umOld = um;
        um = (umUp + umDown) / 2;
        cont++;
        if (um == umOld || cont > limit)
            run = false;
    } while (run);

    return um;
}
