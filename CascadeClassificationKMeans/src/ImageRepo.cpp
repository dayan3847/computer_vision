//
// Created by dayan3847 on 3/28/23.
//

#include "ImageRepo.h"

void ImageRepo::byName(Mat &image, Mat &imageOriginal, const string &name) {
    // Read image.
    imageOriginal = imread(name);
    // Convert to float values.
    Mat imageFloat;
    imageOriginal.convertTo(imageFloat, CV_32FC3);
    // Normalize.
    imageFloat /= 255.0;
    // Convert to BGR2Lab.
    cvtColor(imageFloat, image, COLOR_BGR2Lab);
}

void ImageRepo::defaultImage(Mat &image, Mat &imageOriginal) {
    imageOriginal = Mat::zeros(3, 3, CV_8UC3);
    imageOriginal.at<Vec3b>(0, 0) = Vec3b(0, 0, 255);
    imageOriginal.at<Vec3b>(0, 1) = Vec3b(0, 255, 0);
    imageOriginal.at<Vec3b>(0, 2) = Vec3b(255, 0, 0);
    imageOriginal.at<Vec3b>(1, 0) = Vec3b(0, 255, 255);
    imageOriginal.at<Vec3b>(1, 1) = Vec3b(255, 0, 255);
    imageOriginal.at<Vec3b>(1, 2) = Vec3b(255, 255, 0);
    imageOriginal.at<Vec3b>(2, 0) = Vec3b(255, 255, 255);
    imageOriginal.at<Vec3b>(2, 1) = Vec3b(0, 165, 255);
    imageOriginal.at<Vec3b>(2, 2) = Vec3b(128, 0, 0);
    // Convert to float values.
    Mat imageFloat;
    imageOriginal.convertTo(imageFloat, CV_32FC3);
    // Normalize.
    imageFloat /= 255.0;
    // Convert to BGR2Lab.
    cvtColor(imageFloat, image, COLOR_BGR2Lab);
}

void ImageRepo::jaguarcito(Mat &image, Mat &imageOriginal) {
    string name = "img/jaguarcito.png";
    byName(image, imageOriginal, name);
}

void ImageRepo::corazon_10x10(Mat &image, Mat &imageOriginal) {
    string name = "img/corazon.png";
    byName(image, imageOriginal, name);
}

void ImageRepo::corazon_3x3(Mat &image, Mat &imageOriginal) {
    string name = "img/c_3x3.png";
    byName(image, imageOriginal, name);
}

void ImageRepo::arcoirisLab_3x3(Mat &image, Mat &imageOriginal) {
    // crear una imagen Lab de 3x3 a color
    image = Mat::zeros(3, 3, CV_8UC3);
    uchar l = 0;
    // poner pixel 0,0 en rojo
    image.at<Vec3b>(0, 0) = Vec3b(53, 80, 67);
    // poner pixel 0,1 en verde
    image.at<Vec3b>(0, 1) = Vec3b(l, 0, 255);
    // poner pixel 0,2 en azul
    image.at<Vec3b>(0, 2) = Vec3b(l, 255, 0);
    // poner pixel 1,0 en morado
    image.at<Vec3b>(1, 0) = Vec3b(l, 255, 64);
    image.at<Vec3b>(1, 1) = Vec3b(l, 128, 0);
    image.at<Vec3b>(1, 2) = Vec3b(l, 128, 128);
    image.at<Vec3b>(2, 0) = Vec3b(l, 128, 196);
    image.at<Vec3b>(2, 1) = Vec3b(l, 64, 255);
    image.at<Vec3b>(2, 2) = Vec3b(l, 255, 128);

    cvtColor(image, imageOriginal, COLOR_Lab2BGR);
    imageOriginal *= 255.0;
    imageOriginal.convertTo(imageOriginal, CV_8UC3);
}
