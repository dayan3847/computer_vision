//
// Created by dayan3847 on 3/18/23.
//

#include "MatTools.h"
#include <vector>

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
    ImageStats result = ImageStats();

    auto itMask = mask.begin<uchar>();
    auto itImage = image.begin<Vec3f>();
    auto itImageEnd = image.end<Vec3f>();
    int cont = 0;

    while (itImage != itImageEnd) {
        if (*itMask == label) {
            result.mean.a += (*itImage)[0];
            result.mean.b += (*itImage)[1];
            cont++;
        }
        itImage++;
        itMask++;
    }

    if (0 == cont)
        return {};

    result.mean.a /= (float) cont;
    result.mean.b /= (float) cont;

    if (cont < 2) {
        return result;
    }

    itMask = mask.begin<uchar>();
    itImage = image.begin<Vec3f>();

    while (itImage != itImageEnd) {
        if (*itMask == label) {
            auto a = (*itImage)[0];
            auto b = (*itImage)[1];
            auto ad = a - result.mean.a;
            auto bd = b - result.mean.b;
            result.covariance.s1 += ad * ad;
            result.covariance.s2 += bd * bd;
            result.covariance.s3 += ad * bd;
        }
        itImage++;
        itMask++;
    }

    auto iCont = (float) (1. / (cont - 1));
    result.covariance.s1 *= iCont;
    result.covariance.s2 *= iCont;
    result.covariance.s3 *= iCont;

    return result;
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

map<int, ImageStats> MatTools::mean(Mat &image, Mat &mask) {
    auto stats = map<int, ImageStats>();

    auto itMask = mask.begin<uchar>();
    auto itMaskEnd = mask.end<uchar>();
    auto itImage = image.begin<Vec3f>();

    while (itMask != itMaskEnd) {
        auto label = *itMask;
        if (stats.find(label) == stats.end()) {
            stats[label] = ImageStats();
            stats[label].label = label;

        }
        auto &imageStats = stats[label];
        imageStats.mean.a += (*itImage)[0];
        imageStats.mean.b += (*itImage)[1];
        imageStats.count++;
        itMask++;
        itImage++;
    }

    for (auto &item: stats) {
        auto &imageStats = item.second;
        auto &count = imageStats.count;
        imageStats.mean.a /= (float) count;
        imageStats.mean.b /= (float) count;
    }

    return stats;
}

map<int, ImageStats> MatTools::meanCovariance(Mat &image, Mat &mask, bool covariance) {
    auto stats = this->mean(image, mask);
    if (covariance) {
        // calculate covariance
        auto itMask = mask.begin<uchar>();
        auto itMaskEnd = mask.end<uchar>();
        auto itImage = image.begin<Vec3f>();

        while (itMask != itMaskEnd) {
            auto label = *itMask;
            auto &imageStats = stats[label];
            auto a = (*itImage)[0];
            auto b = (*itImage)[1];
            auto ad = a - imageStats.mean.a;
            auto bd = b - imageStats.mean.b;
            imageStats.covariance.s1 += ad * ad;
            imageStats.covariance.s2 += bd * bd;
            imageStats.covariance.s3 += ad * bd;
            itMask++;
            itImage++;
        }

        for (auto &item: stats) {
            auto &imageStats = item.second;
            auto &count = imageStats.count;
            if (count < 2) {
                continue;
            }
            auto iCont = (float) (1. / (count - 1));
            imageStats.covariance.s1 *= iCont;
            imageStats.covariance.s2 *= iCont;
            imageStats.covariance.s3 *= iCont;
        }

    }
    return stats;
}
