#include <iostream>
#include <opencv2/opencv.hpp>
//#include <Eigen/Dense>


void getOriginalCorners(cv::Size &size, double squareSize, std::vector<cv::Point2f> &outCorners) {
    double initHeight = (size.height - 1.) / 2 * squareSize * -1;
    double initWidth = (size.width - 1.) / 2 * squareSize * -1;
    for (int i = 0; i < size.height; ++i) {
        double y = initHeight + i * squareSize;
        for (int j = 0; j < size.width; ++j) {
            double x = initWidth + j * squareSize;
            outCorners.emplace_back(x, y);
        }
    }
}

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
    cv::Size patternSize = cv::Size(8, 6);
    std::vector<cv::Point2f> originalCorners;
    getOriginalCorners(patternSize, 28.45, originalCorners);
    cv::Mat frame;
    std::vector<cv::Point2f> corners;
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

        if (scaleX != 1. || scaleY != 1.) {
            resize(frame, frame, cv::Size(), scaleX, scaleY, cv::INTER_AREA);
        }

        // Find Chessboard Corners
        bool patternWasFound = cv::findChessboardCorners(frame, patternSize, corners);
//        bool patternWasFound = cv::findChessboardCorners(frame, patternSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH);
        // Draw Chessboard Corners
        drawChessboardCorners(frame, patternSize, corners, patternWasFound);
        if (patternWasFound) {
            std::cout << corners.size() << std::endl;

            // Calculate Homography (H matrix)
            cv::Mat H = cv::findHomography(originalCorners, corners);

            // norma de la primera columna de H (r1)
            double norm = cv::norm(H.col(0));

            // normalizar la primera columna de H (r1) para toda la matriz
            H /= norm;
            // Print H matrix
            std::cout << "H: " << H << std::endl;

            // T Matrix is 3rd columns of H matrix
            cv::Mat T = H.col(2);
            // Print T matrix
            std::cout << "T: " << T << std::endl;

            // Gram-Schmidt Orthogonalization Method
        }

        imshow(winName, frame);

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