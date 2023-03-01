#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    cout << "Hello, World!" << endl;

    Mat A = Mat::zeros(4, 4, CV_8UC1);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            A.at<unsigned char>(i, j) = 10 * i + 5 * j + 128;

    cout << "A = " << A << endl;
    return 0;
}
