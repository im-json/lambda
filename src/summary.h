#pragma once

#include <vector>
#include <string>
#include <Eigen/Dense>
#include <cmath>
#include <iomanip>

#include "model.h"

struct Summary {
    int n;
    int k;
    double rse;
    double r2;
    double adjr2;
    double fval;
    double pval;
    Eigen::VectorXd beta;
    Eigen::VectorXd secoeff;
    Eigen::VectorXd t_val;
    std::string name;
    std::vector<std::string> call;
};

void summary(Model m, Summary &s);

void print_summary(Summary s);

void quantile(Eigen::VectorXd v, Eigen::VectorXd &q);
