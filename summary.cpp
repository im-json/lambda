#include <iostream>
#include <string>

#include "summary.h"

void summary(Model m, Summary &s) {
    double pval;

    double rss = m.res.squaredNorm();
    double tss = (m.y.array() - m.bar_y).square().sum();
    double ess = tss - rss;
    double se = (m.x.array() - m.bar_x[1]).square().sum();
    double tstat = m.beta[1] / se;

    s.rse = std::sqrt(rss / (m.n - m.k - 1));

    Eigen::MatrixXd xtx = m.x.transpose() * m.x;
    Eigen::MatrixXd var = s.rse * s.rse * xtx.inverse();

    s.secoeff = var.diagonal().array().sqrt();
    s.t_val = m.beta.array() / s.secoeff.array();

    s.r2 = 1.0 - (rss / tss);
    s.adjr2 = 1.0 - ((1.0 - s.r2) * (m.n - 1) / (m.n - m.k - 1));
    s.fval = (ess / m.k) / (rss / (m.n - m.k - 1));

    print_summary(m, s);
}

void print_summary(Model m, Summary s) {
    std::cout << "Call:\nlm(formula = " << m.names[0] << " ~ ";

    for (int i = 1; i < m.k + 1; i++) {
        std::cout << m.names[i];
        if (i == m.k) {
            std::cout << ")\n" << std::endl;
            break;
        }
        std::cout << " + ";
    }

    // Eigen::VectorXd q(5);
    // quantile(m.res, q);

    // std::cout << "Residuals:\nMin\t\t1Q\t\tMedian\t\t3Q\t\tMax\n";
    // std::cout << q[0] << '\t' << q[1] << '\t' << q[2];
    // std::cout << '\t' << q[3] << '\t' << q[4] << std::endl;

    std::cout << "Coefficients:\n\t\tEstimate\tStd. Error\t";
    std::cout << "t value\tPr(>|t|)\n(Intercept)\t";

    for (int i = 0; i < m.beta.size(); i++) {
        std::cout << std::fixed << std::setprecision(6);
        std::cout << m.beta[i] << '\t' << s.secoeff[i] << '\t';
        std::cout << std::fixed << std::setprecision(3);
        std::cout << s.t_val[i] << "\t";
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "0" << std::endl;

        if (i == m.beta.size() - 1) {
            break;
        }
        std::cout << m.names[i + 1] << '\t';
        if (m.names[i + 1].size() < 8) {
            std::cout << '\t';
        }
    }

    std::cout << std::endl;
    std::cout << "Residual standard error: " << s.rse << " on ";
    std::cout << m.n - m.k - 1 << " degrees of freedom" << std::endl;
    
    std::cout << "Multiple R-squared: " << s.r2 << ", ";
    std::cout << "Adjusted R-squared: " << s.adjr2 << std::endl;

    std::cout << "F-statistic: " << s.fval << " on " << m.k << " and ";
    std::cout << m.n - m.k - 1 << " DF\n" << std::endl;
}
