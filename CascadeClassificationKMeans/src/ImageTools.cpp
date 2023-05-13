//
// Created by dayan3847 on 4/11/23.
//

#include "ImageTools.h"

void ImageTools::showImage(Mat &image, const string &name, bool destroy) {
    Mat &imageToPrint = image;
    // resize without interpolation
    resize(image, imageToPrint, Size(600, 600), 0, 0, INTER_NEAREST);
    imshow(name, imageToPrint);
    waitKey(0);
    if (destroy)
        destroyWindow(name);
}

void ImageTools::printImageByMask(
        const Mat &mask,
        const Mat &originalImage,
        map<int, ImageStats> &stats,
        const int &luminance
) {
    // create a new image L*a*b* with the same size of the mask
    Mat imageLabThr = Mat::zeros(mask.size(), CV_32FC3);
    auto itImageOriginal = originalImage.begin<Vec3f>();
    auto itImage = imageLabThr.begin<Vec3f>();
    auto itMask = mask.begin<uchar>();
    auto itEnd = mask.end<uchar>();
    while (itMask != itEnd) {
        auto label = *itMask;
        auto &pixel = *itImage;
        auto imageStatsClassI = stats[label];
        // luminance analysis
        if (0 >= luminance) // luminance = 0 -> no luminance
            pixel[0] = 0;
        else if (1 == luminance) // luminance = 1 -> original luminance
            pixel[0] = (*itImageOriginal)[0];
        else // luminance = 2 -> mean luminance
            pixel[0] = imageStatsClassI.mean.l;
        pixel[1] = imageStatsClassI.mean.a;
        pixel[2] = imageStatsClassI.mean.b;
        itImageOriginal++;
        itImage++;
        itMask++;
    }

    Mat imageThr;
    cvtColor(imageLabThr, imageThr, COLOR_Lab2BGR);
    imageThr *= 255.0;
    imageThr.convertTo(imageThr, CV_8UC3);

    ImageTools::showImage(imageThr, "Thresholding");

}
