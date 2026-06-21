#pragma once

#include <Eigen/Dense>

void multiple_summary(
    int n, int k, int p, double x_bar, double y_bar,
    Eigen::MatrixXd &x, Eigen::VectorXd &y
);
