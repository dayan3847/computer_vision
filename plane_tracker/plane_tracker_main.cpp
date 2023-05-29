#include <iostream>
#include "plane_tracker.h"

int main(int argc, char ** argv)
{
	std::cout << argc << std::endl;
	std::cout << argv[0] << std::endl;
	std::cout << argv[1] << std::endl;
	if (argc < 2)
	{
		std::cerr << "You need to pass a parameter" << std::endl;
		return 1;
	}
	cv::VideoCapture videoCapture;
	std::string indexOrFilename = argv[1];

	if (my_tools::isInteger(indexOrFilename))
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

	my_plane_tracker::keepTrack(videoCapture);

	return 0;
}
