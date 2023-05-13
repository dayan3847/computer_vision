//
// Created by dayan3847 on 3/8/23.
//

#ifndef LEARNINGOPENCV_HISTOGRAM_H
#define LEARNINGOPENCV_HISTOGRAM_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

namespace histogram {

    class Histogram {
    public:
        void histogram(Mat &image, Mat &histogram);

        // Histograma usando iteradores
        void histogramUsingIterator(Mat &image, Mat &histogram);

        void test(Mat &image);


        void show(Mat histogram);
    };

} // histogram

#endif //LEARNINGOPENCV_HISTOGRAM_H
