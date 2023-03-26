//
// Created by dayan3847 on 3/18/23.
//

#include "MatTools.h"
#include <vector>

int MatTools::mean(Mat &image, Mat &mask, map<int, ImageStats> &stats, vector<int> &labels) {
    if (labels.empty()) {
        return -1;
    }
    for (auto label: labels) {
        stats[label] = ImageStats();
        stats[label].label = label;
    }

    auto itMask = mask.begin<uchar>();
    auto itMaskEnd = mask.end<uchar>();
    auto itImage = image.begin<Vec3f>();

    while (itMask != itMaskEnd) {
        auto label = *itMask;
        // skip if label is not in labels
        if (find(labels.begin(), labels.end(), label) == labels.end()) {
            itMask++;
            itImage++;
            continue;
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

    return 0;
}

int MatTools::meanCovariance(Mat &image, Mat &mask, map<int, ImageStats> &stats, vector<int> &labels, bool covariance) {
    auto result = MatTools::mean(image, mask, stats, labels);
    if (0 != result) {
        return result;
    }
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
    return 0;
}

double MatTools::distanceMahalanobisNormalized(double a, double b, ImageStats imageStats) {
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
