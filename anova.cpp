#include <iostream>
#include <string>

#include "anova.h"
#include "data.h"

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

    a.rss = m.res.squaredNorm();
    a.rse = std::sqrt(a.rss / (m.n - m.k - 1));

    print_aov(m, a);
}

void anova(Model m, Anova &a) {
    sequence(m, a);

    a.meansq.resize(m.k + 1);
    a.fval.resize(m.k + 1);

    for (int i = 0; i <= m.k; i++) {
        a.meansq[i] = a.seqss[i] / a.df[i];
    }

    double se = (m.x.array() - m.bar_x[1]).square().sum();
    a.fval = (m.beta / se).array().square();

    print_anova(m, a);
}

void print_aov(Model m, Anova a) {
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Call:\naov";

    print_formula(m.call);

    std::cout << "Terms:\n\t\t";

    for (int i = 1; i < m.k + 1; i++) {
        std::cout << m.call[i] << "\t";
        if (m.call[i].size() < 8) {
            std::cout << '\t';
        }
    }

    std::cout << "Residuals\nSum of Squares\t";

    for (int j = 1; j < m.k + 1; j++) {
        std::cout << a.seqss[j] << "\t";
    }

    std::cout << a.rss << "\nDeg. of Freedom\t";

    std::cout << std::fixed << std::setprecision(0);

    for (int k = 1; k <= m.k + 1; k++) {
        std::cout << a.df[k] << "\t\t";
        if (k == m.k + 1) {
            std::cout << '\n' << std::endl;
        }
    }

    std::cout << std::fixed << std::setprecision(7);

    std::cout << "Residual standard error: " << a.rse << std::endl;
    std::cout << "Estimated effects may be unbalanced\n" << std::endl;
}

void print_anova(Model m, Anova a) {
    std::cout << "Analysis of Variance Table\n" << std::endl;
    std::cout << "Response: " << m.call[0] << std::endl;;

    std::cout << "\t\tDf\tSum Sq\tMean Sq\tF value\tPr(>F)\n";

    for (int i = 1; i < m.beta.size(); i++) {
        std::cout << std::fixed << std::setprecision(4);

        std::cout << m.call[i] << '\t';

        if (m.call[i].size() < 8) {
            std::cout << '\t';
        }

        std::cout << "1\t" << a.seqss[i] << '\t' << a.meansq[i];
        std::cout << '\t' << a.fval[i];
        
        std::cout << std::fixed << std::setprecision(5);
        std::cout << "\t0" << std::endl;
    }

    std::cout << std::fixed << std::setprecision(0);
    std::cout << "Residuals\t" << a.df[m.k + 1] << '\t';

    std::cout << std::fixed << std::setprecision(4);
    std::cout << a.rss << '\t' << a.rss / a.df[m.k + 1];
    std::cout << "\n---\n" << std::endl;
}
