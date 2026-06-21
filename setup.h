#pragma once

#include <iostream>
#include <vector>
#include <Eigen/Dense>

void setup(
    int &n, int &k, int &p, double &x_bar, double &y_bar,
    Eigen::MatrixXd &x, Eigen::VectorXd &y
);

void vectorize(int n, Eigen::Ref<Eigen::VectorXd> v);

void tensorize(int n, int p, Eigen::MatrixXd &x);

void print_vector(Eigen::Ref<Eigen::VectorXd> v);

void print_matrix(Eigen::MatrixXd &m);

double mean_vector(Eigen::Ref<Eigen::VectorXd> v);

double mean_matrix(Eigen::MatrixXd &m);
