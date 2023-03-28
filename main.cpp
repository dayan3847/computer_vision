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

void showImage(Mat &image, const string& name) {
    Mat &imageToPrint = image;
//    resize(image, imageToPrint, Size(600, 600));
//    resizeWindow(name, 600, 600);
    imshow(name, imageToPrint);
    waitKey(0);
    destroyWindow(name);
}


void printImage(Mat &image, const string& name) {
    cout << "Image: " << name << endl;
    cout << "\tMatrix L:" << name << endl;
    cout << "\t[ " << endl;
    for (int i = 0; i < image.cols; ++i) {
        for (int j = 0; j < image.rows; ++j) {
            cout << "\t"<< image.at<Vec3f>(i, j)[0];
        }
        cout << endl;
    }

    cout << "\t] " << endl;

    cout << "\tMatrix a:" << name << endl;
    cout << "\t[ " << endl;
    for (int i = 0; i < image.cols; ++i) {
        for (int j = 0; j < image.rows; ++j) {
            cout << "\t" << image.at<Vec3f>(i, j)[1];
        }
        cout << endl;
    }

    cout << "\t] " << endl;

    cout << "\tMatrix b:" << name << endl;
    cout << "\t[ " << endl;
    for (int i = 0; i < image.cols; ++i) {
        for (int j = 0; j < image.rows; ++j) {
            cout << "\t" << image.at<Vec3f>(i, j)[2];
        }
        cout << endl;
    }

    cout << "\t] " << endl;
}

int main() {
    // Image
//    auto name = "img/c_3x3.png";
//    auto name = "img/corazon.png";
    auto name = "img/jaguarcito.png";
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
    // init mask with zeros.
    Mat mask = Mat::zeros(imageLab.size(), CV_8UC1);

    cout << "imageLab.size()" << imageLab.size() << endl;

    vector<int> labels = {0};
    vector<History> historyVector;
    auto iHistory = History(mask, labels);
    historyVector.push_back(iHistory);
    auto &stats = History::imageStatsMap;

    MatTools::meanCovariance(imageLab, mask, stats, labels);

    printImage(imageLab, name);
    showImage(image, name);

    auto thresholding = Thresholding(imageLab);

    for (int i = 0; i < 3; ++i) {
        cout << "Level: " << i + 1 << endl;

        if (labels.empty()) {
            break;
        }
         vector<int> nextLabels = thresholding.propagate(mask, labels);

        // print labels
        cout << "Labels: ";
        for (const auto &itemLabels: nextLabels) {
            cout << itemLabels << " ";
        }
        cout << endl;

        iHistory = History(mask, nextLabels);
        historyVector.push_back(iHistory);

        labels = nextLabels;
    }

    for (const auto &itemHistoryVector: historyVector) {
        Mat m = itemHistoryVector.mask;
        Mat imageLabThr = imageLab.clone();
        auto itImage = imageLabThr.begin<Vec3f>();
        auto itMask = m.begin<uchar>();
        auto itEnd = m.end<uchar>();
        while (itMask != itEnd) {
            auto imageStatsClassI = History::imageStatsMap[*itMask];
            (*itImage)[0] = 29.0;
            (*itImage)[1] = imageStatsClassI.mean.a;
            (*itImage)[2] = imageStatsClassI.mean.b;
            itImage++;
            itMask++;
        }

        Mat imageThr;
        cvtColor(imageLabThr, imageThr, COLOR_Lab2BGR);
        imageThr *= 255.0;
        imageThr.convertTo(imageThr, CV_8UC3);

        showImage(imageThr, "Thresholding");
    }

    return 0;
}
