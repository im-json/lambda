#pragma once

#include <vector>
#include <Eigen/Dense>

#include "data.h"

struct Model {
    int n;
    int k;
    double bar_y;
    Eigen::VectorXd bar_x;
    Eigen::VectorXd beta;
    Eigen::VectorXd res;
    Eigen::VectorXd y;
    Eigen::MatrixXd x;
    std::vector<std::string> call;
};

void lm(Model &m, DataFrame d);

void response(Model &m, DataFrame d);

void design(Model &m, DataFrame d);
