#pragma once

#include <Eigen/Dense>

void simple_summary(int n, int k, Model m, Summary &s);

double simple_rss(
    Eigen::Ref<Eigen::VectorXd> x, Eigen::Ref<Eigen::VectorXd> y,
    Eigen::Ref<Eigen::VectorXd> beta
);

double simple_tss(double bar_y, Eigen::Ref<Eigen::VectorXd> y);

double simple_se(int n, double bar_x, Eigen::Ref<Eigen::VectorXd> x);
