#include <iostream>
#include <Eigen/Dense>

#include "lambda.h"

int main() {
    int n, k, p;
    double bar_y;
    Eigen::VectorXd y, bar_x;
    Eigen::MatrixXd x;

    setup(n, k, p, bar_y, bar_x, y, x);

    if (k == 1) {
        simple_summary(n, k, p, bar_y, bar_x, y, x);
    } else if (k > 1) {
        multiple_summary(n, k, p, bar_y, bar_x, y, x);
    }

    return 0;
}
