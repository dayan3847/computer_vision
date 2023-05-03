#include <cmath>

/**
 * Gaussian function.
 *
 * @param x Value to evaluate the function.
 * @param sigma Standard deviation that defines the gaussian. Default value is 1.
 * @param mu Mean of the gaussian. Default value is 0.
 *
 * @return The value of the gaussian function evaluated in x.
 */
double gaussian(double x, double sigma = 1, double mu = 0) {
    return exp(-pow(x - mu, 2) / (2 * pow(sigma, 2))) / (sigma * sqrt(2 * M_PI));
}

/**
 * Gaussian derivative first order.
 *
 * @param x Value to evaluate the function.
 * @param sigma Standard deviation that defines the gaussian. Default value is 1.
 * @param mu Mean of the gaussian. Default value is 0.
 */
double gaussian_derivative(double x, double sigma = 1, double mu = 0) {
    return -(x - mu) * gaussian(x, sigma, mu) / pow(sigma, 2);
}

/**
 * Gaussian derivative second order.
 *
 * @param x Value to evaluate the function.
 * @param sigma Standard deviation that defines the gaussian. Default value is 1.
 * @param mu Mean of the gaussian. Default value is 0.
 */
double gaussian_derivative_2(double x, double sigma = 1, double mu = 0) {
    return (pow(x - mu, 2) / pow(sigma, 2) - 1) * gaussian(x, sigma, mu) / pow(sigma, 2);
}

/**
 * Gaussian derivative n order.
 *
 * @param x Value to evaluate the function.
 * @param sigma Standard deviation that defines the gaussian. Default value is 1.
 * @param mu Mean of the gaussian. Default value is 0.
 * @param n Order of the derivative. (0 is the gaussian function itself)
 */
double gaussian_derivative_n(double x, double sigma = 1, double mu = 0, int n = 0) {
    if (n == 0) {
        return gaussian(x, sigma, mu);
    } else if (n == 1) {
        return gaussian_derivative(x, sigma, mu);
    } else if (n == 2) {
        return gaussian_derivative_2(x, sigma, mu);
    }
    throw "Not implemented";
}

/**
* Buld Kernel.
*/