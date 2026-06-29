#pragma once

#include <cmath>
#include <algorithm>
#include <Eigen/Dense>

struct Model {
    int n;
    int k;
    double bar_y;
    Eigen::VectorXd bar_x;
    Eigen::VectorXd beta;
    Eigen::VectorXd epsilon;
    Eigen::VectorXd y;
    Eigen::MatrixXd x;
};

struct Summary {
    double rse;
    double r2;
    double adjr2;
    double fstat;
    double pval;
};

void vectorize(Eigen::Ref<Eigen::VectorXd> v);

void design(Eigen::MatrixXd &x);
