//
// Created by dayan3847 on 1/03/23.
//

#include "GeometricTransformation.h"
#include "iostream"

using namespace std;

void GeometricTransformation::rotation(Mat &src, Mat &dst, double angle) {
    // transformation matrix
    Mat transformationMatrix = Mat::zeros(3, 3, CV_64FC1);
    transformationMatrix.at<double>(0, 0) = cos(angle);
    transformationMatrix.at<double>(0, 1) = -sin(angle);
    transformationMatrix.at<double>(1, 0) = sin(angle);
    transformationMatrix.at<double>(1, 1) = cos(angle);
    cout << "transformationMatrix = " << transformationMatrix << endl;
}

void GeometricTransformation::translation(Mat &src, Mat &dst, double x, double y) {
    // transformation matrix
}

void GeometricTransformation::affine(Mat &src, Mat &dst, double a, double b, double c) {
    // transformation matrix


}

void GeometricTransformation::scaling(Mat &src, Mat &dst, double xScale, double yScale) {
    // transformation matrix

}
