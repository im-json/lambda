#pragma once

#include <Eigen/Dense>

void setup(
    int &n, int &k, int &p, double &y_bar, Eigen::VectorXd &x_bar,
    Eigen::VectorXd &y, Eigen::MatrixXd &x
);

void vectorize(Eigen::Ref<Eigen::VectorXd> v);

void tensorize(int p, Eigen::VectorXd &x_bar, Eigen::MatrixXd &x);

void print_vector(Eigen::Ref<Eigen::VectorXd> v);

void print_matrix(Eigen::MatrixXd &m);

double mean_vector(Eigen::Ref<Eigen::VectorXd> v);