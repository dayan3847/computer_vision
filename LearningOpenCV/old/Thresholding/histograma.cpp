#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>

using namespace cv;

void Histo(Mat & I, Mat &H)
{
   int i, j;

   H = Mat::zeros(1, 256, CV_32SC1);

   for (i = 0; i < I.rows; ++i)
   {
      u_char *ptr = I.ptr < u_char > (i);
      for (j = 0; j < I.cols; ++j,++ptr)
         H.at<int>(0, *ptr)++;

   }
}

void plotHisto(Mat &H, Mat &G)
{
  int i, j, k, valor;

  double mn, mx, scale;

  minMaxLoc(H, &mn, &mx);
  scale = 250 / mx;
  G = Mat::zeros(256, 512, CV_8UC1);

  for (i = j = 0; i < 256; ++i, j += 2)
  {
     valor = (int)(scale * H.at<int>(0, i));
     for (k = 0; k < valor; k++)
         G.at<u_char>(255-k, j) = G.at<u_char>(255-k, j+1) = 255;
  }
}

size_t nPixeles(Mat &H)
{
  size_t acum;
  int *ptr, *end;

  ptr = H.ptr<int>(0);
  end = ptr + H.cols;
  for (acum = 0; ptr < end; ++ptr)
    acum += *ptr;
  return acum;
}

void meanStdHist(Mat &H, double &mean, double &std)
{
  size_t n, idx;
  double acum;
  int *ptr, *end;

  ptr = H.ptr<int>(0);
  end = ptr + H.cols;
  n = 0;
  for (acum = 0, idx = 0; ptr < end; ++ptr, ++idx)
  {
    n += *ptr; //Contamos cuantos pixeles hay.
    acum += *ptr * idx; //acumulamos los valores de cada pixel
  }
  mean = acum / n;

  ptr = H.ptr<int>(0);
  end = ptr + H.cols;
  for (acum = 0, idx = 0; ptr < end; ++ptr, ++idx)
    acum += *ptr * pow(idx - mean, 2);
  std = sqrt(acum/n);
}

void meanStdHist(Mat &H, Mat &Mask, double &mean, double &std, int value=0)
{
  size_t n, idx;
  double acum;
  int *ptr, *end;
  u_char *ptrM;

  ptr = H.ptr<int>(0);
  end = ptr + H.cols;
  ptrM = Mask.ptr<u_char>(0);
  n = 0;
  for (acum = 0, idx = 0; ptr < end; ++ptr, ++ptrM, ++idx)
  {
    if (*ptrM == value)
    {
      n += *ptr; //Contamos cuantos pixeles hay.
      acum += *ptr * idx; //acumulamos los valores de cada pixel
    }
  }
  mean = acum / n;

  ptr = H.ptr<int>(0);
  end = ptr + H.cols;
  ptrM = Mask.ptr<u_char>(0);
  for (acum = 0, idx=0; ptr < end; ++ptr, ++ptrM, ++idx)
    if (*ptrM == value)
      acum += *ptr * pow(idx - mean, 2);

  std = sqrt(acum/n);
}

int minHist(Mat &H)
{
  int idx;

  idx = 0;
  while (H.at<int>(idx) == 0 && idx < H.cols)
    idx++;
  if (idx == H.cols)
    idx = -1; //Excepcion. El histograma no tiene pixeles.
  return idx;
}

int maxHist(Mat &H)
{
  int idx;

  idx = 255;
  while (H.at<int>(idx) == 0 && idx >= 0)
    idx--;

  return idx;
}
