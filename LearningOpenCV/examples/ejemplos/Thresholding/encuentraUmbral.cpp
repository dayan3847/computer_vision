#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <cstring>
#include "histograma.h"
#include "gaussianIntersection.h"

using namespace std;
using namespace cv;

/*
Encuentra el umbral óptimo de una imagen.
*/
double umbralOptimo (Mat & I, size_t limite=15)
{
   int i, j;
   double umUp, umDown, um, umOld;
   unsigned int cont, contUp, contDown;
   bool corre;
   Scalar val;

   val = mean(I);
   um = val[0];
   cont = 0;
   corre = true;
   while (corre)
   {
     umUp = umDown = 0;
     contUp = contDown = 0;
     for (i = 0; i < I.rows; ++i)
     {
        unsigned char *ptr = I.ptr < unsigned char > (i);
        for (j = 0; j < I.cols; ++j, ++ptr)
           if (*ptr > um)
           {
             umUp += *ptr;
             contUp++;
           }
           else
           {
             umDown += *ptr;
             contDown++;
           }
      }

      umUp /= contUp;
      umDown /= contDown;
      umOld = um;
      um = (umUp+umDown)/2;
      cont++;
      if (um == umOld || cont>limite)
        corre = false;
      #ifdef VERBOSE
      cout << "Umbral Up   = " << umUp << endl;
      cout << "Umbral Down = " << umDown << endl;
      cout << "Diff.Umbral = " << umOld - um << endl;
      cout << "Umbral      = " << um << endl;
      cout << "cont        = " << cont << endl << endl;
      #endif
   }
   return um;
}

double umbralIdealHist(Mat &I, Mat &Out, unsigned int Limite, unsigned int seed = 23094)
{
  Mat H, Clases;
  bool bandera;
  unsigned int iteraciones, cambios;
  double m1, m2, s1, s2, d1, d2, x1, x2;
  unsigned char *apu, *fin, oldC;
  int *ptr, *end;
  u_char *ptrC;

  Histo(I, H);

  srandom(seed);

  Clases=Mat::zeros(1, 256, CV_8UC1);
  //Inicializamos I con valores aleatorios.
  apu = Clases.ptr<unsigned char>(0);
  fin =  apu + 256;
  for (; apu < fin; ++apu)
    *apu = random() % 2;

  bandera = true;
  iteraciones = 0;
  while (bandera)
  {
    //Calculamos el valor promedio y desv. estandar. de cada clase.
    meanStdHist(H, Clases, m1, s1, 0);
    meanStdHist(H, Clases, m2, s2, 1);

    ptr = H.ptr<int>(0);
    end = ptr + 256;
    ptrC = Clases.ptr<u_char>(0);
    for (cambios = 0; ptr < end; ++ptr, ++ptrC)
    {
      d1 = (*ptr-m1)/s1;
      d1 *= d1;
      d2 = (*ptr-m2)/s2;
      d2 *= d2;

      oldC = *ptrC;
      if (d1 < d2)
        *ptrC = 0;
      else
        *ptrC = 1;
      if (oldC != *ptrC)
        cambios++;
    }
    iteraciones++;
    if (!cambios || iteraciones > Limite)
      bandera = false;
  }
  gaussianIntersection(m1, s1, m2, s2, x1, x2);
  if (x1 >= m1 && x2 <= m2)
    return x1;
  return x2;
}

int main (int argc, char **argv)
{
   Mat I, Ium2, Ium;
   double thr, thrOtsu;
   char nombre[256];
   int key;

   if (argc < 2)
   {
      cerr << "Se necesita pasar el nombre de un archivo"
         << " que contenga una imagen." << endl;
      exit (0);
   }

   strncpy (nombre, argv[1], 255);

   I = imread (nombre, IMREAD_GRAYSCALE);

   thr = umbralOptimo (I);
   threshold(I, Ium, (int)thr, 255, THRESH_BINARY);
   thrOtsu = threshold(I, Ium2, 0, 255, THRESH_OTSU);
   namedWindow ("Imagen");
   namedWindow ("Imagen Umbralizada");

   cout << "El umbral óptimo es                   " << thr << endl;
   cout << "El umbral óptimo de acuerdo a Otsu es " << thrOtsu << endl;
   do
   {
      imshow ("Imagen", I);
      imshow ("Imagen Umbralizada", Ium);

      key = waitKeyEx (1);
   }
   while (toupper ((char) key) != 'Q');

   destroyAllWindows ();
   return 0;
}
