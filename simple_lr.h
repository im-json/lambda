#pragma once

#include <Eigen/Dense>

void simple_summary(int n, int k, Model m, Summary &s);

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

double simple_tss(double bar_y, Eigen::Ref<Eigen::VectorXd> y);

double simple_adjr2(int n, int k, double r2);

double simple_fstat(int n, int k, double rss, double ess);

double simple_se(int n, double bar_x, Eigen::Ref<Eigen::VectorXd> x);

double simple_tstat(double slope, double se);
