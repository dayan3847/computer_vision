#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "src/Thresholding.h"
#include "src/MatTools.h"
#include "src/History.h"

using namespace std;
using namespace cv;

int main() {
    // Image
    string name = "img/jaguarcito.png";
    // Read image.
    Mat image = imread(name);
    // Convert to float values.
    Mat imageFloat;
    image.convertTo(imageFloat, CV_32FC3);
    // Normalize.
    imageFloat /= 255.0;
    // Convert to BGR2Lab.
    Mat imageLab;
    cvtColor(imageFloat, imageLab, COLOR_BGR2Lab);
    // Calculate mean and covariance.
    MatTools matTools = MatTools();
    Mat mask = Mat::zeros(imageLab.size(), CV_8UC1);

    cout << "imageLab.size()" << imageLab.size() << endl;

    ImageStats imageStats = matTools.meanCovariance(imageLab, mask, 1);
    cout << "Mean: "
         << "a " << imageStats.mean.a
         << " b " << imageStats.mean.b
         << endl;
    cout << "Covariance: "
         << "s1 " << imageStats.covariance.s1
         << " s2 " << imageStats.covariance.s2
         << " s3 " << imageStats.covariance.s3
         << endl;

    cout << "Image: \"" << name << "\" (" << image.rows << "x" << image.cols << ")" << endl;

    imshow(name, image);
    waitKey(0);
    destroyWindow(name);

    Thresholding thresholding = Thresholding();

    History::imageStatsMap[1] = imageStats;
    vector<History> historyVector;
    vector<int> labels = {0};
    auto iHistory = History(mask, labels);
    historyVector.push_back(iHistory);
    for (int i = 0; i < 1; ++i) {
        cout << "Level: " << i << endl;
        labels = thresholding.propagate(imageLab, mask, labels);

        if (labels.empty()) {
            break;
        }

        // print labels
        cout << "Labels: ";
        for (const auto &itemLabels: labels) {
            cout << itemLabels << " ";
        }
        cout << endl;

        iHistory = History(mask, labels);
        historyVector.push_back(iHistory);
    }

    for (const auto &itemHistoryVector: historyVector) {
        Mat m = itemHistoryVector.mask;
        Mat imageLabThr = imageLab.clone();
        auto itImage = imageLabThr.begin<Vec3f>();
        auto itMask = m.begin<uchar>();
        auto itEnd = m.end<uchar>();
        while (itMask != itEnd) {
            auto imageStatsClassI = History::imageStatsMap[*itMask];
            (*itImage)[0] = imageStatsClassI.mean.a;
            (*itImage)[1] = imageStatsClassI.mean.b;
            itImage++;
            itMask++;
        }

        Mat imageThr;
        cvtColor(imageLabThr, imageThr, COLOR_Lab2BGR);
        imageThr *= 255.0;
        imageThr.convertTo(imageThr, CV_8UC3);

        imshow("Thresholding", imageThr);
        waitKey(0);
        destroyWindow("Thresholding");
    }

    return 0;
}
