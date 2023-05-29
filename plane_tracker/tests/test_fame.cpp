#include "../plane_tracker.h"

int main()
{
	unsigned int frameNumber = 50;
	// import image
	cv::Mat frame = cv::imread("./../tests/data/frame_" + std::to_string(frameNumber) + ".jpg");
	cv::Size patternSize(8, 6);

	std::string winName = "Chessboard";
	cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);

	std::vector<cv::Point3f> iK_OriginalCornersVP;
	my_functions::get_iK_OriginalCorners(patternSize, 28.45e-3, iK_OriginalCornersVP, false);

	my_plane_tracker::analiceFrame(frame, iK_OriginalCornersVP, patternSize, winName, true);

	do
	{
		if (cv::waitKey(1) == 27) break;
	} while (true);

	cv::destroyWindow(winName);
	return 0;
}
