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
	void analiceFrame(cv::Mat& frame,
			std::vector<cv::Point3f>& cornersOriginalMeterVP,
			cv::Mat& G1,
			cv::Mat const& G0,
			const bool& saveData = false)
	{
		cv::Size patternSize = my_config::patternSize;
		// Step 3: Find Chessboard Corners
		std::cout << "Step 3: Find Chessboard Corners" << std::endl;
		// Corners found in the image
		std::vector<cv::Point2f> cornersFoundPixelVP;
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

		std::vector<cv::Point2f> cornersFountMeterVP;
		my_tools::convertMatToVecPoint(cornersFountMeterM, cornersFountMeterVP);


		// Step 4: Calculate Homography (H matrix)
		std::cout << "Step 4: Calculate Homography (H matrix)" << std::endl;
		cv::Mat H = cv::findHomography(cornersOriginalMeterVP, cornersFountMeterVP);

		// Experimento H
		{
			my_functions::drawAxesWithH(frame, H);
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

		cv::Mat T = (cv::Mat_<double>(3, 1)
				<<
				H.at<double>(0, 2),
				H.at<double>(1, 2),
				H.at<double>(2, 2)
		);
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

		// Step 8: Calculate G1 matrix
		my_functions::buildTransformationMatrix(R, T, G1);
		// Print G1 matrix
		my_tools::printMat(G1, "G1");
		if (saveData)
		{
			my_tools::saveMatInTxt(G1, "f/G1");
		}

		// Experiment G1
		{
//			my_functions::drawAxesWithG(frame, G1);
		}

		// Experiment solvePnP
		{
			//distCoeffs zeros
			cv::Mat _distCoeffs;

			cv::Mat _rVec, _t;
			// Resolver PnP
			cv::solvePnP(cornersOriginalMeterVP, cornersFoundPixelVP, my_config::K, _distCoeffs, _rVec, _t);

			// matrix de rotacion de 3x3
			cv::Mat _r;
			cv::Rodrigues(_rVec, _r);

			cv::Mat _g;
			my_functions::buildTransformationMatrix(_r, _t, _g);
			if (saveData)
			{
				my_tools::saveMatInTxt(_t, "f/_solvePnP_t");
				my_tools::saveMatInTxt(_r, "f/_solvePnP_r");
				my_tools::saveMatInTxt(_g, "f/_solvePnP_g");
			}
			my_functions::drawAxesWithG(frame, _g);
			G1 = _g;
		}

		if (!G0.empty())
		{
			cv::Mat R1 = R;
			cv::Mat T1 = T;
			double dt = my_config::deltaT;
			cv::Mat R0 = G0(cv::Rect(0, 0, 3, 3));
			cv::Mat T0 = G0(cv::Rect(3, 0, 1, 3));
			cv::Mat R1_prime = (R1 - R0) / dt;
			cv::Mat T1_prime = (T1 - T0) / dt;
			cv::Mat w = R1_prime * R.t();
			cv::Mat v = T1_prime - w * T;
			cv::Mat Xi1;
			cv::hconcat(w, v, Xi1);
			cv::vconcat(
					Xi1,
					cv::Mat::zeros(1, 4, CV_64F),
					Xi1
			);

			cv::Mat G01 = G1 * G0.inv();
			cv::Mat I4x4 = cv::Mat::eye(4, 4, CV_64F);
			cv::Mat G12 = (I4x4 + Xi1) * G01 * dt;

			cv::Mat G2 = G12 * G1;

			{
				cv::Mat cornersOriginalMeterM;
				my_tools::convertVecPointToMat(cornersOriginalMeterVP, cornersOriginalMeterM);

				cv::Mat K_I0 = my_config::K_I0;
				cv::Mat K_I0_G2 = K_I0 * G2;
				cv::Mat cornersOriginalPixelM_2 = K_I0_G2 * cornersOriginalMeterM;

				cv::Mat list_x = cornersOriginalPixelM_2.row(0);
				cv::Mat list_y = cornersOriginalPixelM_2.row(1);

				double min_x, max_x, min_y, max_y;

				cv::minMaxLoc(list_x, &min_x, &max_x);
				cv::minMaxLoc(list_y, &min_y, &max_y);

				cv::rectangle(
						frame,
						cv::Point2d(min_x, min_y),
						cv::Point2d(max_x, max_y),
						cv::Scalar(0, 255, 0),
						2
				);
			}

		}

	}

	int keepTrack(cv::VideoCapture& videoCapture)
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

		std::vector<cv::Point3f> originalCornersVP;
		my_functions::getOriginalCorners(my_config::patternSize, my_config::squareSize, originalCornersVP, false);

		cv::Mat frame;
		unsigned int frameNumber = 0;

		cv::Mat G0;
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
			cv::Mat G1;
			analiceFrame(frame, originalCornersVP, G1, G0);
			G0 = G1;

			imshow(winName, frame);

			if (cv::waitKey(1) == 27) break;
		} while (true);

		videoCapture.release();
		cv::destroyWindow(winName);

		return 0;
	}

}

#endif //CHESSBOARD_CAMERA_CALIBRATION_PLANE_TRACKER_H
