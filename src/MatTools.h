//
// Created by dayan3847 on 3/18/23.
//

#ifndef CASCADECLASSIFICATIONKMEANS_MATTOOLS_H
#define CASCADECLASSIFICATIONKMEANS_MATTOOLS_H

#include <vector>
#include "opencv2/opencv.hpp"
#include "ImageStats.h"

using namespace cv;
using namespace std;

class MatTools {
public:

    /**
     * Calcula la media de una imagen
     *
     * @param image imagen en formato BGR2Lab
     * @param mask la mascara que tiene los labels
     * @param stats el diccionario donde se van a guardar los resultados
     * @param labels los labels que se van a calcular
     *
     * @return {int} 0 ok, -1 si labels esta vacio
     */
    static int mean(Mat &image, Mat &mask, map<int, ImageStats> &stats, vector<int> &labels);

    /**
     * Calcula la media y la matriz de covarianza de una imagen
     *
     * @param image imagen en formato BGR2Lab
     * @param mask la mascara que tiene los labels
     * @param stats el diccionario donde se van a guardar los resultados
     * @param labels los labels que se van a calcular
     * @param covariance {true} calculate covariance matrix
     *                   {false} calculate only mean (covariance matrix is identity)
     *
     * @return int 0 ok, -1 si labels esta vacio
     */
    static int
    meanCovariance(Mat &image, Mat &mask, map<int, ImageStats> &stats, vector<int> &labels, bool covariance = true);

    /**
     * Distance Mahalanobis Normalized
     *
     * @param a
     * @param b
     * @param imageStats
     *
     * @return
     */
    static double distanceMahalanobisNormalized(double a, double b, ImageStats imageStats);

};

#endif //CASCADECLASSIFICATIONKMEANS_MATTOOLS_H
