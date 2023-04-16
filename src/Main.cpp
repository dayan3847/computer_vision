//
// Created by dayan3847 on 4/11/23.
//

#include "Main.h"

#include <utility>
#include "ImageRepo.h"
#include "ImageTools.h"
#include "MatTools.h"
#include "ConsolePrinter.h"
#include "Thresholding.h"


Main::Main(string imagePath) {
    this->imagePath = std::move(imagePath);
    this->stats = map<int, ImageStats>();
}

void Main::run() {

    // loadImages
    if (!imagePath.empty()) {
        ImageRepo::byName(image, imageOriginal, imagePath);
    } else {
        ImageRepo::defaultImage(image, imageOriginal);
    }

    // showOriginalImage
    ImageTools::showImage(imageOriginal, "Original", false);

    // init mask with zeros.
    mask = Mat::zeros(image.size(), CV_8UC1);
    // print mask
    ConsolePrinter::printMask(mask);
    // init classes
    vector<int> labels = {0};
    MatTools::meanCovariance(image, mask, stats, labels);

    int luminance = 0;
    ImageTools::printImageByMask(mask, image, stats, luminance);

    auto thresholding = Thresholding(image);
    for (int i = 0; i < 20; ++i) {
        cout << "Level: " << i + 1 << endl;

        vector<int> nextLabels = thresholding.propagate(mask, labels, stats);
        if (nextLabels.empty()) {
            break;
        }
        ConsolePrinter::printMask(mask);
        ImageTools::printImageByMask(mask, image, stats, luminance);

        labels = nextLabels;
    }
}
