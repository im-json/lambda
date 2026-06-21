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

    slope = get_slope(bar_x[1], bar_y, x.col(1), y);
    intercept = get_intercept(slope, bar_x[1], bar_y);

    rss = get_RSS(intercept, slope, x.col(1), y);
    rse = get_RSE(n, k, rss);
    tss = get_TSS(bar_y, y);

    r2 = get_R2(rss, tss);
    adjr2 = get_adjR2(n, k, r2);

    std::cout << "Intercept: " << intercept << std::endl;
    std::cout << "Slope: " << slope << std::endl;

    std::cout << "Residual standard error: " << rse << " on ";
    std::cout << n - p << " degrees of freedom" << std::endl;
    
    std::cout << "Multiple R-squared: " << r2 << ", ";
    std::cout << "Adjusted R-squared: " << adjr2 << std::endl;
}

double get_slope(
    double bar_x, double bar_y,
    Eigen::Ref<Eigen::VectorXd> x, Eigen::Ref<Eigen::VectorXd> y
) {
    double num = 0.0, den = 0.0;

    for (int i = 0; i < y.size(); i++) {
        num += (x[i] - bar_x) * (y[i] - bar_y);
        den += std::pow((x[i] - bar_x), 2);
    }

    return num / den;
}

double get_intercept(double slope, double bar_x, double bar_y) {
    return bar_y - (slope * bar_x);
}

double get_RSS(
    double intercept, double slope,
    Eigen::Ref<Eigen::VectorXd> x, Eigen::Ref<Eigen::VectorXd> y
) {
    double y_hat;
    double rss = 0.0;

    for (int i = 0; i < y.size(); i++) {
        y_hat = intercept + (slope * x[i]);
        rss += std::pow(std::abs(y[i] - y_hat), 2);
    }
    
    return rss;
}

double get_RSE(int n, int p, double rss) {
    return std::pow(rss / (n - p - 1), 0.5);
}

double get_TSS(double bar_y, Eigen::Ref<Eigen::VectorXd> y) {
    double tss = 0.0;

    for (int i = 0; i < y.size(); i++) {
        tss += std::pow(std::abs(y[i] - bar_y), 2);
    }

    return tss;
}

double get_R2(double rss, double tss) {
    return 1.0 - (rss / tss);
}

double get_adjR2(int n, int p, double r2) {
    return 1.0 - ((1.0 - r2)*(n - 1) / (n - p - 1));
}
