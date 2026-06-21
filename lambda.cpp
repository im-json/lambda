#include "lambda.h"

int main() {
    int n, k, p;
    double x_bar, y_bar;
    Eigen::MatrixXd x;
    Eigen::VectorXd y;

    setup(n, k, p, x_bar, y_bar, x, y);

    if (k == 1) {
        simple_summary(n, k, x_bar, y_bar, x, y);
    } else if (k > 1) {
        multiple_summary(n, k, x_bar, y_bar, x, y);
    }

    return 0;
}
