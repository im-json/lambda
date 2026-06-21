#pragma once

#include <iostream>
#include <vector>
#include <Eigen/Dense>

void multiple_summary(
    int n, int k, double x_bar, double y_bar,
    Eigen::MatrixXd &x, Eigen::VectorXd &y
);
