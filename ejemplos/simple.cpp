#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

using namespace std;

using namespace cv;

int main()
{
	Mat A;
	unsigned int i, j;

	A = Mat::zeros(4, 4, CV_8UC1);
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j)
			A.at<unsigned char>(i,j) = 128+i*10+j*5;

	cout << "A = " << A << endl;
	
	return 0;
}
