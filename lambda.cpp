#include <iostream>
#include <Eigen/Dense>

#include "lambda.h"

int main() {
    int n, k;
    double bar_y;
    Eigen::VectorXd y, bar_x;
    Eigen::MatrixXd x;

    model(n, k, bar_y, bar_x, y, x);

    if (k == 1) {
        simple_summary(n, k, bar_y, bar_x[1], y, x.col(1));
    } else if (k > 1) {
        multiple_summary(n, k, bar_y, bar_x, y, x);
    }

    return 0;
}
