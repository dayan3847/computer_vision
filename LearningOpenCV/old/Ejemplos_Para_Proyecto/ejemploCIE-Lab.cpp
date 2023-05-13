#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;
using namespace cv;

/*!
\fn int MeanCov(Mat &image, Mat &Mask, Mat &mean, Mat &cov)

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

int MeanCov (Mat & image, Mat & Mask, Mat & mean, Mat & cov)
{
   float m[2], pm[2], Cv[3], icont;
   int cont;

   mean = Mat::zeros (2, 1, CV_32F);
   cov = Mat::zeros (2, 2, CV_32F);
   Mat_ < Vec3f >::iterator it, itEnd;
   Mat_ < uchar >::iterator itM;

   it = image.begin < Vec3f > ();
   itM = Mask.begin < uchar > ();
   itEnd = image.end < Vec3f > ();
   m[0] = m[1] = 0;
   memset (m, 0, 2 * sizeof (float));
   for (cont = 0; it != itEnd; ++it, ++itM)
   {
      if ((*itM))
      {
         m[0] += (*it)[1];      //Acumulamos el componente a de CIE-Lab
         m[1] += (*it)[2];      //Acumulamos el componente b de CIE-Lab
         cont++;
      }
   }

   if (!cont)
      return -1;
   m[0] /= cont;
   m[1] /= cont;
   mean = Mat (2, 1, CV_32F, m).clone ();

   if (cont < 2)
   {
      cov.at < float >(0, 0) = cov.at < float >(1, 1) =
         cov.at < float >(2, 2) = 1.;
      return -2;
   }
   it = image.begin < Vec3f > ();
   itM = Mask.begin < uchar > ();
   memset (Cv, 0, 3 * sizeof (float));
   for (; it != itEnd; ++it, ++itM)
   {
      if ((*itM))
      {
         pm[0] = (*it)[1] - m[0];
         pm[1] = (*it)[2] - m[1];
         Cv[0] += pm[0] * pm[0];
         Cv[1] += pm[1] * pm[1];
         Cv[2] += pm[0] * pm[1];
      }
   }
   icont = 1. / (cont - 1);
   Cv[0] *= icont;
   Cv[1] *= icont;
   Cv[2] *= icont;

   cov.at < float >(0, 0) = Cv[0];
   cov.at < float >(1, 1) = Cv[1];
   cov.at < float >(1, 0) = cov.at < float >(0, 1) = Cv[2];

   return cont;
}


int main (int argc, char **argv)
{
   Mat frame, fFrame, mMask, labFrame;
   Mat Mean, Cov, M;

   if (argc < 2)
   {
      cerr << "Falta Parámetro." << endl;
      cerr << "Uso: ejemploCIE-Lab nombre-de-archivo" << endl << endl;
      exit (1);
   }

   frame = imread (argv[1]);

   // Lo convertimos a valores flotantes.
   frame.convertTo (fFrame, CV_32FC3);
   // Es necesario normalizar la image BGR al intervalo [0,1]
   // antes de convertir a espacio CIE Lab.
   fFrame /= 255;
   cvtColor (fFrame, labFrame, COLOR_BGR2Lab);

   mMask = Mat::ones (fFrame.size (), CV_8UC1);
   MeanCov (labFrame, mMask, Mean, Cov);

   cout << endl
      << "El valor promedio de los componentes ab de la imagen son: ["
      << Mean.at < float >(0, 0) << ", " << Mean.at < float >(1,
                                                              0) << "]" <<
      endl << endl;
   cout << "La matriz de ccovarianza de las componentes ab de la imagen es:"
      << endl << "[" << Cov.at < float >(0, 0) << ", " << Cov.at < float >(0,
                                                                           1)
      << ";" << endl << Cov.at < float >(1, 0) << ", " << Cov.at < float >(1,
                                                                           1)
      << "]" << endl << endl;

   return 0;
}
