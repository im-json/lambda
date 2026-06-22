#include <iostream>
#include <cmath>

#include "setup.h"
#include "simple_lr.h"

void simple_summary(int n, int k, Model m, Summary &s) {
    int dof;
    double slope, intercept;
    double rss, rse;
    double r2, adjr2;

    slope = simple_slope(m.bar_y, m.bar_x[1], m.y, m.x.col(1));
    intercept = simple_intercept(slope, m.bar_y, m.bar_x[1]);

    dof = n - k - 1;

    rss = simple_rss(intercept, slope, m.y, m.x.col(1));
    rse = simple_rse(n, k, rss);

    r2 = simple_r2(rss, m.bar_y, m.y);
    adjr2 = simple_adjr2(n, k, r2);

    Eigen::VectorXd hat_beta(2);
    hat_beta << intercept, slope;

    s = {hat_beta, rse, r2, adjr2, dof};
}

double simple_slope(
    double bar_y, double bar_x,
    Eigen::Ref<Eigen::VectorXd> y, Eigen::Ref<Eigen::VectorXd> x
) {
    double num = 0.0, den = 0.0;

    for (int i = 0; i < y.size(); i++) {
        num += (x[i] - bar_x) * (y[i] - bar_y);
        den += std::pow((x[i] - bar_x), 2);
    }

    return num / den;
}

double simple_intercept(double slope, double bar_y, double bar_x) {
    return bar_y - (slope * bar_x);
}

double simple_rss(
    double intercept, double slope,
    Eigen::Ref<Eigen::VectorXd> y, Eigen::Ref<Eigen::VectorXd> x
) {
    double y_hat = 0.0, rss = 0.0;

    for (int i = 0; i < y.size(); i++) {
        y_hat = intercept + (slope * x[i]);
        rss += std::pow(std::abs(y[i] - y_hat), 2);
    }
    
    return rss;
}

double simple_rse(int n, int k, double rss) {
    return std::pow(rss / (n - k - 1), 0.5);
}

double simple_r2(double rss, double bar_y, Eigen::Ref<Eigen::VectorXd> y) {
    double tss = 0.0;

    for (int i = 0; i < y.size(); i++) {
        tss += std::pow(std::abs(y[i] - bar_y), 2);
    }

    return 1.0 - (rss / tss);
}

double simple_adjr2(int n, int k, double r2) {
    return 1.0 - ((1.0 - r2)*(n - 1) / (n - k - 1));
}
