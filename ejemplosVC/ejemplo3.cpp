#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <ctype.h>
#include <cstring>

using namespace std;
using namespace cv;

/*
Encuentra el valor máximo de una imagen.
*/
template < typename X > X maximo (Mat & I)
{
   int i, j;
   X max;

   max = I.at < X > (0, 0);
   for (i = 0; i < I.rows; ++i)
   {
      X *ptr = I.ptr < X > (i);
      for (j = 0; j < I.cols; ++j, ++ptr)
         if (*ptr > max)
            max = *ptr;
   }
   return max;
}

/*
Encuentra el valor mínimo de una imagen.
*/
template < typename X > X minimo (Mat & I)
{
   int i, j;
   X min;

   min = I.at < X > (0, 0);
   for (i = 0; i < I.rows; ++i)
   {
      X *ptr = I.ptr < X > (i);
      for (j = 0; j < I.cols; ++j, ++ptr)
         if (*ptr < min)
            min = *ptr;
   }
   return min;
}

int main (int argc, char **argv)
{
   Mat I[4], Ir1, Ir2;
   char nombre[256];
   int cont, key, i, j;
   char inc;

   if (argc < 2)
   {
      cerr << "Se necesita pasar el nombre de un archivo"
         << " que contenga una imagen." << endl;
      exit (0);
   }

   strncpy (nombre, argv[1], 255);

   I[0] = imread (nombre);
   I[0].convertTo (I[1], CV_32FC3);
   cvtColor (I[0], I[2], COLOR_BGR2GRAY);
   cvtColor (I[1], I[3], COLOR_BGR2GRAY);

   Ir1 = I[2] (Rect (100, 100, 120, 60));
   Ir2 = I[2] (Rect (20, 20, 70, 50));
   for (i = 0; i < 4; ++i)
   {
      cout << "La imagen I[" << i << "] tiene " << I[i].rows 
           << " renglones." << endl;
      cout << "La imagen I[" << i << "] tiene " << I[i].cols
           << " columnas." << endl;
      cout << "La imagen I[" << i << "] tiene " << I[i].channels()
           << " canales." << endl;
      cout << "Cada elemento de la imagen I[" << i << "] tiene tamaño "
           << I[i].size () << endl;
      cout << "Cada elemento de la imagen I[" << i << "] tiene tipo "
           << I[i].type () << endl;
      cout << "Cada elemento de la imagen I[" << i
           << "] tiene un 'paso' igual a " << I[i].step
           << endl << endl;
   }

   namedWindow ("Imagen1");
   namedWindow ("Imagen2");
   namedWindow ("Imagen3");
   cont = 0;
   inc = 1;
   do
   {
      Mat Out;


      imshow ("Imagen1", I[2]);
      imshow ("Imagen2", Ir1);
      imshow ("Imagen3", Ir2);
      cout << "El valor Mínimo de I[3] es " 
           << minimo < float >(I[3]) << endl;
      cout << "El valor Máximo de I[3] es "
           << maximo < float >(I[3]) << endl;

      //Sumamos inc a cada pixel de la imagen.
      //I[2] = I[2] + inc;
      for (i = 0; i < I[2].rows; ++i)
         for (j = 0; j < I[2].cols; ++j)
            I[2].at < u_char >(i, j) =
         saturate_cast < u_char >(I[2].at < u_char >(i, j) + inc);

      for (i = 0; i < Ir1.rows; ++i)
      {
         u_char *ptr = Ir1.ptr < u_char >(i);
         for (j = 0; j < Ir1.cols; ++j, ++ptr)
            *ptr = saturate_cast < u_char >(*ptr + 2 * inc);
      }

      Mat_ < u_char >::iterator it, end;
      it = Ir2.begin < u_char >();
      end = Ir2.end < u_char >();
      for (; it != end; ++it)
         *it = saturate_cast < u_char >(*it - 2 * inc);

      cont = cont + inc;
      if (cont > 25 || cont < -25)
         inc = -inc;

      key = waitKeyEx (1);
   }
   while (toupper ((char) key) != 'Q');

   destroyAllWindows ();
   return 0;
}
