//
// Created by dayan3847 on 5/21/23.
//

#ifndef CHESSBOARD_CAMERA_CALIBRATION_TOOLS_H
#define CHESSBOARD_CAMERA_CALIBRATION_TOOLS_H

#include <iostream>
#include <opencv2/opencv.hpp>

namespace my_tools
{

	void printMat(const cv::Mat &mat, const std::string &name = "Mat")
	{
		std::cout << name << std::endl;
		for (int i = 0; i < mat.rows; i++)
		{
			for (int j = 0; j < mat.cols; j++)
				std::cout << mat.at<double>(i, j) << "\t";
			std::cout << std::endl;
		}
	}

	void convertVecPointToMat(const std::vector<cv::Point3f> &vecPoint, cv::Mat &matPoint)
	{
		int count = int(vecPoint.size());
		matPoint = cv::Mat(4, count, CV_64FC1);
		for (int i = 0; i < count; ++i)
		{
			matPoint.at<double>(0, i) = vecPoint[i].x;
			matPoint.at<double>(1, i) = vecPoint[i].y;
			matPoint.at<double>(2, i) = vecPoint[i].z;
			matPoint.at<double>(3, i) = 1.;
		}
	}

	void convertVecPointToMat(const std::vector<cv::Point2f> &vecPoint, cv::Mat &matPoint)
	{
		int count = int(vecPoint.size());

		matPoint = cv::Mat(3, count, CV_64FC1);
		for (int i = 0; i < count; ++i)
		{
			matPoint.at<double>(0, i) = vecPoint[i].x;
			matPoint.at<double>(1, i) = vecPoint[i].y;
			matPoint.at<double>(2, i) = 1.;
		}
	}

	void convertMatToVecPoint(const cv::Mat &matPoint, std::vector<cv::Point2f> &vecPoint)
	{
		int i;

		vecPoint.clear();
		for (i = 0; i < matPoint.cols; ++i)
			vecPoint.emplace_back(matPoint.at<double>(0, i), matPoint.at<double>(1, i));
	}

}

#endif //CHESSBOARD_CAMERA_CALIBRATION_TOOLS_H
