#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "src/Thresholding/Thresholding.h"
#include "src/GeometricTransformation/GeometricTransformation.h"
#include "src/Histogram/Histogram.h"

using namespace std;
using namespace cv;
using namespace histogram;


int main() {
//    Mat image = imread("images/lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//    GeometricTransformation geometricTransformation = GeometricTransformation();


    // Thresholding
    Thresholding thresholding = Thresholding();
    thresholding.helloWorld();
    Mat a = Mat::zeros(4, 4, CV_8UC1);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            a.at<unsigned char>(i, j) = 128 + 10 * i + 5 * j;

    cout << "a = " << a << endl;

    // Image
    string name = "./img/Jaguarcito1.png";
    Mat image = imread(name, IMREAD_GRAYSCALE);

    cout << "Image " << name << endl;
    cout << "La imagen tiene " << image.rows << " renglones." << endl;
    cout << "La imagen tiene " << image.cols << " columnas." << endl;

    // Histogram
    Histogram histogram = Histogram();
    Mat matHistogram;

    // Calculate the histogram
    histogram.histogram(image, matHistogram);
    // Show the histogram
    histogram.show(matHistogram);

    // Calculate the histogram using iterator
    histogram.histogramUsingIterator(image, matHistogram);
    // Show the histogram
    histogram.show(matHistogram);

    // example 2
    int cont = 0;
    int key;
    int inc = 1;
    do {
        imshow("image", image);
        image = image + inc;
        cont = cont + inc;
        if (cont > 50 || cont < -50)
            inc = -inc;
        key = waitKeyEx(1);
    } while (toupper((char) key) != 'Q');
    destroyWindow("image");

//    // example 1
//    Mat A;
//    unsigned int i, j;
//
//    A = Mat::zeros(4, 4, CV_8UC1);
//    for (i = 0; i < 4; ++i)
//        for (j = 0; j < 4; ++j)
//            A.at<unsigned char>(i,j) = 128+i*10+j*5;
//
//    cout << "A = " << A << endl;

    return 0;
}
