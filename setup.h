#pragma once

#include <Eigen/Dense>

void model(
    int &n, int &k, double &bar_y, Eigen::VectorXd &bar_x,
    Eigen::VectorXd &y, Eigen::MatrixXd &x
);

void vectorize(Eigen::Ref<Eigen::VectorXd> v);

void tensorize(Eigen::MatrixXd &x);
