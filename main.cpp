#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "src/Thresholding.h"

using namespace std;
using namespace cv;

int main() {
    cout << "Hello, World!" << endl;

    // Image
    string name = "img/jaguarcito.png";
    Mat image = imread(name, IMREAD_GRAYSCALE);
    cout << "Image: \"" << name << "\" (" << image.rows << "x" << image.cols << ")" << endl;

    imshow(name, image);
    waitKey(0);
    destroyWindow(name);

    Thresholding thresholding = Thresholding();
    double optimalThreshold = thresholding.optimalThreshold(image);
    cout << "Optimal threshold: " << optimalThreshold << endl;
    return 0;
}
