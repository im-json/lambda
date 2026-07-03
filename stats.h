#pragma once

#include <vector>
#include <Eigen/Dense>

#include "data.h"

struct Summary {
    double rse;
    double r2;
    double adjr2;
    double fstat;
    double pval;
    Eigen::VectorXd secoeff;
    Eigen::VectorXd t_val;
};

void summary(Model m, Summary &s);

void print_summary(Model m, Summary s);

void quantile(Eigen::VectorXd v, Eigen::VectorXd &q);

void aov();

void print_aov();