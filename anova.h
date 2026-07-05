#pragma once

#include <vector>
#include <string>
#include <Eigen/Dense>
#include <cmath>
#include <iomanip>

#include "model.h"

struct Anova {
    int k;
    double rse;
    double rss;
    Eigen::VectorXd df;
    Eigen::VectorXd seqss;
    Eigen::VectorXd meansq;
    Eigen::VectorXd fval;
    std::string name;
    std::vector<std::string> call;
};

void sequence(Model m, Anova &a);

void aov(Model m, Anova &a);

void anova(Model m, Anova &a);

void print_aov(Anova a);

void print_anova(Anova a);
