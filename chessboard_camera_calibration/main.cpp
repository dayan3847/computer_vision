#include <iostream>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>

void printMat(const cv::Mat &mat, const std::string &name = "Mat") {
    std::cout << name << std::endl;
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++)
            std::cout << mat.at<double>(i, j) << "\t";
        std::cout << std::endl;
    }
}

void buildTransformationMatrix(const cv::Mat &R, const cv::Mat &T, cv::Mat &G) {
    CV_Assert(R.rows == 3 && R.cols == 3 && T.rows == 3 && T.cols == 1);

    R.copyTo(G(cv::Rect(0, 0, 3, 3)));
    T.copyTo(G(cv::Rect(3, 0, 1, 3)));
    G.at<double>(0, 3) = 0.;
    G.at<double>(1, 3) = 0.;
    G.at<double>(2, 3) = 0.;
    G.at<double>(3, 3) = 1.;
}

void gramSchmidtOrthogonalizationMethod(cv::Mat &H) {
    Eigen::MatrixXd eigenR12(3, 2);
    eigenR12
            <<
            H.at<double>(0, 0), H.at<double>(0, 1),
            H.at<double>(1, 0), H.at<double>(1, 1),
            H.at<double>(2, 0), H.at<double>(2, 1);
    // std::cout << "eigenR12: " << eigenR12 << std::endl;
    // Orthogonalization
    Eigen::MatrixXd R12_orthogonal = eigenR12.householderQr().householderQ();
    // Print R12_orthogonal
    // std::cout << "R12_orthogonal: " << R12_orthogonal << std::endl;
    // actualizar los valores de r1 y r2
    for (int col = 0; col < 2; ++col)
        for (int row = 0; row < 3; ++row)
            H.at<double>(row, col) = R12_orthogonal(row, col);
}

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

    // K matrix
    cv::Mat K = (cv::Mat_<double>(3, 3)
            <<
            7.6808743880079578e+02, 0., 4.2089026071365419e+02,
            0., 7.6808743880079578e+02, 3.0855623821214846e+02,
            0., 0., 1.
    );

    // I_3x3_0_3X1 matrix
    cv::Mat I0 = (cv::Mat_<double>(3, 4)
            <<
            1., 0., 0., 0.,
            0., 1., 0., 0.,
            0., 0., 1., 0.
    );

    // K IO matrix
    cv::Mat KI0 = K * I0;

    // delta t 30 fps
    double dt = 1. / 30;
    std::string winName = "Chessboard";
    cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
    cv::Size patternSize = cv::Size(8, 6);
    std::vector<cv::Point2f> originalCorners;
    getOriginalCorners(patternSize, 28.45e-3, originalCorners);


    cv::Mat rObject = (cv::Mat_<double>(4, 4)
            <<
            0., 1., 0., 0., // x
            0., 0., 1., 0., // y
            0., 0., 0., 1., // z
            1., 1., 1., 1. // 1
    );

    printMat(rObject, "rObject");

    // get the first row of rObject remove the last row
    cv::Mat objectRow = rObject.col(0);
    // remove the last row
    objectRow.pop_back(1);

    printMat(objectRow, "objectRow");

    cv::Point3f objectPoint(objectRow);


    cv::Mat frame;
    std::vector<cv::Point2f> corners;
    do {
        // print current time
        std::cout << "current time is: "
                  << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())
                  << std::endl;

        // Step 2: Capture frame
        std::cout << "Step 2: Capture frame" << std::endl;
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

        // Step 3: Find Chessboard Corners
        std::cout << "Step 3: Find Chessboard Corners" << std::endl;
        bool patternWasFound = cv::findChessboardCorners(frame, patternSize, corners);
        // bool patternWasFound = cv::findChessboardCorners(frame, patternSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH);
        // Draw Chessboard Corners
        if (patternWasFound) {
//            drawChessboardCorners(frame, patternSize, corners, patternWasFound);
            std::cout << corners.size() << std::endl;
            // Applying K matrix
            cv::Mat cornersMat(corners);
            cv::Mat cornersMatT = cornersMat.t();

            // Step 4: Calculate Homography (H matrix)
            std::cout << "Step 4: Calculate Homography (H matrix)" << std::endl;
            cv::Mat H = cv::findHomography(originalCorners, corners);
//            cv::Mat H = cv::findHomography(corners, originalCorners);
            std::cout << "H: " << H << std::endl;

            // Step 5: Normalize H matrix
            std::cout << "Step 5: Normalize H matrix" << std::endl;
            H /= cv::norm(H.col(0));
            std::cout << "H: " << H << std::endl;

            // Step 5.5: Calculate the translation vector T
            std::cout << "Step 5.5: Calculate the translation vector T" << std::endl;
            cv::Mat T = H.col(2);
            // Print T matrix
            std::cout << "T: " << T << std::endl;

            // Step 6: Gram-Schmidt Orthogonalization Method
            std::cout << "Step 6: Gram-Schmidt Orthogonalization Method" << std::endl;
            gramSchmidtOrthogonalizationMethod(H);

            // Print H matrix
            std::cout << "H: " << H << std::endl;

            // Step 6.5: Normalize r1 and r2
            // r1
            cv::Mat r1 = H.col(0);
            r1 /= cv::norm(r1);
            // r2
            cv::Mat r2 = H.col(1);
            r2 /= cv::norm(r2);

            // Step 7: Calculate the rotation matrix R
            std::cout << "Step 7: Calculate the rotation matrix R" << std::endl;
            cv::Mat R(3, 3, CV_64F);
            cv::Mat r3 = r1.cross(r2);
            r1.copyTo(R.col(0));
            r2.copyTo(R.col(1));
            r3.copyTo(R.col(2));
            // Print R matrix
            std::cout << "R: " << R << std::endl;

            // Step 8: Calculate G matrix
            cv::Mat G(4, 4, CV_64F, cv::Scalar(0));
            buildTransformationMatrix(R, T, G);

            printMat(G, "G");

            cv::Mat_<double> object = I0 * G * rObject;
//            object.
            printMat(object, "object");
            cv::Mat_<double> object_col1 = object.col(1);
            object_col1 /= object_col1.at<double>(2, 0);
            object_col1.pop_back(1);
            printMat(object_col1, "object_col1");
            cv::Point2f object_col1p(object_col1);
            // Draw point in green
            cv::circle(frame, object_col1p, 5, cv::Scalar(0, 255, 0), 2);


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