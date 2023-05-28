#include "../functions.h"
#include "../tools.h"
#include "../config.h"

int main()
{
	cv::Size patternSize(8, 6);

	// Original Corners Points
	std::vector<cv::Point3f> originalCornersPoints;
	my_functions::getOriginalCorners(patternSize, 28.45e-3, originalCornersPoints, false);
	// Original Corners Mat
	cv::Mat originalCornersMat;
	my_tools::convertVecPointToMat(originalCornersPoints, originalCornersMat);
	// save original corners mat
	my_tools::saveMatInTxt(originalCornersMat.t(), "originalCornersMat");
	// print original corners mat
	my_tools::printMat(originalCornersMat.t(), "originalCornersMat");

	cv::Mat iK = my_config::iK();
	my_tools::printMat(iK, "iK");

	originalCornersMat.pop_back();
	cv::Mat iK_originalCornersMat = iK * originalCornersMat;
	// save iK_originalCornersMat
	my_tools::saveMatInTxt(iK_originalCornersMat.t(), "iK_originalCornersMat");
	// print iK_originalCornersMat
	my_tools::printMat(iK_originalCornersMat.t(), "iK_originalCornersMat");

	return 0;
}
