//
// Created by dayan3847 on 3/16/23.
//

#include "Thresholding.h"
#include "MatTools.h"
#include <iostream>

int Thresholding::lastLabel = 1;

Thresholding::Thresholding(Mat &image) {
    this->image = image;
    this->iterationsLimitWithConvergence = 20;
    this->iterationsLimitWithoutConvergence = 5;
}

int Thresholding::countClass(Mat &mask, int label) {
    auto it = mask.begin<uchar>();
    auto itEnd = mask.end<uchar>();
    int count = 0;
    for (; it != itEnd; ++it) {
        if ((*it) == label) {
            count++;
        }
    }
    return count;
}

vector<int> Thresholding::divideClass(Mat &mask, int label) {
    int newLabelA = Thresholding::lastLabel++;
    int newLabelB = Thresholding::lastLabel++;
    int changesCount = 0;
    auto it = mask.begin<uchar>();
    auto itEnd = mask.end<uchar>();
    for (; it != itEnd; ++it) {
        if (*it == label) {
            *it = (0 == (changesCount % 2)) ? newLabelA : newLabelB;
            changesCount++;
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
        map<int, ImageStats> &stats,
        bool &hasClassA,
        bool &hasClassB,
        bool covariance
) {
    int limit = covariance ? iterationsLimitWithConvergence : iterationsLimitWithoutConvergence;
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
                stats,
                hasClassA,
                hasClassB
        );

        if (0 == changesCount) {
            cout << "El algoritmo convergió en " << i << " iteraciones." << endl;
            return 0;
        } else {
            cout << "Hubo: " << changesCount << " cambios." << endl;
            MatTools::meanCovariance(this->image, mask, stats, labels, covariance);
        }
    }

    return 1;
}

int Thresholding::reorderPixels(
        Mat &mask,
        vector<int> &labels,
        map<int, ImageStats> &stats,
        bool &hasClassA,
        bool &hasClassB
) {
    int classA = labels[0];
    int classB = labels[1];
    ImageStats imageStatsClassA = stats[classA];
    ImageStats imageStatsClassB = stats[classB];

    auto itImage = this->image.begin<Vec3f>();
    auto itMask = mask.begin<uchar>();
    auto itEnd = mask.end<uchar>();
    int changesCount = 0;
    while (itMask != itEnd) {
        auto &label = *itMask;
        if (classA != label && classB != label) {
            itImage++;
            itMask++;
            continue;
        }
        Vec3f pixel = *itImage;
        float a = pixel[1];
        float b = pixel[2];
        // Calculate distance.
        double distanceA = MatTools::distanceMahalanobisNormalized(a, b, imageStatsClassA);
        double distanceB = MatTools::distanceMahalanobisNormalized(a, b, imageStatsClassB);
        if (distanceA < distanceB) {
            hasClassA = true;
            if (classA != label) {
                label = classA;
                changesCount++;
            }
        } else {
            hasClassB = true;
            if (classB != label) {
                label = classB;
                changesCount++;
            }
        }
        itImage++;
        itMask++;
    }

    return changesCount;
}


vector<int> Thresholding::propagate(Mat &mask, vector<int> &labels, map<int, ImageStats> &stats) {
    // labels que de deben propagar en la siguiente iteracion
    vector<int> nextLabels = {};

    for (int label: labels) {
        auto count = this->countClass(mask, label);
        if (count < 2) {
            continue;
        }
        vector<int> newLabels = this->divideClass(mask, label);

        MatTools::meanCovariance(this->image, mask, stats, newLabels, false);

        bool hasClassA = false, hasClassB = false;
        this->toThreshold(
                mask,
                newLabels,
                stats,
                hasClassA,
                hasClassB,
                false
        );

        if (hasClassA && hasClassB) {
            this->toThreshold(
                    mask,
                    newLabels,
                    stats,
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
