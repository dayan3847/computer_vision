//
// Created by dayan3847 on 3/18/23.
//

#include "MatTools.h"

int MatTools::meanCovariance(Mat &image, Mat &Mask, Mat &mean, Mat &cov, int label) {
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
        if ((*itM) == label) {
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
        if ((*itM) == label) {
            pm[0] = (*it)[1] - m[0];
            pm[1] = (*it)[2] - m[1];
            Cv[0] += pm[0] * pm[0];
            Cv[1] += pm[1] * pm[1];
            Cv[2] += pm[0] * pm[1];
        }
    }
    icont = (float) (1. / (cont - 1));
    Cv[0] *= icont;
    Cv[1] *= icont;
    Cv[2] *= icont;

    cov.at<float>(0, 0) = Cv[0];
    cov.at<float>(1, 1) = Cv[1];
    cov.at<float>(1, 0) = cov.at<float>(0, 1) = Cv[2];

    return cont;
}

ImageStats MatTools::meanCovariance(Mat &image, Mat &mask, int label) {
    Mat mean, covariance;
    this->meanCovariance(image, mask, mean, covariance, label);
    auto a = mean.at<float>(0, 0);
    auto b = mean.at<float>(0, 1);
    auto s1 = covariance.at<float>(0, 0);
    auto s2 = covariance.at<float>(1, 1);
    auto s3 = covariance.at<float>(0, 1);

    return ImageStats{.mean = {a, b}, .covariance = {s1, s2, s3}};
}

double MatTools::distanceMahalanobisNormalized(
        double a,
        double b,
        double am,
        double bm,
        double s1,
        double s2,
        double s3
) {
    /*
       (a,b) vector a calcular su distancia.
       (am, bm) Vector promedio de la clase;
       [s1,s3
       s3,s2] Matriz de covarianza de la clase.
     */
    double det, idet, da, db, D;

    det = s1 * s2 - s3 * s3;
    idet = 1 / det;
    da = a - am;
    db = b - bm;
    D = log(det) + idet * (da * (da * s2 - db * s3) + db * (db * s1 - da * s3));
    return D;
}

double MatTools::distanceMahalanobisNormalized(float a, float b, ImageStats imageStats) {
    auto am = imageStats.mean.a;
    auto bm = imageStats.mean.b;
    auto s1 = imageStats.covariance.s1;
    auto s2 = imageStats.covariance.s2;
    auto s3 = imageStats.covariance.s3;
    auto det = s1 * s2 - s3 * s3;
    auto da = a - am;
    auto db = b - bm;
    auto distance = log(det) + (da * (da * s2 - db * s3) + db * (db * s1 - da * s3)) / det;

    return distance;
}

int MatTools::lastLabel = 1;

int MatTools::divideClass(Mat &mask, int label) {
    int newLabelA = ++MatTools::lastLabel;
    int newLabelB = ++MatTools::lastLabel;
    Mat_<uchar>::iterator it = mask.begin<uchar>();
    Mat_<uchar>::iterator itEnd = mask.end<uchar>();
    for (; it != itEnd; ++it) {
        if (*it == label) {
            if (rand() % 2) {
                *it = newLabelA;
            } else {
                *it = newLabelB;
            }
        }
    }
    return newLabelA;
}
