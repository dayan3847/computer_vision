#ifndef __HISTOGRAMA_
#define __HISTOGRAMA_

#include "opencv2/opencv.hpp"

using namespace cv;

void Histo(Mat &I, Mat &H);

void plotHisto(Mat &H, Mat &G);

size_t nPixeles(Mat &H);

void meanStdHist(Mat &H, double &mean, double &std);

void meanStdHist(Mat &H, Mat &Mask, double &mean, double &std, int value);

int minHist(Mat &H);

int maxHist(Mat &H);
#endif
