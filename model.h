#pragma once

#include <vector>
#include <string>
#include <Eigen/Dense>
#include <iomanip>

struct Column {
    std::string name;
    std::vector<std::string> vars;
    Eigen::VectorXd vals;
};

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

void effects(Model m, Eigen::VectorXd &v);

void print_column(Column c);

void print_column_precise(Column c);

void print_formula(std::vector<std::string> call);