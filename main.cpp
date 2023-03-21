#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "src/Thresholding.h"
#include "src/MatTools.h"

using namespace std;
using namespace cv;

int main() {
    cout << "Hello, World!" << endl;

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
    Mat mask = Mat::ones(imageLab.size(), CV_8UC1);

    cout << "imageLab.size()" << imageLab.size() << endl;

    ImageStats imageStats = matTools.meanCovariance(imageLab, mask, 2);
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


    int l = matTools.divideClass(mask, 1);

    ImageStats imageStatsClassA = matTools.meanCovariance(imageLab, mask, l);
    ImageStats imageStatsClassB = matTools.meanCovariance(imageLab, mask, l + 1);

    int label = 0;
    for (int i = 0; i < imageLab.rows; ++i) {
        for (int j = 0; j < imageLab.cols; ++j) {
            // Get pixel.
            Vec3f pixel = imageLab.at<Vec3f>(i, j);
            float a = pixel[1];
            float b = pixel[2];
            // Calculate distance.
            double distance = matTools.distanceMahalanobisNormalized(a, b, imageStats);

        }

    }


    imshow(name, image);
    waitKey(0);
    destroyWindow(name);

//    Thresholding thresholding = Thresholding();
//    double optimalThreshold = thresholding.optimalThreshold(image);
//    cout << "Optimal threshold: " << optimalThreshold << endl;
    return 0;
}
