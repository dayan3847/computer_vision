#include <opencv2/opencv.hpp>

int main() {
    // Crear una imagen en escala de grises de 800x800 píxeles
    cv::Mat imagen(800, 800, CV_8UC1, cv::Scalar(0));

    // Dibujar los puntos de origen de las coordenadas x e y
    cv::circle(imagen, cv::Point(0, 0), 10, cv::Scalar(255), -1); // Origen (0, 0)
    cv::circle(imagen, cv::Point(0, imagen.rows - 1), 3, cv::Scalar(255), -1); // Origen (0, altura de la imagen - 1)
    cv::circle(imagen, cv::Point(imagen.cols - 1, 0), 3, cv::Scalar(255), -1); // Origen (ancho de la imagen - 1, 0)

    // Dibujar la línea y = 5
    cv::line(imagen, cv::Point(0, 5), cv::Point(imagen.cols - 1, imagen.rows - 1), cv::Scalar(255), 1);

    // Mostrar la imagen en una ventana
    cv::imshow("Imagen en escala de grises", imagen);
    cv::waitKey(0);

    return 0;
}