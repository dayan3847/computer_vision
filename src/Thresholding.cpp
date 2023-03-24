//
// Created by dayan3847 on 3/16/23.
//

#include "Thresholding.h"
#include "MatTools.h"
#include "History.h"
#include <iostream>

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

int Thresholding::lastLabel = 1;

int Thresholding::divideClass(Mat &mask, int label) {
    int newLabelA = Thresholding::lastLabel++;
    int newLabelB = Thresholding::lastLabel++;
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

void cOutImageStats(ImageStats imageStats) {
    cout << "Class: " << imageStats.label << endl
         << "\tcount: " << imageStats.count << endl
         << "\tmean: "
         << "a: " << imageStats.mean.a
         << " b: " << imageStats.mean.b << endl
         << "\tcovariance: "
         << "s1: " << imageStats.covariance.s1
         << " s2: " << imageStats.covariance.s2
         << " s3: " << imageStats.covariance.s3
         << endl;
}

int Thresholding::toThreshold(
        Mat &image,
        Mat &mask,
        int classA,
        int classB,
        ImageStats &imageStatsClassA,
        ImageStats &imageStatsClassB,
        bool &hasClassA,
        bool &hasClassB,
        int iterationsLimit,
        int iterationsLimitWithoutConvergence
) {
    MatTools matTools = MatTools();
    for (int i = 0; i < iterationsLimit; i++) {
        cout << "Iteration: " << i << endl;

        hasClassA = false;
        hasClassB = false;
        imageStatsClassA = matTools.meanCovariance(image, mask, classA);
        imageStatsClassB = matTools.meanCovariance(image, mask, classB);

        cout << "imageStatsClassA.mean: "
             << "a: " << imageStatsClassA.mean.a
             << " b: " << imageStatsClassA.mean.b
             << endl;
        cout << "imageStatsClassB.mean: "
             << "a: " << imageStatsClassB.mean.a
             << " b: " << imageStatsClassB.mean.b
             << endl;

        auto stats = matTools.meanCovariance(
                image,
                mask,
                i < iterationsLimitWithoutConvergence
        );

        imageStatsClassA = stats[classA];
        imageStatsClassB = stats[classB];

        cOutImageStats(imageStatsClassA);
        cOutImageStats(imageStatsClassB);

        auto itImage = image.begin<Vec3f>();
        auto itMask = mask.begin<uchar>();
        auto itEnd = mask.end<uchar>();
        int changesCount = 0;
        while (itMask != itEnd) {
            Vec3f pixel = *itImage;
            float a = pixel[1];
            float b = pixel[2];
            // Calculate distance.
            double distanceA = matTools.distanceMahalanobisNormalized(a, b, imageStatsClassA);
            double distanceB = matTools.distanceMahalanobisNormalized(a, b, imageStatsClassB);
            if (distanceA < distanceB) {
                hasClassA = true;
                if (classA != *itMask) {
                    *itMask = classA;
                    changesCount++;
                }
            } else {
                hasClassB = true;
                if (classB != *itMask) {
                    *itMask = classB;
                    changesCount++;
                }
            }
            itImage++;
            itMask++;
        }
        if (0 == changesCount) {
            cout << "El algoritmo convergió en " << i << " iteraciones." << endl;
            break;
        }
    }

    return 0;
}

vector<int> Thresholding::propagate(Mat &image, Mat &mask, vector<int> &labels) {
    vector<int> newLabels = {};

    for (int label: labels) {
        int classA = this->divideClass(mask, label);
        int classB = classA + 1;
        ImageStats imageStatsClassA, imageStatsClassB;
        bool hasClassA, hasClassB;
        this->toThreshold(
                image,
                mask,
                classA,
                classB,
                imageStatsClassA,
                imageStatsClassB,
                hasClassA,
                hasClassB
        );
        if (hasClassA) {
            History::imageStatsMap[classA] = imageStatsClassA;
            if (hasClassB) {
                newLabels.push_back(classA);
            }
        }
        if (hasClassB) {
            History::imageStatsMap[classB] = imageStatsClassB;
            if (hasClassA) {
                newLabels.push_back(classB);
            }
        }
    }
    return newLabels;
}
