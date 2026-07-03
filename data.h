#pragma once

#include <iostream>
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

void df(DataFrame &d);

void vectorize(Column &c);