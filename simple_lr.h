#pragma once

#include <Eigen/Dense>

void simple_summary(
    int n, int k, int p, double bar_y, Eigen::VectorXd bar_x,
    Eigen::VectorXd &y, Eigen::MatrixXd &x
);

double simple_slope(
    double bar_y, double bar_x,
    Eigen::Ref<Eigen::VectorXd> y, Eigen::Ref<Eigen::VectorXd> x
);

double simple_intercept(double slope, double bar_y, double bar_x);

double simple_RSS(
    double intercept, double slope,
    Eigen::Ref<Eigen::VectorXd> y, Eigen::Ref<Eigen::VectorXd> x
);

double simple_RSE(int n, int p, double rss);

double simple_TSS(double bar_y, Eigen::Ref<Eigen::VectorXd> y);

double simple_R2(double rss, double tss);

double simple_adjR2(int n, int p, double r2);
