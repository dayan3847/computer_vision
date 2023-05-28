//
// Created by dayan3847 on 5/21/23.
//

#ifndef CHESSBOARD_CAMERA_CALIBRATION_CONFIG_H
#define CHESSBOARD_CAMERA_CALIBRATION_CONFIG_H

#include <iostream>
#include <opencv2/opencv.hpp>

namespace my_config
{

	cv::Mat K()
	{
		cv::Mat K = (cv::Mat_<double>(3, 3)
			<<
			7.6808743880079578e+02, 0., 4.2089026071365419e+02,
			0., 7.6808743880079578e+02, 3.0855623821214846e+02,
			0., 0., 1.
		);
		return K;
	}

	cv::Mat iK()
	{
		cv::Mat iK = (cv::Mat_<double>(3, 3)
			<<
			1. / 7.6808743880079578e+02, 0., -4.2089026071365419e+02 / 7.6808743880079578e+02,
			0., 1. / 7.6808743880079578e+02, -3.0855623821214846e+02 / 7.6808743880079578e+02,
			0., 0., 1.
		);
		return iK;
	}

	cv::Mat I0()
	{
		cv::Mat I0 = (cv::Mat_<double>(3, 4)
			<<
			1., 0., 0., 0.,
			0., 1., 0., 0.,
			0., 0., 1., 0.
		);
		return I0;
	}

	cv::Mat axis()
	{
		cv::Mat I0 = (cv::Mat_<double>(4, 4)
			<<
			0., 1., 0., 0., // x
			0., 0., 1., 0., // y
			0., 0., 0., 1., // z
			1., 1., 1., 1.  // 1
		);
		return I0;
	}

}

#endif //CHESSBOARD_CAMERA_CALIBRATION_CONFIG_H
