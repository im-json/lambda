#pragma once

#include <vector>
#include <Eigen/Dense>

struct Column {
    std::string name;
    Eigen::VectorXd vals;
};

struct DataFrame {
    int m;
    int n;
    std::vector<Column> data;
};

struct Model {
    int n;
    int k;
    double bar_y;
    Eigen::VectorXd bar_x;
    Eigen::VectorXd beta;
    Eigen::VectorXd epsilon;
    Eigen::VectorXd y;
    Eigen::MatrixXd x;
    std::vector<std::string> names;
};

void df(DataFrame &d);

void vectorize(Column &d);

void lm(Model &m, DataFrame d);

void response(Model &m, DataFrame d);

void design(Model &m, DataFrame d);
