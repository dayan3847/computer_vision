//
// Created by dayan3847 on 3/16/23.
//

#include "Thresholding.h"
#include "MatTools.h"
#include "History.h"
#include <iostream>

int Thresholding::lastLabel = 1;

vector<int> Thresholding::divideClass(Mat &mask, int label) {
    int newLabelA = Thresholding::lastLabel++;
    int newLabelB = Thresholding::lastLabel++;
    auto it = mask.begin<uchar>();
    auto itEnd = mask.end<uchar>();
    for (; it != itEnd; ++it) {
        if (*it == label) {
            if (rand() % 2) {
                *it = newLabelA;
            } else {
                *it = newLabelB;
            }
        }
    }
    return vector<int>({newLabelA, newLabelB});
}

void Thresholding::cOutImageStats(ImageStats &imageStats) {
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
        Mat &mask,
        vector<int> &labels,
        bool &hasClassA,
        bool &hasClassB,
        bool covariance
) {
    int limit = covariance ? iterationsLimitWithConvergence : iterationsLimitWithoutConvergence;
    auto &stats = History::imageStatsMap;
    for (int i = 0; i < limit; i++) {
        cout << "Iteration: " << i << endl;

        hasClassA = false;
        hasClassB = false;

        int classA = labels[0];
        int classB = labels[1];

        cOutImageStats(stats[classA]);
        cOutImageStats(stats[classB]);

        auto changesCount = this->reorderPixels(
                mask,
                labels,
                hasClassA,
                hasClassB
        );

        if (0 == changesCount) {
            cout << "El algoritmo convergió en " << i << " iteraciones." << endl;
            return 0;
        } else {
            MatTools::meanCovariance(this->image, mask, stats, labels, covariance);
        }
    }

    return 1;
}

// reordenar los pixels
int Thresholding::reorderPixels(
        Mat &mask,
        vector<int> &labels,
        bool &hasClassA,
        bool &hasClassB
) {
    auto &stats = History::imageStatsMap;
    int classA = labels[0];
    int classB = labels[1];
    ImageStats imageStatsClassA = stats[classA];
    ImageStats imageStatsClassB = stats[classB];

    auto itImage = this->image.begin<Vec3f>();
    auto itMask = mask.begin<uchar>();
    auto itEnd = mask.end<uchar>();
    int changesCount = 0;
    while (itMask != itEnd) {
        Vec3f pixel = *itImage;
        float a = pixel[1];
        float b = pixel[2];
        // Calculate distance.
        double distanceA = MatTools::distanceMahalanobisNormalized(a, b, imageStatsClassA);
        double distanceB = MatTools::distanceMahalanobisNormalized(a, b, imageStatsClassB);
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

    return changesCount;
}


vector<int> Thresholding::propagate(Mat &mask, vector<int> &labels) {
    // labels que de deben propagar en la siguiente iteracion
    vector<int> nextLabels = {};

    auto &stats = History::imageStatsMap;
    for (int label: labels) {
        vector<int> newLabels = this->divideClass(mask, label);

        MatTools::meanCovariance(this->image, mask, stats, newLabels, false);

        bool hasClassA = false, hasClassB = false;
        this->toThreshold(
                mask,
                newLabels,
                hasClassA,
                hasClassB,
                false
        );

        if (hasClassA && hasClassB) {
            this->toThreshold(
                    mask,
                    newLabels,
                    hasClassA,
                    hasClassB,
                    true
            );
        }
        if (hasClassA) {
            int classA = newLabels[0];
            if (hasClassB) {
                nextLabels.push_back(classA);
            }
        }
        if (hasClassB) {
            int classB = newLabels[1];
            if (hasClassA) {
                nextLabels.push_back(classB);
            }
        }
    }
    return nextLabels;
}

Thresholding::Thresholding(Mat &image) {
    this->image = image;
    this->iterationsLimitWithConvergence = 10;
    this->iterationsLimitWithoutConvergence = 5;
}
