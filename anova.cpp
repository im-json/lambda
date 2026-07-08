#include <iostream>
#include <string>

#include "anova.h"

void sequence(Model m, Anova &a) {
    a.seqss.resize(m.k + 1);
    a.df.resize(m.k + 2);

    a.df.setConstant(1.0);
    a.df.tail(1) << m.n - m.k - 1;

    Eigen::HouseholderQR<Eigen::MatrixXd> qr(m.x);
    Eigen::MatrixXd i = Eigen::MatrixXd::Identity(m.n, m.k + 1);
    Eigen::MatrixXd q = qr.householderQ() * i;
    Eigen::VectorXd proj = q.transpose() * m.y;

    for (int i = 0; i <= m.k; i++) {
        a.seqss[i] = std::pow(proj[i], 2);
    }
}

void aov(Model m, Anova &a) {
    sequence(m, a);

    a.isAov = true;
    a.k = m.k;
    a.rss = m.res.squaredNorm();
    a.rse = std::sqrt(a.rss / (m.n - m.k - 1));

    a.meansq.resize(m.k + 1);
    a.fval.resize(m.k + 1);
    a.call = m.call;

    for (int i = 0; i <= m.k; i++) {
        a.meansq[i] = a.seqss[i] / a.df[i];
    }

    double se = (m.x.array() - m.bar_x[1]).square().sum();
    a.fval = (m.beta / se).array().square();
}

void anova(Model m, Anova &a) {
    sequence(m, a);

    a.isAov = false;
    a.k = m.k;
    a.rss = m.res.squaredNorm();
    a.rse = std::sqrt(a.rss / (m.n - m.k - 1));

    a.meansq.resize(m.k + 1);
    a.fval.resize(m.k + 1);
    a.call = m.call;

    for (int i = 0; i <= m.k; i++) {
        a.meansq[i] = a.seqss[i] / a.df[i];
    }

    double se = (m.x.array() - m.bar_x[1]).square().sum();
    a.fval = (m.beta / se).array().square();
}

void print_aov(Anova a) {
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Call:\naov";

    print_formula(a.call);

    std::cout << "Terms:\n\t\t";

    for (int i = 1; i < a.k + 1; i++) {
        std::cout << a.call[i] << "\t";
        if (a.call[i].size() < 8) {
            std::cout << '\t';
        }
    }

    std::cout << "Residuals\nSum of Squares\t";

    for (int j = 1; j < a.k + 1; j++) {
        std::cout << a.seqss[j] << "\t";
    }

    std::cout << a.rss << "\nDeg. of Freedom\t";

    std::cout << std::fixed << std::setprecision(0);

    for (int k = 1; k <= a.k + 1; k++) {
        std::cout << a.df[k] << "\t\t";
        if (k == a.k + 1) {
            std::cout << '\n' << std::endl;
        }
    }

    std::cout << std::fixed << std::setprecision(7);

    std::cout << "Residual standard error: " << a.rse << std::endl;
    std::cout << "Estimated effects may be unbalanced\n" << std::endl;
}

void print_anova(Anova a) {
    std::cout << "Analysis of Variance Table\n" << std::endl;
    std::cout << "Response: " << a.call[0] << std::endl;;

    std::cout << "\t\tDf\tSum Sq\tMean Sq\tF value\tPr(>F)\n";

    for (int i = 1; i <= a.k; i++) {
        std::cout << std::fixed << std::setprecision(4);

        std::cout << a.call[i] << '\t';

        if (a.call[i].size() < 8) {
            std::cout << '\t';
        }

        std::cout << "1\t" << a.seqss[i] << '\t' << a.meansq[i];
        std::cout << '\t' << a.fval[i];
        
        std::cout << std::fixed << std::setprecision(5);
        std::cout << "\t0" << std::endl;
    }

    std::cout << std::fixed << std::setprecision(0);
    std::cout << "Residuals\t" << a.df[a.k + 1] << '\t';

    std::cout << std::fixed << std::setprecision(4);
    std::cout << a.rss << '\t' << a.rss / a.df[a.k + 1];
    std::cout << "\n---\n" << std::endl;
}
