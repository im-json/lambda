#pragma once

#include <vector>
#include <string>
#include <Eigen/Dense>

struct Model {
    int n;
    int k;
    double bar_y;
    Eigen::VectorXd bar_x;
    Eigen::VectorXd beta;
    Eigen::VectorXd res;
    Eigen::VectorXd y;
    Eigen::MatrixXd x;
    std::string name;
    std::vector<std::string> call;
};

void print_formula(std::vector<std::string> call);