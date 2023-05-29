#include "../plane_tracker.h"

int main()
{
	unsigned int frameNumber = 1;
	// import image

	std::string winName = "Chessboard";
	cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);

	std::vector<cv::Point3d> originalCornersVP;
	my_functions::getOriginalCorners(my_config::patternSize, my_config::squareSize, originalCornersVP, false);

	cv::Mat frame = cv::imread("./tests/data/frame_" + std::to_string(frameNumber) + ".jpg");

	my_plane_tracker::analiceFrame(frame, originalCornersVP, winName, true);

	do
	{
		if (cv::waitKey(1) == 27) break;
	} while (true);

	cv::destroyWindow(winName);
	return 0;
}
