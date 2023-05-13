//
// Created by dayan3847 on 3/8/23.
//

#include "Histogram.h"
#include "iostream"

using namespace std;

namespace histogram {

    void Histogram::histogram(Mat &image, Mat &histogram) {
        histogram = Mat::zeros(1, 256, CV_32SC1);
        for (int i = 0; i < image.rows; ++i) {
            for (int j = 0; j < image.cols; ++j) {
                unsigned char pixel = image.at<unsigned char>(i, j);
                histogram.at<int>(pixel)++;
            }
        }
    }

    void Histogram::histogramUsingIterator(Mat &image, Mat &histogram) {
        // histograma
        histogram = Mat::zeros(1, 256, CV_32SC1);

        // iteradores
        MatIterator_<int> it = image.begin<int>();
        MatIterator_<int> end = image.end<int>();   // end es el final del histograma
        // recorremos la imagen
        while (it != end) {
            // obtenemos el valor del pixel
            // unsigned char pixel = image.at<unsigned char>(it.pos());
            unsigned char pixel = *it;
            // incrementamos el valor del histograma
            histogram.at<int>(pixel)++;
            // avanzamos el iterador
            it++;
        }
    }

    void Histogram::show(Mat histogram) {
        // Show the histogram
        for (int i = 0; i < 256; ++i) {
            cout << "[" << i << "->" << histogram.at<int>(i) << "]";
        }
        cout << endl;
    }

    void Histogram::test(Mat &image) {

        // histograma
        Mat histogram;

        // calculamos el histograma
        histogramUsingIterator(image, histogram);

        // mostramos el histograma
        for (int i = 0; i < 256; ++i) {
            cout << i << " -> " << histogram.at<int>(i) << endl;
        }

    }
} // histogram