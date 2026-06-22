#pragma once

#include <Eigen/Dense>

struct Model {
    Eigen::MatrixXd x;
    Eigen::VectorXd y;
    Eigen::VectorXd bar_x;
    double bar_y;
};

struct Summary {
    Eigen::VectorXd hat_beta;
    double rse;
    double r2;
    double adjr2;
    int dof;
};

void lm(int &n, int &k, Model &m);

void print_summary(Summary s);

void vectorize(Eigen::Ref<Eigen::VectorXd> v);

void tensorize(Eigen::MatrixXd &x);
