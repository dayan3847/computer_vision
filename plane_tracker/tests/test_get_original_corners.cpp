#include "../functions.h"
#include "../tools.h"
#include "../config.h"

int main()
{
	cv::Size patternSize(8, 6);

	// Original Corners Points
	std::vector<cv::Point3f> originalCornersPoints;
	my_functions::getOriginalCorners(patternSize, 28.45e-3, originalCornersPoints);
	// Original Corners Mat
	cv::Mat originalCornersMat;
	my_tools::convertVecPointToMat(originalCornersPoints, originalCornersMat);
	// Print Original Corners Mat
	my_tools::printMat(originalCornersMat.t(), "originalCornersMat");

	cv::Mat iK = my_config::iK();
	// remove last row
	originalCornersMat.pop_back();
	cv::Mat iK_originalCornersMat = iK * originalCornersMat;
	my_tools::printMat(iK_originalCornersMat.t(), "iK_originalCornersMat");

	return 0;
}
