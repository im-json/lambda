#include <iostream>

#include "setup.h"
#include "simple_lr.h"

void simple_summary(int n, int k, Model m, Summary &s) {
    int dof;
    double slope, intercept;
    double rss, rse, tss, ess;
    double r2, adjr2, fstat, se, tstat, pval;

    slope = simple_slope(m.bar_y, m.bar_x[1], m.y, m.x.col(1));
    intercept = m.bar_y - (slope * m.bar_x[1]);
    
    rss = simple_rss(intercept, slope, m.y, m.x.col(1));
    rse = std::sqrt(rss / (n - k - 1));
    tss = simple_tss(m.bar_y, m.y);

    ess = tss - rss;
    r2 = 1.0 - (rss / tss);

    adjr2 = 1.0 - ((1.0 - r2)*(n - 1) / (n - k - 1));
    fstat = (ess / k) / (rss / (n - k - 1));
    se = simple_se(n, m.bar_x[1], m.x.col(1));
    tstat = slope / se;

    Eigen::VectorXd beta(2);
    beta << intercept, slope;

    s = {beta, rse, r2, adjr2, fstat, pval};
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

double simple_tss(double bar_y, Eigen::Ref<Eigen::VectorXd> y) {
    double tss = 0.0;

    for (int i = 0; i < y.size(); i++) {
        tss += std::pow(y[i] - bar_y, 2);
    }

    return tss;
}

double simple_se(int n, double bar_x, Eigen::Ref<Eigen::VectorXd> x) {
    int num = 0.0;

    for (int i = 0; i < n; i++) {
        num += std::pow(x[i] - bar_x, 2);
    }

    return std::sqrt(num / std::pow(n, 2));
}
