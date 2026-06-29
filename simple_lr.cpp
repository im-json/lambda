#include <iostream>

#include "setup.h"
#include "simple_lr.h"

void simple_summary(int n, int k, Model m, Summary &s) {
    double rss, rse, tss, ess;
    double r2, adjr2, fstat, se, tstat, pval;
    
    rss = m.epsilon.squaredNorm();
    rse = std::sqrt(rss / (n - k - 1));
    tss = ((m.y.array() - m.bar_y).square()).sum();
    ess = tss - rss;

    r2 = 1.0 - (rss / tss);
    adjr2 = 1.0 - ((1.0 - r2) * (n - 1) / (n - k - 1));
    fstat = (ess / k) / (rss / (n - k - 1));
    se = ((m.x.array() - m.bar_x[1]).square()).sum();
    tstat = m.beta[1] / se;

    s = {rse, r2, adjr2, fstat, pval};
}
