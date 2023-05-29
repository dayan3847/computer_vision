#include "../plane_tracker.h"

int main()
{
	unsigned int frameNumber = 50;
	// import image
	cv::Mat frame = cv::imread("./../tests/data/frame_" + std::to_string(frameNumber) + ".jpg");
	cv::Size patternSize(8, 6);
	double squareSize = 28.45e-3;

	std::string winName = "Chessboard";
	cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);

	std::vector<cv::Point3f> originalCornersVP;
	my_functions::getOriginalCorners(patternSize, squareSize, originalCornersVP, false);

	my_plane_tracker::analiceFrame(frame, originalCornersVP, patternSize, winName, true);

	do
	{
		if (cv::waitKey(1) == 27) break;
	} while (true);

	cv::destroyWindow(winName);
	return 0;
}
