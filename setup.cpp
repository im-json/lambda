#include <iostream>

#include "setup.h"

void lm(int &n, int &k, Model &m) {
    Eigen::MatrixXd x;
    Eigen::VectorXd y, beta, bar_x;

    double bar_y;

    std::cout << "Enter number of observations: ";
    std::cin >> n;

    std::cout << "Enter number of predictors: ";
    std::cin >> k;

    std::cout << "Enter y values separated by commas: " << std::endl;
    
    y.resize(n);
    vectorize(y);

    int p = k + 1;

    x.resize(n, p);
    tensorize(x);

    std::cout << "x.transpose:\n" << x.transpose() << '\n' << std::endl;

    beta = coefficients(x, y);
    
    bar_y = y.mean();

    bar_x.resize(p);
    bar_x = x.colwise().mean();

    m = {x, y, beta, bar_x, bar_y};
}

Eigen::VectorXd coefficients(Eigen::MatrixXd x, Eigen::VectorXd y) {
    Eigen::MatrixXd xtx = x.transpose() * x;
    return xtx.inverse() * x.transpose() * y;
}

void print_summary(int n, int k, Model m, Summary s) {
    std::cout << "Intercept: " << m.beta[0] << std::endl;

    for (int i = 1; i < m.beta.size(); i++) {
        std::cout << "beta_" << i << ": " << m.beta[i] << std::endl;
    }

    std::cout << "Residual standard error: " << s.rse << " on ";
    std::cout << n - k - 1 << " degrees of freedom" << std::endl;
    
    std::cout << "Multiple R-squared: " << s.r2 << ", ";
    std::cout << "Adjusted R-squared: " << s.adjr2 << std::endl;

    std::cout << "F-statistic: " << s.fstat << " on " << k << " and ";
    std::cout << n - k - 1 << " DF" << std::endl;
}

void vectorize(Eigen::Ref<Eigen::VectorXd> v) {
    double d;
    char c;

    for (int i = 0; i < v.size(); i++) {
        std::cin >> d;
        v(i) = d;
        if (i == v.size() - 1) {
            break;
        }
        std::cin >> c;
    }
}

void tensorize(Eigen::MatrixXd &x) {
    x.col(0).setOnes();

    for (int i = 1; i < x.cols(); i++) {
        std::cout << "Enter x_" << i;
        std::cout << " values separated by commas: " << std::endl;
        vectorize(x.col(i));
    }
}
