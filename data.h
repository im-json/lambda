#pragma once

#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <Eigen/Dense>

struct Input {
    std::string obj;
    std::string fn;
    std::string args;
};

struct Column {
    std::string name;
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

struct Memory {
    std::vector<Column> data;
    std::vector<Model> models;
};

void readline(Input &i, Memory &m);

void add_model(Input i, Memory &m);

void add_summary(Input i, Memory &m);

void add_aov(Input i, Memory &m);

void add_anova(Input i, Memory &m);

void add_vector(Input i, Memory &m);

void print_formula(std::vector<std::string> call);
