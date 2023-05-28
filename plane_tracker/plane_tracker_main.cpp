#include <iostream>
#include <opencv2/opencv.hpp>
#include "tools.h"
#include "functions.h"
#include "config.h"

int myFindChessboardCorners(cv::VideoCapture &videoCapture)
{

	if (!videoCapture.isOpened())
	{
		std::cout << "Error al abrir la camara o el video" << std::endl;
		return -1;
	}
	int IM_WIDTH = 800, IM_HEIGHT = 600;
	double frmWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
	double frmHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
	double scaleX = IM_WIDTH / frmWidth;
	double scaleY = IM_HEIGHT / frmHeight;

	// delta t 30 fps
	double dt = 1. / 30;
	cv::Size patternSize = cv::Size(8, 6);
	cv::Mat K = my_config::K();
	cv::Mat iK = my_config::iK();
	cv::Mat I0 = my_config::I0();
	my_tools::printMat(I0, "I0");

	std::string winName = "Chessboard";;
	cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);

	std::vector<cv::Point3f> originalCorners;
	my_functions::getOriginalCorners(patternSize, 28.45e-3, originalCorners);

	cv::Mat originalCornersMat(originalCorners);
	my_tools::printMat(originalCornersMat, "originalCornersMat");

	std::vector<cv::Point3f> testCorners;
	auto s = cv::Size(3, 2);
	my_functions::getOriginalCorners(s, 1, testCorners, false);
	cv::Mat testCornersMat;
	my_tools::convertVecPointToMat(testCorners, testCornersMat);
	my_tools::printMat(testCornersMat, "testCornersMat");

	cv::Mat frame;
	std::vector<cv::Point2f> corners;
	do
	{
		// print current time
		std::cout << "current time is: "
				  << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())
				  << std::endl;

		// Step 2: Capture frame
		std::cout << "Step 2: Capture frame" << std::endl;
		videoCapture >> frame;
		if (frame.empty())
		{
			std::cout << "Error al capturar el frame" << std::endl;
			break;
		}
		// resize frame
		if (scaleX != 1. || scaleY != 1.)
		{
			resize(frame, frame, cv::Size(), scaleX, scaleY, cv::INTER_AREA);
		}

		// Step 3: Find Chessboard Corners
		std::cout << "Step 3: Find Chessboard Corners" << std::endl;
		bool patternWasFound = cv::findChessboardCorners(frame, patternSize, corners);
		// bool patternWasFound = cv::finhomogenous2CartesiandChessboardCorners(frame, patternSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH);
		// Draw Chessboard Corners
		if (patternWasFound)
		{
			drawChessboardCorners(frame, patternSize, corners, patternWasFound);

			// Draw point in red
			cv::circle(frame, cv::Point2f(500, 500), 5, cv::Scalar(0, 0, 255), 2);

			std::cout << corners.size() << std::endl;
			// Applying K matrix
			cv::Mat cornersMat, canonicalCorners;

			std::cout << "Corners Antes:" << corners << std::endl;

			my_tools::convertVecPointToMat(corners, cornersMat);

			std::cout << "Corners Mat:" << cornersMat << std::endl;

			canonicalCorners = iK * cornersMat;

			std::cout << "canonicalCorners:" << canonicalCorners << std::endl;

			my_functions::homogenous2Cartesian(canonicalCorners);

			std::cout << "homogeneous canonicalCorners:" << canonicalCorners << std::endl;

			my_tools::convertMatToVecPoint(canonicalCorners, corners);
			std::cout << "Corners Despues:" << corners << std::endl;

			// Step 4: Calculate Homography (H matrix)
			std::cout << "Step 4: Calculate Homography (H matrix)" << std::endl;
			cv::Mat H = cv::findHomography(originalCorners, corners);
//            cv::Mat H = cv::findHomography(corners, originalCorners);
			std::cout << "H: " << H << std::endl;

			// Step 5: Normalize H matrix
			std::cout << "Step 5: Normalize H matrix" << std::endl;
			H /= cv::norm(H.col(0));
			std::cout << "H: " << H << std::endl;

			// Step 5.5: Calculate the translation vector T
			std::cout << "Step 5.5: Calculate the translation vector T" << std::endl;
			cv::Mat T = H.col(2);
			// Print T matrix
			std::cout << "T: " << T << std::endl;

			// Step 6: Gram-Schmidt Orthogonalization Method
			std::cout << "Step 6: Gram-Schmidt Orthogonalization Method" << std::endl;
			my_functions::gramSchmidtOrthogonalizationMethod(H);

			// Print H matrix
			std::cout << "H: " << H << std::endl;

			// Step 6.5: Normalize r1 and r2
			// r1
			cv::Mat r1 = H.col(0);
			r1 /= cv::norm(r1);
			// r2
			cv::Mat r2 = H.col(1);
			r2 /= cv::norm(r2);

			// Step 7: Calculate the rotation matrix R
			std::cout << "Step 7: Calculate the rotation matrix R" << std::endl;
			cv::Mat R(3, 3, CV_64F);
			cv::Mat r3 = r1.cross(r2);
			r1.copyTo(R.col(0));
			r2.copyTo(R.col(1));
			r3.copyTo(R.col(2));
			// Print R matrix
			std::cout << "R: " << R << std::endl;

			// Step 8: Calculate G matrix
			cv::Mat G(4, 4, CV_64F, cv::Scalar(0));
			my_functions::buildTransformationMatrix(R, T, G);

			my_tools::printMat(G, "G");

		}

		imshow(winName, frame);

		if (cv::waitKey(1) == 27) break;
	} while (true);

	videoCapture.release();
	cv::destroyWindow(winName);

	return 0;
}

bool myIsInteger(const std::string &s)
{
	try
	{
		std::stoi(s);
		return true;
	}
	catch (const std::invalid_argument &ia)
	{
		return false;
	}
}

int main(int argc, char ** argv)
{
	std::cout << argc << std::endl;
	std::cout << argv[0] << std::endl;
	std::cout << argv[1] << std::endl;
	if (argc < 2)
	{
		std::cout << "You need to pass a parameter" << std::endl;
		return 1;
	}
	cv::VideoCapture videoCapture;
	std::string indexOrFilename = argv[1];

	if (myIsInteger(indexOrFilename))
	{
		videoCapture = cv::VideoCapture(std::stoi(indexOrFilename));
		if (argc > 3)
		{
			double newCapPropFrameWidth = std::stoi(argv[2]);
			double newCapPropFrameHeight = std::stoi(argv[3]);

			double oldCapPropFrameWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
			double oldCapPropFrameHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);

			videoCapture.set(cv::CAP_PROP_FRAME_WIDTH, newCapPropFrameWidth);
			videoCapture.set(cv::CAP_PROP_FRAME_HEIGHT, newCapPropFrameHeight);

			std::cout << "Changed frame width from " << oldCapPropFrameWidth << " to " << newCapPropFrameWidth
					  << std::endl;
			std::cout << "Changed frame height from " << oldCapPropFrameHeight << " to " << newCapPropFrameHeight
					  << std::endl;
		}
	}
	else
	{
		videoCapture = cv::VideoCapture(indexOrFilename);
	}

	myFindChessboardCorners(videoCapture);

	return 0;
}
