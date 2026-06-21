#include <iostream>
#include <cmath>

#include "setup.h"
#include "simple_lr.h"

void simple_summary(
    int n, int k, int p, double bar_y, Eigen::VectorXd bar_x,
    Eigen::VectorXd &y, Eigen::MatrixXd &x
) {
    double slope, intercept;
    double rss, rse, tss;
    double r2, adjr2;

    slope = simple_slope(bar_y, bar_x[1], y, x.col(1));
    intercept = simple_intercept(slope, bar_y, bar_x[1]);

    rss = simple_RSS(intercept, slope, y, x.col(1));
    rse = simple_RSE(n, k, rss);
    tss = simple_TSS(bar_y, y);

    r2 = simple_R2(rss, tss);
    adjr2 = simple_adjR2(n, k, r2);

    std::cout << "Intercept: " << intercept << std::endl;
    std::cout << "Slope: " << slope << std::endl;

    std::cout << "Residual standard error: " << rse << " on ";
    std::cout << n - p << " degrees of freedom" << std::endl;
    
    std::cout << "Multiple R-squared: " << r2 << ", ";
    std::cout << "Adjusted R-squared: " << adjr2 << std::endl;
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

double simple_RSS(
    double intercept, double slope,
    Eigen::Ref<Eigen::VectorXd> y, Eigen::Ref<Eigen::VectorXd> x
) {
    double y_hat;
    double rss = 0.0;

    for (int i = 0; i < y.size(); i++) {
        y_hat = intercept + (slope * x[i]);
        rss += std::pow(std::abs(y[i] - y_hat), 2);
    }
    
    return rss;
}

double simple_RSE(int n, int p, double rss) {
    return std::pow(rss / (n - p - 1), 0.5);
}

double simple_TSS(double bar_y, Eigen::Ref<Eigen::VectorXd> y) {
    double tss = 0.0;

    for (int i = 0; i < y.size(); i++) {
        tss += std::pow(std::abs(y[i] - bar_y), 2);
    }

    return tss;
}

double simple_R2(double rss, double tss) {
    return 1.0 - (rss / tss);
}

double simple_adjR2(int n, int p, double r2) {
    return 1.0 - ((1.0 - r2)*(n - 1) / (n - p - 1));
}
