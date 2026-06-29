#pragma once

#include <cmath>
#include <algorithm>
#include <Eigen/Dense>

struct Model {
    Eigen::MatrixXd x;
    Eigen::VectorXd y;
    Eigen::VectorXd beta;
    Eigen::VectorXd bar_x;
    double bar_y;
};

struct Summary {
    double rse;
    double r2;
    double adjr2;
    double fstat;
    double pval;
};

void lm(int &n, int &k, Model &m);

Eigen::VectorXd coefficients(Eigen::MatrixXd x, Eigen::VectorXd y);

void print_summary(int n, int k, Model m, Summary s);

void vectorize(Eigen::Ref<Eigen::VectorXd> v);

void tensorize(Eigen::MatrixXd &x);
