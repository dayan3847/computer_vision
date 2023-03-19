//
// Created by dayan3847 on 3/18/23.
//

#ifndef CASCADECLASSIFICATIONKMEANS_MATTOOLS_H
#define CASCADECLASSIFICATIONKMEANS_MATTOOLS_H

#include "opencv2/opencv.hpp"

using namespace cv;

class MatTools {
public:

    /**
     * Mean Covariance
     *
     * @param image
     * @param Mask
     * @param mean
     * @param cov
     * @return int
     *
\fn int meanCovariance(Mat &image, Mat &Mask, Mat &mean, Mat &cov)

\brief Esta funcion calcula la media y la matriz de covarianza de cada uno de los elementos de una matriz que representa una imagen a color.
\param image La imagen a la que se le va a calcular la media y la matriz de covarianza.
\param Mask Una matriz que binaria que se usa para determinar sobre que elementos de image se va a realizar el cómputo.
\param mean Una matriz de 2 renglones y 1 columna, en donde se regresa el vector promedio de los pixeles de la imagen.
\param mean Una matriz de 2 renglones y 2 columnas, en donde se regresa la matriz de covarianza de los pixeles de la imagen.
\return El número de elementos procesados. Regresa el valor -1 si el número de elementos a procesar es menor a 2.

Esta funcion calcula la media y la matriz de covarianza de cada uno de los elementos de una matriz que representa una imagen a color.
Como parámetro se recibe una matriz de mascara, del mismo tamaño que la imagen de entrada, con lo cual podemos controlar de manera fina
que elementos de la matriz de entrada se deben procesar. La funcion regresa el número de elementos procesados (que es el número de
elementos de la matriz de mascara diferentes a 0); si ese número es menor a 1, la funcion regresa el valor -1 para indicar un fallo,
y como no se puede calcular ni el vector promedio ni la matriz de covarianza los valores de los parámteros por referencia mean y cov
son indeterminados. Si el número de elementos procesado es igual a 1, el parametro por referencia mean es valido y contiene el valor del
elemento procesado, pero el parametro por referencia cov es indeterminado, y la funcion indica fallo regresando el valor -2.

*/
    int meanCovariance(Mat &image, Mat &Mask, Mat &mean, Mat &cov);

    /**
     * Distance Mahalanobis Normalized
     *
     */
    double distanceMahalanobisNormalized(double a, double b, double am, double bm, double s1, double s2, double s3);

};


#endif //CASCADECLASSIFICATIONKMEANS_MATTOOLS_H
