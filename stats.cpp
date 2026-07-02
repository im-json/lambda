#include <iostream>
#include <string>

#include "stats.h"

void summary(Model m, Summary &s) {
    double pval;

    double rss = m.epsilon.squaredNorm();
    double tss = ((m.y.array() - m.bar_y).square()).sum();
    double ess = tss - rss;
    double se = ((m.x.array() - m.bar_x[1]).square()).sum();
    double tstat = m.beta[1] / se;

    s.rse = std::sqrt(rss / (m.n - m.k - 1));

    Eigen::MatrixXd xtx = m.x.transpose() * m.x;
    Eigen::MatrixXd var = s.rse * s.rse * xtx.inverse();

    s.secoeff = var.diagonal().array().sqrt();
    s.t_val = m.beta.array() / s.secoeff.array();

    s.r2 = 1.0 - (rss / tss);
    s.adjr2 = 1.0 - ((1.0 - s.r2) * (m.n - 1) / (m.n - m.k - 1));
    s.fstat = (ess / m.k) / (rss / (m.n - m.k - 1));

    print_summary(m, s);
}

void print_summary(Model m, Summary s) {
    std::cout << "Call:" << std::endl;

    for (int i = 0; i < m.k + 1; i++) {
        if (!i) {
            std::cout << "lm(formula = " << m.names[0] << " ~ ";
            continue;
        }
        std::cout << m.names[i];
        if (i == m.k) {
            std::cout << ")\n" << std::endl;
            break;
        }
        std::cout << " + ";
    }

    std::cout << "Coefficients:\n\t\tEstimate\tStd. Error\t";
    std::cout << "t value\t\tPr(>|t|)" << std::endl;

    for (int i = 0; i < m.beta.size(); i++) {
        if (!i) {
            std::cout << "Intercept: ";
        } else {
            std::cout << "beta_" << i << ": ";
        }
        std::cout << '\t' << m.beta[i] << '\t' << s.secoeff[i];
        std::cout << '\t' << s.t_val[i] << "\t" << std::endl;
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