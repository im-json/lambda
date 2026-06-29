#include <iostream>
#include <string>

#include "stats.h"

void summary(Model m, Summary &s) {
    double rss, rse, tss, ess;
    double r2, adjr2, fstat, se, tstat, pval;
    
    rss = m.epsilon.squaredNorm();
    rse = std::sqrt(rss / (m.n - m.k - 1));
    tss = ((m.y.array() - m.bar_y).square()).sum();
    ess = tss - rss;

    r2 = 1.0 - (rss / tss);
    adjr2 = 1.0 - ((1.0 - r2) * (m.n - 1) / (m.n - m.k - 1));
    fstat = (ess / m.k) / (rss / (m.n - m.k - 1));
    se = ((m.x.array() - m.bar_x[1]).square()).sum();
    tstat = m.beta[1] / se;

    s = {rse, r2, adjr2, fstat, pval};

    print_summary(m, s);
}

void print_summary(Model m, Summary s) {
    std::cout << "Intercept: " << m.beta[0] << std::endl;

    for (int i = 1; i < m.beta.size(); i++) {
        std::cout << "beta_" << i << ": " << m.beta[i] << std::endl;
    }

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