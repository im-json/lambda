#pragma once

#include <Eigen/Dense>

void simple_summary(int n, int k, Model m, Summary &s);

double simple_slope(
    double bar_y, double bar_x,
    Eigen::Ref<Eigen::VectorXd> y, Eigen::Ref<Eigen::VectorXd> x
);

double simple_rss(
    double intercept, double slope,
    Eigen::Ref<Eigen::VectorXd> y, Eigen::Ref<Eigen::VectorXd> x
);


double simple_tss(double bar_y, Eigen::Ref<Eigen::VectorXd> y);

double simple_se(int n, double bar_x, Eigen::Ref<Eigen::VectorXd> x);
