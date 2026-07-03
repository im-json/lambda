#pragma once

#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include <iomanip>

#include "summary.h"
#include "model.h"

struct Summary {
    double rse;
    double r2;
    double adjr2;
    double fval;
    double pval;
    Eigen::VectorXd secoeff;
    Eigen::VectorXd t_val;
};

void summary(Model m, Summary &s);

void print_summary(Model m, Summary s);

void quantile(Eigen::VectorXd v, Eigen::VectorXd &q);
