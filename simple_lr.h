#pragma once

#include <Eigen/Dense>

void simple_summary(
    int n, int k, int p, double bar_y, Eigen::VectorXd bar_x,
    Eigen::VectorXd &y, Eigen::MatrixXd &x
);

double get_slope(
    double bar_x, double bar_y,
    Eigen::Ref<Eigen::VectorXd> x, Eigen::Ref<Eigen::VectorXd> y
);

double get_intercept(double slope, double bar_x, double bar_y);

double get_RSS(
    double intercept, double slope,
    Eigen::Ref<Eigen::VectorXd> x, Eigen::Ref<Eigen::VectorXd> y
);

double get_RSE(int n, int p, double rss);

double get_TSS(double bar_y, Eigen::Ref<Eigen::VectorXd> y);

double get_R2(double rss, double tss);

double get_adjR2(int n, int p, double r2);
