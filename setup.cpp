#include <iostream>
#include <cmath>

#include "setup.h"

void model(
    int &n, int &k, double &bar_y, Eigen::VectorXd &bar_x,
    Eigen::VectorXd &y, Eigen::MatrixXd &x
) {
    std::cout << "Enter number of observations: ";
    std::cin >> n;

    y.resize(n);

    std::cout << "Enter number of predictors: ";
    std::cin >> k;

    int p = k + 1;
    bar_x.resize(p);
    x.resize(n, p);

    std::cout << "Enter y values separated by commas: " << std::endl;
    vectorize(y);
    bar_y = y.mean();

    tensorize(bar_x, x);
    std::cout << "x.transpose:\n";
    print_matrix(x);

    std::cout << std::endl;
}

void vectorize(Eigen::Ref<Eigen::VectorXd> v) {
    double d;
    char c;

    for (int i = 0; i < v.size(); i++) {
        std::cin >> d;
        v(i) = d;
        if (i == v.size() - 1) {
            break;
        }
        std::cin >> c;
    }
}

void tensorize(Eigen::VectorXd &bar_x, Eigen::MatrixXd &x) {
    x.col(0).setOnes();

    for (int i = 1; i < x.cols(); i++) {
        std::cout << "Enter x_" << i;
        std::cout << " values separated by commas: " << std::endl;
        vectorize(x.col(i));
    }

    bar_x = x.colwise().mean();
}

void print_vector(Eigen::Ref<Eigen::VectorXd> v) {
    std::cout << v.transpose() << std::endl;
}

void print_matrix(Eigen::MatrixXd &m) {
    std::cout << m.transpose() << std::endl;
}