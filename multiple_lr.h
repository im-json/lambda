#pragma once

#include <Eigen/Dense>

void multiple_summary(int n, int k, Model m, Summary &s);

double multiple_slope(
    double bar_y, double bar_x,
    Eigen::Ref<Eigen::VectorXd> y, Eigen::Ref<Eigen::VectorXd> x
);

double multiple_rss(
    double intercept, double slope,
    Eigen::Ref<Eigen::VectorXd> y, Eigen::Ref<Eigen::VectorXd> x
);

double multiple_tss(double bar_y, Eigen::Ref<Eigen::VectorXd> y);

double multiple_se(int n, double bar_x, Eigen::Ref<Eigen::VectorXd> x);