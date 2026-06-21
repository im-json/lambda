#include <iostream>
#include <Eigen/Dense>

#include "lambda.h"

int main() {
    int n, k, p;
    double y_bar;
    Eigen::MatrixXd x;
    Eigen::VectorXd x_bar, y;

    setup(n, k, p, y_bar, x_bar, y, x);

    if (k == 1) {
        simple_summary(n, k, p, y_bar, x_bar, y, x);
    } else if (k > 1) {
        multiple_summary(n, k, p, y_bar, x_bar, y, x);
    }

    return 0;
}
