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
    Mat mask = Mat::ones(imageFloat.size(), CV_8UC1);
    Mat mean, covariance;
    matTools.meanCovariance(imageLab, mask, mean, covariance);

    cout << "Mean: " << mean << endl;
    cout << "Covariance: " << covariance << endl;

    cout << "Image: \"" << name << "\" (" << image.rows << "x" << image.cols << ")" << endl;

    imshow(name, image);
    waitKey(0);
    destroyWindow(name);

//    Thresholding thresholding = Thresholding();
//    double optimalThreshold = thresholding.optimalThreshold(image);
//    cout << "Optimal threshold: " << optimalThreshold << endl;
    return 0;
}
