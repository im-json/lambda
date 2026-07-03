#pragma once

#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include <iomanip>

#include "model.h"

struct Anova {
    double rse;
    double rss;
    Eigen::VectorXd df;
    Eigen::VectorXd seqss;
    Eigen::VectorXd meansq;
    Eigen::VectorXd fval;
};

void sequence(Model m, Anova &a);

void aov(Model m, Anova &a);

void anova(Model m, Anova &a);

void print_aov(Model m, Anova a);

void print_anova(Model m, Anova a);
