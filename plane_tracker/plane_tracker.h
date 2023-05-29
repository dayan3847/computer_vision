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
		std::vector<cv::Point3d> &cornersOriginalMeterVP,
		const std::string &winName,
		const bool &saveData = false)
	{
		cv::Size patternSize = my_config::patternSize;
		// Step 3: Find Chessboard Corners
		std::cout << "Step 3: Find Chessboard Corners" << std::endl;
		// Corners found in the image
		std::vector<cv::Point2d> cornersFoundPixelVP;
		bool patternWasFound = cv::findChessboardCorners(frame, patternSize, cornersFoundPixelVP);
		if (!patternWasFound)
			return;

		// Draw Chessboard Corners
		drawChessboardCorners(frame, patternSize, my_tools::covertVecPoint2f(cornersFoundPixelVP), true);

		cv::Mat cornersFountPixelM;
		my_tools::convertVecPointToMat(cornersFoundPixelVP, cornersFountPixelM);

		if (saveData)
		{
			my_tools::saveMatInTxt(cornersFountPixelM.t(), "f/corners_fount_pixel");
		}

		cv::Mat iK = my_config::iK;
		cv::Mat cornersFountMeterM = iK * cornersFountPixelM;

		if (saveData)
		{
			my_tools::saveMatInTxt(cornersFountMeterM.t(), "f/corners_fount_meter");
		}

		std::vector<cv::Point2d> cornersFountMeterVP;
		my_tools::convertMatToVecPoint(cornersFountMeterM, cornersFountMeterVP);


		// Step 4: Calculate Homography (H matrix)
		std::cout << "Step 4: Calculate Homography (H matrix)" << std::endl;
		cv::Mat H = cv::findHomography(cornersOriginalMeterVP, cornersFountMeterVP);

		// Experimento
		{
			std::cout << "puntoR 0,0 -> " << cornersOriginalMeterVP[0].x << " ; " << cornersOriginalMeterVP[0].y
					  << std::endl;
			std::cout << "puntoM 0,0 -> " << cornersFoundPixelVP[0].x << " ; " << cornersFoundPixelVP[0].y
					  << std::endl;
			cv::Mat zero_zero = (cv::Mat_<double>(3, 1)
				<<
				-.1, // x
				0., // y
				1.  // 1
			);

			std::cout << "norma r1: " << cv::norm(H.col(0)) << std::endl;
			std::cout << "norma r2: " << cv::norm(H.col(1)) << std::endl;
			std::cout << "norma T: " << cv::norm(H.col(2)) << std::endl;

			cv::Mat distortedPoint = my_config::K * H * zero_zero;

			cv::circle(frame, cornersFoundPixelVP[0], 10, cv::Scalar(0, 255, 0), 2);
			cv::circle(
				frame,
				cv::Point2d(
					distortedPoint.at<double>(0),
					distortedPoint.at<double>(1)
				),
				50,
				cv::Scalar(0, 0, 255), 2);
		}

		my_tools::printMat(H, "H");
		if (saveData)
		{
			my_tools::saveMatInTxt(H, "f/H_0_initial");
		}

		// Step 5: Normalize H matrix
		std::cout << "Step 5: Normalize H matrix" << std::endl;
		H /= cv::norm(H.col(0));
		my_tools::printMat(H, "H (normalized)");
		if (saveData)
		{
			my_tools::saveMatInTxt(H, "f/H_1_normalized");
		}

		// Step 5.5: Calculate the translation vector T
		std::cout << "Step 5.5: Calculate the translation vector T" << std::endl;
		cv::Mat T = H.col(2);
		// Print T matrix
		my_tools::printMat(T, "T");
		if (saveData)
		{
			my_tools::saveMatInTxt(T, "f/T");
		}


		// Step 6: Gram-Schmidt Orthogonalization Method
		std::cout << "Step 6: Gram-Schmidt Orthogonalization Method" << std::endl;
		my_functions::gramSchmidtOrthogonalizationMethod(H);

		// Print H matrix
		my_tools::printMat(H, "H (normalized and orthogonalized)");
		if (saveData)
		{
			my_tools::saveMatInTxt(H, "f/H_2_orthogonalized");
		}

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
		if (saveData)
		{
			my_tools::saveMatInTxt(R, "f/R");
		}

		// Step 8: Calculate G matrix
		cv::Mat G;
		my_functions::buildTransformationMatrix(R, T, G);
		// Print G matrix
		my_tools::printMat(G, "G");
		if (saveData)
		{
			my_tools::saveMatInTxt(G, "f/G");
		}

		cv::Mat K_I0 = my_config::K_I0;
		cv::Mat K_I0_G = K_I0 * G;

		cv::Mat axis3dMeterM = my_config::axisMeter;
		cv::Mat axis2dPixelM = K_I0_G * axis3dMeterM;
		if (saveData)
		{
			my_tools::saveMatInTxt(axis2dPixelM, "f/axis2dPixelM");
		}
		std::vector<cv::Point2d> axis2dPixelVP;
		my_tools::convertMatToVecPoint(axis2dPixelM, axis2dPixelVP);

//			cv::circle(frame, axis2dPixelVP[0], 10, cv::Scalar(0, 0, 255), 2);
//			cv::circle(frame, cv::Point2d(100, 200), 5, cv::Scalar(0, 255, 0), 2);
//			cv::circle(frame, cv::Point2d(200, 400), 5, cv::Scalar(0, 0, 255), 2);
	}

	int keepTrack(cv::VideoCapture &videoCapture)
	{
		if (!videoCapture.isOpened())
		{
			std::cerr << "Failed to open camera or video" << std::endl;
			return -1;
		}
//		int IM_WIDTH = 800, IM_HEIGHT = 600;
//		double frmWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
//		double frmHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
//		double scaleX = IM_WIDTH / frmWidth;
//		double scaleY = IM_HEIGHT / frmHeight;

		std::string winName = "Chessboard";
		cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);

		std::vector<cv::Point3d> originalCornersVP;
		my_functions::getOriginalCorners(my_config::patternSize, my_config::squareSize, originalCornersVP, false);

		cv::Mat frame;
		unsigned int frameNumber = 0;
		do
		{
			// print frame number in blue
			std::cout << "frame: " << "\033[34m" << ++frameNumber << "\033[0m" << std::endl;
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
//			// resize frame
//			if (scaleX != 1. || scaleY != 1.)
//			{
//				resize(frame, frame, cv::Size(), scaleX, scaleY, cv::INTER_AREA);
//			}
			// Save frame to file (test)
//			if (frameNumber == 50 || frameNumber == 347)
//			{
//				// save current frame to file
//				std::string filename = "./tests/data/frame_" + std::to_string(frameNumber) + ".jpg";
//				cv::imwrite(filename, frame);
////				break;
//			}

			analiceFrame(frame, originalCornersVP, winName);

			imshow(winName, frame);

			if (cv::waitKey(1) == 27) break;
		} while (true);

		videoCapture.release();
		cv::destroyWindow(winName);

		return 0;
	}

}

#endif //CHESSBOARD_CAMERA_CALIBRATION_PLANE_TRACKER_H
