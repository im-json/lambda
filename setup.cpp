#include <iostream>
#include <cmath>

#include "setup.h"

void setup(
    int &n, int &k, int &p, double &y_bar, Eigen::VectorXd &x_bar,
    Eigen::VectorXd &y, Eigen::MatrixXd &x
) {
    std::cout << "Enter number of observations: ";
    std::cin >> n;

    std::cout << "Enter number of predictors: ";
    std::cin >> k;

    p = k + 1;

    y.resize(n);
    x_bar.resize(p);
    x.resize(n, p);

    std::cout << "Enter y values separated by commas: " << std::endl;

    vectorize(n, y);
    tensorize(n, p, x_bar, x);

    y_bar = mean_vector(y);

    std::cout << "x.transpose:\n";
    print_matrix(x);

    std::cout << std::endl;
}

void vectorize(int n, Eigen::Ref<Eigen::VectorXd> v) {
    double d;
    char c;

    for (int i = 0; i < n; i++) {
        std::cin >> d;
        v(i) = d;
        if (i == n - 1) {
            break;
        }
        std::cin >> c;
    }
}

void tensorize(int n, int p, Eigen::VectorXd &x_bar, Eigen::MatrixXd &x) {
    x.col(0).setOnes();

    for (int i = 1; i < p; i++) {
        std::cout << "Enter x_" << i;
        std::cout << " values separated by commas: " << std::endl;
        vectorize(n, x.col(i));
    }

    x_bar = x.colwise().mean();
}

void print_vector(Eigen::Ref<Eigen::VectorXd> v) {
    std::cout << v.transpose() << std::endl;
}

void print_matrix(Eigen::MatrixXd &m) {
    std::cout << m.transpose() << std::endl;
}

double mean_vector(Eigen::Ref<Eigen::VectorXd> v) {
    return v.sum() / v.size();
}