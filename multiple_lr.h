#pragma once

#include <Eigen/Dense>

void multiple_summary(
    int n, int k, int p, double y_bar, Eigen::VectorXd x_bar,
    Eigen::VectorXd &y, Eigen::MatrixXd &x
);