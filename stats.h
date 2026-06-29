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
};

void summary(Model m, Summary &s);

void print_summary(Model m, Summary s);

void aov();

void print_aov();