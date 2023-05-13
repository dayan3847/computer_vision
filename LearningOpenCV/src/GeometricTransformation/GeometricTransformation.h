//
// Created by dayan3847 on 1/03/23.
//

#ifndef LEARNINGOPENCV_GEOMETRICTRANSFORMATION_H
#define LEARNINGOPENCV_GEOMETRICTRANSFORMATION_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class GeometricTransformation {
public:
    // Homografias o colinealidad
    void translation(Mat &src, Mat &dst, double x, double y);

    void rotation(Mat &src, Mat &dst, double angle);

    void scaling(Mat &src, Mat &dst, double xScale, double yScale);

    void affine(Mat &src, Mat &dst, double a, double b, double c);
};


#endif //LEARNINGOPENCV_GEOMETRICTRANSFORMATION_H
