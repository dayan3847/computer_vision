//
// Created by dayan3847 on 5/21/23.
//

#ifndef CHESSBOARD_CAMERA_CALIBRATION_PLANE_TRACKER_H
#define CHESSBOARD_CAMERA_CALIBRATION_PLANE_TRACKER_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "config.h"
#include "functions.h"

namespace my_plane_tracker
{

	void analiceFrame(cv::Mat &frame,
		std::vector<cv::Point3f> &originalCornersVP,
		const cv::Size &patternSize,
		const std::string &winName,
		const bool &saveData = false)
	{
		// Draw point (tests)
		cv::circle(frame, cv::Point2f(100, 200), 5, cv::Scalar(0, 255, 0), 2);
		cv::circle(frame, cv::Point2f(200, 400), 5, cv::Scalar(0, 0, 255), 2);
		// Step 3: Find Chessboard Corners
		std::cout << "Step 3: Find Chessboard Corners" << std::endl;
		// Corners found in the image
		std::vector<cv::Point2f> cornersFoundVP;
		bool patternWasFound = cv::findChessboardCorners(frame, patternSize, cornersFoundVP);
		// bool patternWasFound = cv::findChessboardCorners(frame, patternSize, cornersFoundVP, cv::CALIB_CB_ADAPTIVE_THRESH);
		if (patternWasFound)
		{
			// Draw Chessboard Corners
			drawChessboardCorners(frame, patternSize, cornersFoundVP, true);

			cv::Mat cornersM;
			my_tools::convertVecPointToMat(cornersFoundVP, cornersM);

			if (saveData)
			{
				my_tools::saveMatInTxt(cornersM.t(), "f/iFrameCornersM");
			}

			cv::Mat iK = my_config::iK;
			cv::Mat iK_cornersM = iK * cornersM;

			if (saveData)
			{
				my_tools::saveMatInTxt(iK_cornersM.t(), "f/iFrame_iK_cornersM");
			}

			// Step 4: Calculate Homography (H matrix)
			std::cout << "Step 4: Calculate Homography (H matrix)" << std::endl;
			cv::Mat H = cv::findHomography(originalCornersVP, cornersFoundVP);

			my_tools::printMat(H, "H");

			// Step 5: Normalize H matrix
			std::cout << "Step 5: Normalize H matrix" << std::endl;
			H /= cv::norm(H.col(0));
			my_tools::printMat(H, "H (normalized)");

			// Step 5.5: Calculate the translation vector T
			std::cout << "Step 5.5: Calculate the translation vector T" << std::endl;
			cv::Mat T = H.col(2);
			// Print T matrix
			my_tools::printMat(T, "T");

			// Step 6: Gram-Schmidt Orthogonalization Method
			std::cout << "Step 6: Gram-Schmidt Orthogonalization Method" << std::endl;
			my_functions::gramSchmidtOrthogonalizationMethod(H);

			// Print H matrix
			my_tools::printMat(H, "H (normalized and orthogonalized)");

			// Step 6.5: Normalize r1 and r2
			// r1
			cv::Mat r1 = H.col(0);
			r1 /= cv::norm(r1);
			// r2
			cv::Mat r2 = H.col(1);
			r2 /= cv::norm(r2);
			// r3
			cv::Mat r3 = r1.cross(r2);
			// Step 7: Calculate the rotation matrix R
			std::cout << "Step 7: Calculate the rotation matrix R" << std::endl;
			cv::Mat R(3, 3, CV_64F);
			r1.copyTo(R.col(0));
			r2.copyTo(R.col(1));
			r3.copyTo(R.col(2));
			// Print R matrix
			my_tools::printMat(R, "R");

			// Step 8: Calculate G matrix
			cv::Mat G;
			my_functions::buildTransformationMatrix(R, T, G);
			// Print G matrix
			my_tools::printMat(G, "G");

			cv::Mat K_I0 = my_config::K_I0;
			cv::Mat K_I0_G = K_I0 * G;

			cv::Mat X3d = my_config::axis;

			cv::Mat X2d = K_I0_G * X3d;
			my_tools::saveMatInTxt(X2d.t(), "f/X2d");
		}

		imshow(winName, frame);
	}

	int keepTrack(cv::VideoCapture &videoCapture)
	{
		if (!videoCapture.isOpened())
		{
			std::cerr << "Failed to open camera or video" << std::endl;
			return -1;
		}
		int IM_WIDTH = 800, IM_HEIGHT = 600;
		double frmWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
		double frmHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
		double scaleX = IM_WIDTH / frmWidth;
		double scaleY = IM_HEIGHT / frmHeight;

		cv::Size patternSize = cv::Size(8, 6);

		std::string winName = "Chessboard";
		cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);

		std::vector<cv::Point3f> iK_originalCornersVP;
//		my_functions::get_iK_OriginalCorners(patternSize, 28.45e-3, iK_originalCornersVP);

		cv::Mat frame;
		unsigned int frameNumber = 0;
		do
		{
			// print frame number in blue
			std::cout << "frame: " << "\033[34m" << frameNumber++ << "\033[0m" << std::endl;
			// current time
			std::cout << "current time is: "
					  << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())
					  << std::endl;

			// Step 1: Capture frame
			std::cout << "Step 1: Capture frame" << std::endl;
			videoCapture >> frame;
			if (frame.empty())
			{
				std::cerr << "Error capturing the frame" << std::endl;
				break;
			}
			// resize frame
			if (scaleX != 1. || scaleY != 1.)
			{
				resize(frame, frame, cv::Size(), scaleX, scaleY, cv::INTER_AREA);
			}
			// Save frame to file (test)
			if (frameNumber == 50 || frameNumber == 347)
			{
				// save current frame to file
				std::string filename = "./../tests/data/frame_" + std::to_string(frameNumber) + ".jpg";
				cv::imwrite(filename, frame);
			}

			analiceFrame(frame, iK_originalCornersVP, patternSize, winName);

			if (cv::waitKey(1) == 27) break;
		} while (true);

		videoCapture.release();
		cv::destroyWindow(winName);

		return 0;
	}

}

#endif //CHESSBOARD_CAMERA_CALIBRATION_PLANE_TRACKER_H
