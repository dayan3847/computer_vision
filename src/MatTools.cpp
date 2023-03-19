//
// Created by dayan3847 on 3/18/23.
//

#include "MatTools.h"

int MatTools::meanCovariance(Mat &image, Mat &Mask, Mat &mean, Mat &cov) {
    float m[2], pm[2], Cv[3], icont;
    int cont;

    mean = Mat::zeros(2, 1, CV_32F);
    cov = Mat::zeros(2, 2, CV_32F);
    Mat_<Vec3f>::iterator it, itEnd;
    Mat_<uchar>::iterator itM;

    it = image.begin<Vec3f>();
    itM = Mask.begin<uchar>();
    itEnd = image.end<Vec3f>();
    m[0] = m[1] = 0;
    memset(m, 0, 2 * sizeof(float));
    for (cont = 0; it != itEnd; ++it, ++itM) {
        if ((*itM)) {
            m[0] += (*it)[1];      //Acumulamos el componente a de CIE-Lab
            m[1] += (*it)[2];      //Acumulamos el componente b de CIE-Lab
            cont++;
        }
    }

    if (!cont)
        return -1;
    m[0] /= (float) cont;
    m[1] /= (float) cont;
    mean = Mat(2, 1, CV_32F, m).clone();

    if (cont < 2) {
        cov.at<float>(0, 0) = cov.at<float>(1, 1) =
        cov.at<float>(2, 2) = 1.;
        return -2;
    }
    it = image.begin<Vec3f>();
    itM = Mask.begin<uchar>();
    memset(Cv, 0, 3 * sizeof(float));
    for (; it != itEnd; ++it, ++itM) {
        if ((*itM)) {
            pm[0] = (*it)[1] - m[0];
            pm[1] = (*it)[2] - m[1];
            Cv[0] += pm[0] * pm[0];
            Cv[1] += pm[1] * pm[1];
            Cv[2] += pm[0] * pm[1];
        }
    }
    icont = 1. / (cont - 1);
    Cv[0] *= icont;
    Cv[1] *= icont;
    Cv[2] *= icont;

    cov.at<float>(0, 0) = Cv[0];
    cov.at<float>(1, 1) = Cv[1];
    cov.at<float>(1, 0) = cov.at<float>(0, 1) = Cv[2];

    return cont;
}
