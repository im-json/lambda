#include <iostream>
#include <cmath>

#include "setup.h"
#include "multiple_lr.h"

void multiple_summary(int n, int k, Model m, Summary &s) {

}

double multiple_slope(
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

double multiple_rss(
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

double multiple_tss(double bar_y, Eigen::Ref<Eigen::VectorXd> y) {
    double tss = 0.0;

    for (int i = 0; i < y.size(); i++) {
        tss += std::pow(y[i] - bar_y, 2);
    }

    return tss;
}

double multiple_se(int n, double bar_x, Eigen::Ref<Eigen::VectorXd> x) {
    int num = 0.0;

    for (int i = 0; i < n; i++) {
        num += std::pow(x[i] - bar_x, 2);
    }

    return std::sqrt(num / std::pow(n, 2));
}
