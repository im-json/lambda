#pragma once

#include <Eigen/Dense>

void setup(
    int &n, int &k, double &bar_y, Eigen::VectorXd &bar_x,
    Eigen::VectorXd &y, Eigen::MatrixXd &x
);

void vectorize(Eigen::Ref<Eigen::VectorXd> v);

void tensorize(Eigen::VectorXd &bar_x, Eigen::MatrixXd &x);

void print_vector(Eigen::Ref<Eigen::VectorXd> v);

void print_matrix(Eigen::MatrixXd &m);

double mean_vector(Eigen::Ref<Eigen::VectorXd> v);