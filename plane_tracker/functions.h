//
// Created by dayan3847 on 5/21/23.
//

#ifndef CHESSBOARD_CAMERA_CALIBRATION_FUNCTIONS_H
#define CHESSBOARD_CAMERA_CALIBRATION_FUNCTIONS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "tools.h"
#include "config.h"

namespace my_functions
{

	void getOriginalCorners(cv::Size& size, double squareSize, std::vector<cv::Point3f>& outCorners, bool center = true)
	{
		double initHeight = 0;
		double initWidth = 0;
		if (center)
		{
			initWidth = (size.width - 1.) / 2 * squareSize * -1;
			initHeight = (size.height - 1.) / 2 * squareSize * -1;
		}
		for (int j = 0; j < size.height; ++j)
		{
			double y = initHeight + j * squareSize;
			for (int i = 0; i < size.width; ++i)
			{
				double x = initWidth + i * squareSize;

				outCorners.emplace_back(x, y, 0.);
			}
		}
	}

	void getOriginalCorners(cv::Size& size, double squareSize, cv::Mat& outCorners, bool center = true)
	{
		std::vector<cv::Point3f> outCornersVector;
		getOriginalCorners(size, squareSize, outCornersVector, center);
		my_tools::convertVecPointToMat(outCornersVector, outCorners);
	}

//	void get_iK_OriginalCorners(cv::Size &size, double squareSize, cv::Mat &outCorners, bool center = true)
//	{
//		cv::Mat originalCornersM;
//		getOriginalCorners(size, squareSize, originalCornersM, center);
//		cv::Mat iK = my_config::iK;
//		originalCornersM.pop_back();
//		outCorners = iK * originalCornersM;
//		// add row of ones
//		outCorners.push_back(cv::Mat::ones(1, outCorners.cols, CV_64F));
//	}
//
//	void get_iK_OriginalCorners(cv::Size &size,
//		double squareSize,
//		std::vector<cv::Point3f> &outCorners,
//		bool center = true)
//	{
//		cv::Mat iK_originalCornersM;
//		get_iK_OriginalCorners(size, squareSize, iK_originalCornersM, center);
//		my_tools::convertMatToVecPoint(iK_originalCornersM, outCorners);
//	}

	void buildTransformationMatrix(const cv::Mat& R, const cv::Mat& T, cv::Mat& G)
	{
		CV_Assert(R.rows == 3 && R.cols == 3 && T.rows == 3 && T.cols == 1);

		G = cv::Mat(4, 4, CV_64F, cv::Scalar(0));

		R.copyTo(G(cv::Rect(0, 0, 3, 3)));
		T.copyTo(G(cv::Rect(3, 0, 1, 3)));
		G.at<double>(3, 0) = 0.;
		G.at<double>(3, 1) = 0.;
		G.at<double>(3, 2) = 0.;
		G.at<double>(3, 3) = 1.;
	}

	void proj(cv::Mat& u, cv::Mat& v, cv::Mat& pv)
	{
		pv = u.dot(v) * u / u.dot(u);
	}

	void gramSchmidtOrthogonalizationMethod(cv::Mat& H)
	{
		cv::Mat v1, v2, v3, u[3];

		v1 = H(cv::Rect(0, 0, 1, 3));
		v2 = H(cv::Rect(1, 0, 1, 3));
		v3 = H(cv::Rect(2, 0, 1, 3));
		u[0] = v1;
		proj(u[0], v2, u[1]);
		u[1] = v2 - u[1];
		proj(u[0], v3, v1);
		proj(u[1], v3, v2);
		u[2] = v3 - v1 - v2;

		u[0] = u[0] / sqrt(u[0].dot(u[0]));
		u[1] = u[1] / sqrt(u[1].dot(u[1]));
		u[2] = u[2] / sqrt(u[2].dot(u[2]));
		cv::hconcat(u, 3, H);
	}

	void homogenous2Cartesian(cv::Mat& matPoint)
	{
		for (int i = 0; i < matPoint.cols; ++i)
		{
			double val = matPoint.at<double>(2, i);
			matPoint.at<double>(0, i) /= val;
			matPoint.at<double>(1, i) /= val;
		}
	}

	void drawAxes(cv::Mat& frame, const std::vector<cv::Point2f>& axisPixelVP)
	{
		cv::circle(frame, axisPixelVP[0], 10, cv::Scalar(0, 0, 0), 2);

		cv::line(frame, axisPixelVP[0], axisPixelVP[1], cv::Scalar(0, 0, 255), 2);
		cv::circle(frame, axisPixelVP[1], 10, cv::Scalar(0, 0, 255), 2);

		cv::line(frame, axisPixelVP[0], axisPixelVP[2], cv::Scalar(255, 0, 0), 2);
		cv::circle(frame, axisPixelVP[2], 10, cv::Scalar(255, 0, 0), 2);

		if (axisPixelVP.size() > 3)
		{
			cv::circle(frame, axisPixelVP[3], 10, cv::Scalar(0, 255, 0), 2);
			cv::line(frame, axisPixelVP[0], axisPixelVP[3], cv::Scalar(0, 255, 0), 2);
		}
	}

	void drawAxesWithH(cv::Mat& frame, cv::Mat& H)
	{
		cv::Mat axisMeterM = (cv::Mat_<double>(3, 3)
				<<
				0., -.1, 0., // x
				0., 0., -.1, // y
				1., 1., 1.   // 1
		);

		cv::Mat axisPixelM = my_config::K * H * axisMeterM;
		std::vector<cv::Point2f> axisPixelVP;
		my_tools::convertMatToVecPoint(axisPixelM, axisPixelVP);

		drawAxes(frame, axisPixelVP);
	}

	void drawAxesWithG(cv::Mat& frame, cv::Mat& G)
	{
		cv::Mat axisMeterM = (cv::Mat_<double>(4, 4)
				<<
				0., -.1, 0., 0., // x
				0., 0., -.1, 0., // y
				0., 0., 0., -.1, // z
				1., 1., 1., 1.   // 1
		);

		cv::Mat K_I0 = my_config::K_I0;
		cv::Mat K_I0_G = K_I0 * G;

		cv::Mat axisPixelM = K_I0_G * axisMeterM;
		//	cv::Mat G_A = G * axisMeterM;
		//	cv::Mat I0_G_A = my_config::I0 * G_A;
		//	cv::Mat axisPixelM = my_config::K * I0_G_A;

		std::vector<cv::Point2f> axisPixelVP;
		my_tools::convertMatToVecPoint(axisPixelM, axisPixelVP);

		drawAxes(frame, axisPixelVP);
	}

	void predictG2(
			const cv::Mat& G0,
			const cv::Mat& G1,
			const cv::Mat& R1,
			const cv::Mat& T1,
			const std::vector<cv::Point3f>& cornersOriginalMeterVP,
			cv::Mat& frame
	)
	{
		if (!G0.empty())
		{
			double dt = my_config::deltaT;
			cv::Mat R0 = G0(cv::Rect(0, 0, 3, 3));
			cv::Mat T0 = G0(cv::Rect(3, 0, 1, 3));
			cv::Mat R1_prime = (R1 - R0) / dt;
			cv::Mat T1_prime = (T1 - T0) / dt;
			cv::Mat w = R1_prime * R1.t();
			cv::Mat v = T1_prime - (w * T1);
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

	void experimentSolvePnP(
			std::vector<cv::Point3f>& cornersOriginalMeterVP,
			std::vector<cv::Point2f>& cornersFoundPixelVP,
			cv::Mat& G,
			cv::Mat& frame,
			const bool& saveData = false
	)
	{
		//distCoeffs zeros
		cv::Mat _distCoeffs;

		cv::Mat _rVec, _t;
		// Resolver PnP
		cv::solvePnP(cornersOriginalMeterVP, cornersFoundPixelVP, my_config::K, _distCoeffs, _rVec, _t);

		// matrix de rotacion de 3x3
		cv::Mat _r;
		cv::Rodrigues(_rVec, _r);

		my_functions::buildTransformationMatrix(_r, _t, G);
		if (saveData)
		{
			my_tools::saveMatInTxt(_t, "f/_solvePnP_t");
			my_tools::saveMatInTxt(_r, "f/_solvePnP_r");
			my_tools::saveMatInTxt(G, "f/_solvePnP_g");
		}
		my_functions::drawAxesWithG(frame, G);
	}


	void experimentG0G1G01(
			const std::vector<cv::Point3f>& cornersOriginalMeterVP,
			const cv::Mat& G0,
			const cv::Mat& G1
	)
	{
		if (!G0.empty())
		{
			cv::Mat cornersOriginalMeterM;
			my_tools::convertVecPointToMat(cornersOriginalMeterVP, cornersOriginalMeterM);
			std::cout << "cornersOriginalMeterM" << std::endl;
			my_tools::printMat(cornersOriginalMeterM.col(0), "cornersOriginalMeterM");
			cv::Mat X0 = G0 * cornersOriginalMeterM;
			my_tools::printMat(X0.col(0), "X0");
			cv::Mat X1 = G1 * cornersOriginalMeterM;
			my_tools::printMat(X1.col(0), "X1");
			cv::Mat G01 = G1 * G0.inv();
			cv::Mat X1_ = G01 * X0;
			my_tools::printMat(X1_.col(0), "X1_");
		}
	}

}

#endif //CHESSBOARD_CAMERA_CALIBRATION_FUNCTIONS_H
