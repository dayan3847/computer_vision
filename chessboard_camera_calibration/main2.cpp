#include <iostream>
#include "opencv2/opencv.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    const std::string winName = "camera";

    // abrir la camara
    // cv::VideoCapture videoCapture(0);

    // abrir un video
    auto videoPath = "/media/dayan3847/3TB/photos/clases VC/20230517/profe/Chessboard.mp4";
    cv::VideoCapture videoCapture(videoPath);


    if (!videoCapture.isOpened()) {
        std::cout << "Error al abrir la camara o el video" << std::endl;
        return -1;
    }

    // crear la ventana
    cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);

    // crear un objeto para guardar los cuadros
    std::vector<cv::Mat> frames;

    // crear un objeto para guardar los puntos de las esquinas
    std::vector<std::vector<cv::Point2f>> corners;


    cv::Mat frame;
    cv::Mat imCorners;

    cv::Size patternSize = cv::Size(9, 6);

    while (true) {

        videoCapture >> frame;
        if (frame.empty()) {
            std::cout << "Error al capturar el frame" << std::endl;
            break;
        }
        // find Chessboard Corners
        bool found = cv::findChessboardCorners(frame, patternSize, imCorners, cv::CALIB_CB_ADAPTIVE_THRESH);

        if (found) {
            cv::drawChessboardCorners(frame, patternSize, imCorners, found);
        }

        cv::imshow(winName, frame);

        int c = cv::waitKey(1);
        if (c == 27) {
            break;
        }
    }

    videoCapture.release();
    cv::destroyAllWindows();

    return 0;
}
