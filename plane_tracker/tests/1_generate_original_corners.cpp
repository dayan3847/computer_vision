#include "../config.h"
#include "../tools.h"
#include "../functions.h"

int main()
{
	cv::Size patternSize(8, 6);
	double squareSize = 28.45e-3;
	{
		cv::Mat originalCornersM;
		my_functions::getOriginalCorners(patternSize, squareSize, originalCornersM, false);
		my_tools::saveMatInTxt(originalCornersM.t(), "originalCornersM");
		my_tools::printMat(originalCornersM.t(), "originalCornersM");
	}
	{
		cv::Mat iK_OriginalCornersM;
		my_functions::get_iK_OriginalCorners(patternSize, squareSize, iK_OriginalCornersM, false);
		my_tools::saveMatInTxt(iK_OriginalCornersM.t(), "iK_OriginalCornersM");
		my_tools::printMat(iK_OriginalCornersM.t(), "iK_OriginalCornersM");
	}

	return 0;
}
