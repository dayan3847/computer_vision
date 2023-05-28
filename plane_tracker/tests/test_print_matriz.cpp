#include "../config.h"
#include "../tools.h"

int main()
{
	cv::Mat K = my_config::K();
	my_tools::printMat(K, "K");

	// Inverse of K
	cv::Mat iiK;
	cv::invert(K, iiK);
	my_tools::printMat(iiK, "iiK");

	cv::Mat iK = my_config::iK();
	my_tools::printMat(iK, "iK");

	cv::Mat I0 = my_config::I0();
	my_tools::printMat(I0, "I0");

	return 0;
}
