#pragma once

#include <Eigen/Dense>

void multiple_summary(
    int n, int k, int p, double bar_y, Eigen::VectorXd bar_x,
    Eigen::VectorXd &y, Eigen::MatrixXd &x
);