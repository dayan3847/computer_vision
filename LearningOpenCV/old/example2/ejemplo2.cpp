#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <ctype.h>
#include <cstring>

using namespace std;
using namespace cv;

int main (int argc, char **argv)
{
	Mat I;
  char nombre[256];
  int cont, key;
  char inc;

  if (argc < 2)
  {
    cerr << "Se necesita pasar el nombre de un archivo"
         << " que contenga una imagen."
         << endl;
    exit (0);
  }

  strncpy(nombre, argv[1], 255);

  I = imread(nombre, IMREAD_GRAYSCALE);
  cout << "La imagen tiene " << I.rows << " renglones." << endl;
  cout << "La imagen tiene " << I.cols << " columnas." << endl;
  namedWindow("Imagen");

  cont = 0;
  inc = 1;
  do
  {
    imshow("Imagen", I);
    I = I + inc;
    cont = cont + inc;
    if (cont > 50 || cont < -50)
      inc = -inc;

    key = waitKeyEx(1);
  } while (toupper((char)key) != 'Q');
  destroyWindow("Imagen");
	return 0;
}
