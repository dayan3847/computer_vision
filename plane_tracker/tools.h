//
// Created by dayan3847 on 5/21/23.
//

#ifndef CHESSBOARD_CAMERA_CALIBRATION_TOOLS_H
#define CHESSBOARD_CAMERA_CALIBRATION_TOOLS_H

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

namespace my_tools
{

	std::string matToString(const cv::Mat &mat, bool tab = false)
	{
		char s = tab ? '\t' : ' ';
		std::ostringstream stream;
		std::string matString;
		for (int i = 0; i < mat.rows; i++)
		{
			for (int j = 0; j < mat.cols; j++)
			{
				stream << mat.at<double>(i, j);
				matString += stream.str();
				if (j < mat.cols - 1)
					matString += s;
				stream.str("");
			}
			matString += "\n";
		}
		return matString;
	}

	void saveMatInTxt(const cv::Mat &mat, const std::string &name, const std::string &folder = "./tests/data/")
	{
		std::string matString = matToString(mat, false);
		std::ofstream originalCornersMatFile(folder + name + ".txt");
		originalCornersMatFile << matString;
		originalCornersMatFile.close();
	}

	void printMat(const cv::Mat &mat, const std::string &name = "Mat:")
	{
		std::cout << name << std::endl;
		std::string matString = matToString(mat, true);
		std::cout << matString << std::endl;
	}

	/**
	 * @param mat
	 * @param name
	 *
	 * @deprecated
	 */
	void printMat2(const cv::Mat &mat, const std::string &name = "Mat:")
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
		{
			double w = matPoint.at<double>(2, i);
			vecPoint.emplace_back(
				matPoint.at<double>(0, i) / w,
				matPoint.at<double>(1, i) / w
			);

		}
	}

	void convertMatToVecPoint(const cv::Mat &matPoint, std::vector<cv::Point3f> &vecPoint)
	{
		int i;

		vecPoint.clear();
		for (i = 0; i < matPoint.cols; ++i)
		{
			double w = matPoint.at<double>(3, i);
			vecPoint.emplace_back(
				matPoint.at<double>(0, i) / w,
				matPoint.at<double>(1, i) / w,
				matPoint.at<double>(2, i) / w
			);
		}
	}

	bool isInteger(const std::string &s)
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

}

#endif //CHESSBOARD_CAMERA_CALIBRATION_TOOLS_H
