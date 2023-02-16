#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <ctype.h>
#include <cstring>

using namespace std;
using namespace cv;

void histogram(Mat &image, Mat &hist) {
    hist = Mat::zeros(1, 256, CV_32SC1);
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            unsigned char pixel = image.at<unsigned char>(i, j);
            hist.at<int>(pixel)++;
        }
    }
}

void histogram_iterator(Mat &image, Mat &hist) {
    hist = Mat::zeros(1, 256, CV_32SC1);
    Mat_<unsigned char>::iterator it = image.begin<unsigned char>();
    Mat_<unsigned char>::iterator fin = image.end<unsigned char>();
    while (it != fin) {
        hist.at<int>(*it)++;
        it++;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "Se necesita pasar el nombre de un archivo"
             << " que contenga una imagen."
             << endl;
        exit(0);
    }
    char name[256];
    strncpy(name, argv[1], 255);

    Mat image = imread(name, IMREAD_GRAYSCALE);

    cout << "Image " << name << endl;
    cout << "La imagen tiene " << image.rows << " renglones." << endl;
    cout << "La imagen tiene " << image.cols << " columnas." << endl;

    Mat hist;

//    histogram(image, hist);
    histogram_iterator(image, hist);

    for (int i = 0; i < 256; ++i) {
        cout << i << " -> " << hist.at<int>(i) << endl;
    }


    return 0;
}
