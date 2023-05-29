#include "../config.h"
#include "../tools.h"
#include "../functions.h"

int main()
{
	cv::Size patternSize(8, 6);
	double squareSize = 28.45e-3;

	cv::Mat originalCornersM;
	my_functions::getOriginalCorners(patternSize, squareSize, originalCornersM, false);
	my_tools::saveMatInTxt(originalCornersM.t(), "originalCornersM");
	my_tools::printMat(originalCornersM.t(), "originalCornersM");

	return 0;
}
