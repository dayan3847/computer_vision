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

	void getOriginalCorners(cv::Size &size, double squareSize, std::vector<cv::Point3d> &outCorners, bool center = true)
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

	void getOriginalCorners(cv::Size &size, double squareSize, cv::Mat &outCorners, bool center = true)
	{
		std::vector<cv::Point3d> outCornersVector;
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
//		std::vector<cv::Point3d> &outCorners,
//		bool center = true)
//	{
//		cv::Mat iK_originalCornersM;
//		get_iK_OriginalCorners(size, squareSize, iK_originalCornersM, center);
//		my_tools::convertMatToVecPoint(iK_originalCornersM, outCorners);
//	}

	void buildTransformationMatrix(const cv::Mat &R, const cv::Mat &T, cv::Mat &G)
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

	void proj(cv::Mat &u, cv::Mat &v, cv::Mat &pv)
	{
		pv = u.dot(v) * u / u.dot(u);
	}

	void gramSchmidtOrthogonalizationMethod(cv::Mat &H)
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

	void homogenous2Cartesian(cv::Mat &matPoint)
	{
		int i;
		double val;
		for (i = 0; i < matPoint.cols; ++i)
		{
			val = matPoint.at<double>(2, i);
			matPoint.at<double>(0, i) /= val;
			matPoint.at<double>(1, i) /= val;
		}
	}

}

#endif //CHESSBOARD_CAMERA_CALIBRATION_FUNCTIONS_H
