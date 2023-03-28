#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "src/Thresholding.h"
#include "src/MatTools.h"
#include "src/History.h"
#include "src/ImageRepo.h"

using namespace std;
using namespace cv;

void printMask(const Mat &mask) {
    cout << "Mask: " << endl;
    cout << "\t[ " << endl;
    for (int i = 0; i < mask.cols; ++i) {
        for (int j = 0; j < mask.rows; ++j) {
            int label = mask.at<uchar>(i, j);
            cout << "\t" << label << " ";
        }
        cout << endl;
    }

    cout << "\t] " << endl;

}


void showImage(Mat &image, const string &name, bool destroy = true) {
    Mat &imageToPrint = image;
    // resize without interpolation
//    resize(image, imageToPrint, Size(600, 600), 0, 0, INTER_NEAREST);
    imshow(name, imageToPrint);
    waitKey(0);
    if (destroy)
        destroyWindow(name);
}

void printImageByMask(const Mat &mask, const Mat &originalImage) {
    // create a new image L*a*b* with the same size of the mask
    Mat imageLabThr = Mat::zeros(mask.size(), CV_32FC3);
    auto itImageOriginal = originalImage.begin<Vec3f>();
    auto itImage = imageLabThr.begin<Vec3f>();
    auto itMask = mask.begin<uchar>();
    auto itEnd = mask.end<uchar>();
    while (itMask != itEnd) {
        auto label = *itMask;
        auto &pixel = *itImage;
        auto imageStatsClassI = History::imageStatsMap[label];
        pixel[0] = (*itImageOriginal)[0];
//        pixel[0] = imageStatsClassI.mean.l;
        pixel[1] = imageStatsClassI.mean.a;
        pixel[2] = imageStatsClassI.mean.b;
        itImageOriginal++;
        itImage++;
        itMask++;
    }

    Mat imageThr;
    cvtColor(imageLabThr, imageThr, COLOR_Lab2BGR);
    imageThr *= 255.0;
    imageThr.convertTo(imageThr, CV_8UC3);

    showImage(imageThr, "Thresholding");
}


void printImage(Mat &image, const string &name) {
    cout << "Image: " << name << endl;
    cout << "\tMatrix L:" << name << endl;
    cout << "\t[ " << endl;
    for (int i = 0; i < image.cols; ++i) {
        for (int j = 0; j < image.rows; ++j) {
            cout << "\t" << image.at<Vec3f>(i, j)[0];
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
    ImageRepo repo = ImageRepo();
    Mat image;
    Mat imageOriginal;
//    repo.arcoiris_3x3(image, imageOriginal);
    repo.jaguarcito(image, imageOriginal);
    // init mask with zeros.
    Mat mask = Mat::zeros(image.size(), CV_8UC1);

    cout << "image.size()" << image.size() << endl;
    // print image
//    printImage(imageLab, name);
    string name = "Original";
    showImage(imageOriginal, name, false);


    auto &stats = History::imageStatsMap;
    vector<int> labels = {0};
    MatTools::meanCovariance(image, mask, stats, labels);
    printMask(mask);
    printImageByMask(mask, image);

    auto thresholding = Thresholding(image);
    for (int i = 0; i < 20; ++i) {
        cout << "Level: " << i + 1 << endl;

        vector<int> nextLabels = thresholding.propagate(mask, labels);
        if (nextLabels.empty()) {
            break;
        }
        printMask(mask);
        printImageByMask(mask, image);

        labels = nextLabels;
    }

    return 0;
}
