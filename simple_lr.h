#pragma once

#include <Eigen/Dense>

void simple_summary(
    int n, int k, double bar_y, double bar_x,
    Eigen::Ref<Eigen::VectorXd> y, Eigen::Ref<Eigen::VectorXd> x
);

double simple_slope(
    double bar_y, double bar_x,
    Eigen::Ref<Eigen::VectorXd> y, Eigen::Ref<Eigen::VectorXd> x
);

double simple_intercept(double slope, double bar_y, double bar_x);

double simple_rss(
    double intercept, double slope,
    Eigen::Ref<Eigen::VectorXd> y, Eigen::Ref<Eigen::VectorXd> x
);

double simple_rse(int n, int k, double rss);

double simple_r2(double rss, double bar_y, Eigen::Ref<Eigen::VectorXd> y);

double simple_adjr2(int n, int k, double r2);
