#pragma once

#include <vector>
#include <Eigen/Dense>

struct Data {
    std::string name;
    Eigen::VectorXd v;
};

struct DataFrame {
    int c;
    int n;
    std::vector<Data> col;
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
};

void setup(DataFrame &df);

void vectorize(Data &d);

void lm(Model &m, DataFrame df);

void design(Eigen::MatrixXd &x, DataFrame df);
