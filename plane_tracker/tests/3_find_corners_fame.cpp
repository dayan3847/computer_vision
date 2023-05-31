#include "../plane_tracker.h"

int main()
{
	unsigned int frameNumber = 240;
//	unsigned int frameNumber = 240;
	// import image

	std::string winName = "Chessboard";
	cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);

	std::vector<cv::Point3f> originalCornersVP;
	my_functions::getOriginalCorners(my_config::patternSize, my_config::squareSize, originalCornersVP, false);

	cv::Mat frame = cv::imread("./tests/data/frame_" + std::to_string(frameNumber) + ".jpg");

	cv::Mat G, G0;
	my_plane_tracker::analiceFrame(frame, originalCornersVP, G, G0, frameNumber, true);
	imshow(winName, frame);
	do
	{
		if (cv::waitKey(1) == 27) break;
	} while (true);

	cv::destroyWindow(winName);
	return 0;
}
