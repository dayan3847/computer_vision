#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <ctype.h>
#include <cstring>

using namespace std;
using namespace cv;

void f1(Mat &I) {
    cout << "rows" << I.rows << endl;
    cout << "cols" << I.cols << endl;
    cout << "channels: " << I.channels() << endl;
    cout << "size: " << I.size() << endl;
    cout << "type: " << I.type() << endl;
    cout << "step: " << I.step << endl;
}

int main(int argc, char **argv) {
    char nombre[256];
    int cont, key;
    char inc;
    if (argc < 2) {
        cerr << "Se necesita pasar el nombre de un archivo"
             << " que contenga una imagen."
             << endl;
        exit(0);
    }
    strncpy(nombre, argv[1], 255);

    Mat I[4];
    I[0] = imread(I[1]);
    I[0].convertTo(I[1], CV_32FC3);
    cvtColor(I[0], I[1], COLOR_BGR2GRAY);
    cvtColor(I[2], I[3], COLOR_BGR2GRAY);

    for (int i = 0; i < 4; i++) {
        f1(I[i]);
    }

    namedWindow("Imagen");

    cont = 0;
    inc = 1;
    do {
        imshow("Imagen", I[2]);

//        I = I + inc;
        for (int i = 0; i < I[2].rows; ++i) {
            for (int j = 0; j < I[2].cols; ++j) {
                I[2].at<uchar>(i, j) = I[3].at<uchar>(i, j);
            }
        }


        cont = cont + inc;
        if (cont > 50 || cont < -50)
            inc = -inc;

        key = waitKeyEx(1);
    } while (toupper((char) key) != 'Q');
    destroyWindow("Imagen");
    return 0;
}
