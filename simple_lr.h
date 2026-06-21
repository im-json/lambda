#pragma once

#include <Eigen/Dense>

void simple_summary(
    int n, int k, int p, double x_bar, double y_bar,
    Eigen::MatrixXd &x, Eigen::VectorXd &y
);

double get_slope(
    int n, double x_bar, double y_bar,
    Eigen::Ref<Eigen::VectorXd> x, Eigen::Ref<Eigen::VectorXd> y
);

double get_intercept(double slope, double x_bar, double y_bar);

double get_RSS(
    int n, double intercept, double slope,
    Eigen::Ref<Eigen::VectorXd> x, Eigen::Ref<Eigen::VectorXd> y
);

double get_RSE(int n, int p, double rss);

double get_TSS(int n, Eigen::Ref<Eigen::VectorXd> y, double y_bar);

double get_R2(double rss, double tss);

double get_adjR2(int n, int p, double r2);
