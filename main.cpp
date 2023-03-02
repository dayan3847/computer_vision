#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "src/Thresholding.h"
#include "src/GeometricTransformation.h"

using namespace std;
using namespace cv;



int main() {
    Mat image = imread("images/lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    GeometricTransformation geometricTransformation = GeometricTransformation();



    Thresholding thresholding = Thresholding();
    thresholding.helloWorld();
    Mat a = Mat::zeros(4, 4, CV_8UC1);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            a.at<unsigned char>(i, j) = 128 + 10 * i + 5 * j;

    cout << "a = " << a << endl;

    return 0;
}
