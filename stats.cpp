#include <iostream>
#include <string>

#include "stats.h"

void summary(Model m, Summary &s) {
    double pval;

    double rss = m.epsilon.squaredNorm();
    double rse = std::sqrt(rss / (m.n - m.k - 1));
    double se = ((m.x.array() - m.bar_x[1]).square()).sum();

    Eigen::MatrixXd xtx = m.x.transpose() * m.x;
    Eigen::MatrixXd var = rse * rse * xtx.inverse();
    Eigen::VectorXd secoeff = var.diagonal().array().sqrt();
    Eigen::VectorXd t_val = m.beta.array() / secoeff.array();

    double tss = ((m.y.array() - m.bar_y).square()).sum();
    double ess = tss - rss;

    double r2 = 1.0 - (rss / tss);
    double adjr2 = 1.0 - ((1.0 - r2) * (m.n - 1) / (m.n - m.k - 1));
    double fstat = (ess / m.k) / (rss / (m.n - m.k - 1));
    double tstat = m.beta[1] / se;

    s = {rse, r2, adjr2, fstat, pval, secoeff, t_val};

    print_summary(m, s);
}

void print_summary(Model m, Summary s) {
    std::cout << "Coefficients: " << std::endl;
    std::cout << "\t\tEstimate\tStd. Error\tt value\t\tPr(>|t|)" << std::endl;

    for (int i = 0; i < m.beta.size(); i++) {
        if (!i) {
            std::cout << "Intercept: ";
        } else {
            std::cout << "beta_" << i << ": ";
        }
        std::cout << '\t' << m.beta[i] << '\t' << s.secoeff[i];
        std::cout << '\t' << s.t_val[i] << '\t' << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Residual standard error: " << s.rse << " on ";
    std::cout << m.n - m.k - 1 << " degrees of freedom" << std::endl;
    
    std::cout << "Multiple R-squared: " << s.r2 << ", ";
    std::cout << "Adjusted R-squared: " << s.adjr2 << std::endl;

    std::cout << "F-statistic: " << s.fstat << " on " << m.k << " and ";
    std::cout << m.n - m.k - 1 << " DF" << std::endl;
}

void aov() {

}

void print_aov() {

}