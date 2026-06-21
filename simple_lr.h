#pragma once

#include <Eigen/Dense>

void simple_summary(
    int n, int k, int p, double y_bar, Eigen::VectorXd x_bar,
    Eigen::VectorXd &y, Eigen::MatrixXd &x
);

double get_slope(
    double x_bar, double y_bar,
    Eigen::Ref<Eigen::VectorXd> x, Eigen::Ref<Eigen::VectorXd> y
);

double get_intercept(double slope, double x_bar, double y_bar);

double get_RSS(
    double intercept, double slope,
    Eigen::Ref<Eigen::VectorXd> x, Eigen::Ref<Eigen::VectorXd> y
);

double get_RSE(int n, int p, double rss);

double get_TSS(double y_bar, Eigen::Ref<Eigen::VectorXd> y);

double get_R2(double rss, double tss);

double get_adjR2(int n, int p, double r2);
