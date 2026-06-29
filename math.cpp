#include <iostream>

#include "math.h"

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

void matricize(Eigen::MatrixXd &x) {
    x.col(0).setOnes();

    for (int i = 1; i < x.cols(); i++) {
        std::cout << "Enter x_" << i;
        std::cout << " values separated by commas: " << std::endl;
        vectorize(x.col(i));
    }
}
