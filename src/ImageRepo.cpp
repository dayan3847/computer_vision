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

void ImageRepo::arcoiris_3x3(Mat &image, Mat &imageOriginal) {

    // crear una imagen de 3x3 a color
    imageOriginal = Mat::zeros(3, 3, CV_8UC3);
    // poner el pixel 0,0 en rojo
    imageOriginal.at<Vec3b>(0, 0) = Vec3b(0, 0, 255);
    // poner el pixel 0,1 en verde
    imageOriginal.at<Vec3b>(0, 1) = Vec3b(0, 255, 0);
    // poner el pixel 0,2 en azul
    imageOriginal.at<Vec3b>(0, 2) = Vec3b(255, 0, 0);
    // poner el pixel 1,0 en amarillo
    imageOriginal.at<Vec3b>(1, 0) = Vec3b(0, 255, 255);
    // poner el pixel 1,1 en magenta
    imageOriginal.at<Vec3b>(1, 1) = Vec3b(255, 0, 255);
    // poner el pixel 1,2 en cyan
    imageOriginal.at<Vec3b>(1, 2) = Vec3b(255, 255, 0);
    // poner el pixel 2,0 en blanco
    imageOriginal.at<Vec3b>(2, 0) = Vec3b(255, 255, 255);
    // poner pixel 2,1 en naraja
    imageOriginal.at<Vec3b>(2, 1) = Vec3b(0, 165, 255);
    // poner pixel 2,1 en navy
    imageOriginal.at<Vec3b>(2, 2) = Vec3b(128, 0, 0);

    // Convert to float values.
    Mat imageFloat;
    imageOriginal.convertTo(imageFloat, CV_32FC3);
    // Normalize.
    imageFloat /= 255.0;
    // Convert to BGR2Lab.
    cvtColor(imageFloat, image, COLOR_BGR2Lab);
}
