#pragma once

#include <vector>
#include <string>
#include <Eigen/Dense>
#include <cmath>
#include <iomanip>

#include "model.h"

struct Anova {
    bool isAov;
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

void anova(Model m, Anova &a, bool isAov);

void print_aov(Anova a);

void print_anova(Anova a);
