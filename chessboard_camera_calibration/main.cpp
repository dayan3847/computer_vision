#include <iostream>
#include <opencv2/opencv.hpp>


int myFindChessboardCorners(cv::VideoCapture &videoCapture) {
    if (!videoCapture.isOpened()) {
        std::cout << "Error al abrir la camara o el video" << std::endl;
        return -1;
    }
//    int IM_WIDTH = 1920, IM_HEIGHT = 1080;
    int IM_WIDTH = 800, IM_HEIGHT = 600;
    double frmWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
    double frmHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
    double scaleX = IM_WIDTH / frmWidth;
    double scaleY = IM_HEIGHT / frmHeight;

    std::string winName = "Chessboard";
    cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
    cv::Size patternSize = cv::Size(9, 6);
    cv::Mat frame;
    cv::Mat corners;
    do {
        // print current time
        std::cout << "current time is: "
                  << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())
                  << std::endl;

        videoCapture >> frame;
        if (frame.empty()) {
            std::cout << "Error al capturar el frame" << std::endl;
            break;
        }

//        bool retVal = videoCapture.read(frame);
//        if (!retVal) {
//            std::cout << "Error al capturar el frame" << std::endl;
//            break;
//        }

//        if (scaleX != 1. || scaleY != 1.) {
//            resize(frame, frame, cv::Size(), scaleX, scaleY, cv::INTER_AREA);
//        }

        bool patternWasFound = cv::findChessboardCorners(frame, patternSize, corners);
//        bool patternWasFound = cv::findChessboardCorners(frame, patternSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH);
        if (patternWasFound) {
            std::cout << corners.size() << std::endl;
            drawChessboardCorners(frame, patternSize, corners, true);
        }

        imshow(winName, frame);

        // calcular la homografia
        // 1. encontrar las esquinas en el mundo real

//        std::vector<cv::Point2f> realCorners;
//        realCorners.emplace_back(0, 0);
//        realCorners.emplace_back(0, 1);
//        realCorners.emplace_back(1, 1);
//        realCorners.emplace_back(1, 0);
//
//        // 2. encontrar las esquinas en la imagen
//        std::vector<cv::Point2f> imCorners;
//        imCorners.emplace_back(0, 0);
//        imCorners.emplace_back(0, 1);
//        imCorners.emplace_back(1, 1);
//        imCorners.emplace_back(1, 0);


        // 3. calcular la homografia




        //         H, status = findHomography(realCorners, imCorners)



        if (cv::waitKey(1) == 27) break;
    } while (true);

    videoCapture.release();
    cv::destroyWindow(winName);

    return 0;
}


bool myIsInteger(const std::string &s) {
    try {
        std::stoi(s);
        return true;
    } catch (const std::invalid_argument &ia) {
        return false;
    }
}

int main(int argc, char **argv) {
    std::cout << argc << std::endl;
    std::cout << argv[0] << std::endl;
    std::cout << argv[1] << std::endl;
    if (argc < 2) {
        std::cout << "You need to pass a parameter" << std::endl;
        return 1;
    }
    cv::VideoCapture videoCapture;
    std::string indexOrFilename = argv[1];

    if (myIsInteger(indexOrFilename)) {
        videoCapture = cv::VideoCapture(std::stoi(indexOrFilename));
        if (argc > 3) {
            double newCapPropFrameWidth = std::stoi(argv[2]);
            double newCapPropFrameHeight = std::stoi(argv[3]);

            double oldCapPropFrameWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
            double oldCapPropFrameHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);

            videoCapture.set(cv::CAP_PROP_FRAME_WIDTH, newCapPropFrameWidth);
            videoCapture.set(cv::CAP_PROP_FRAME_HEIGHT, newCapPropFrameHeight);

            std::cout << "Changed frame width from " << oldCapPropFrameWidth << " to " << newCapPropFrameWidth
                      << std::endl;
            std::cout << "Changed frame height from " << oldCapPropFrameHeight << " to " << newCapPropFrameHeight
                      << std::endl;
        }
    } else {
        videoCapture = cv::VideoCapture(indexOrFilename);
    }

    myFindChessboardCorners(videoCapture);

    return 0;
}