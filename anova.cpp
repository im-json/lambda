#include <iostream>
#include <string>

#include "anova.h"

void aov(Model m, Anova &a) {
    a.rss = m.res.squaredNorm();
    a.rse = std::sqrt(a.rss / (m.n - m.k - 1));

    a.seqss.resize(m.k + 1);
    a.fval.resize(m.k + 1);

    Eigen::HouseholderQR<Eigen::MatrixXd> qr(m.x);
    Eigen::MatrixXd i = Eigen::MatrixXd::Identity(m.n, m.k + 1);
    Eigen::MatrixXd q = qr.householderQ() * i;
    Eigen::VectorXd proj = q.transpose() * m.y;

    for (int i = 0; i <= m.k; i++) {
        a.seqss[i] = std::pow(proj[i], 2);
    }

    print_aov(m, a);
}

void print_aov(Model m, Anova a) {
    std::cout << std::fixed << std::setprecision(6);

    std::cout << "Call:\naov(formula = " << m.names[0] << " ~ ";

    for (int i = 1; i < m.k + 1; i++) {
        std::cout << m.names[i];
        if (i == m.k) {
            std::cout << ")\n" << std::endl;
            break;
        }
        std::cout << " + ";
    }

    std::cout << "Terms:\n\t\t";

    for (int i = 1; i < m.k + 1; i++) {
        std::cout << m.names[i] << "\t";
        if (m.names[i].size() < 8) {
            std::cout << '\t';
        }
    }

    std::cout << "Residuals\nSum of Squares\t";

    for (int j = 1; j < m.k + 1; j++) {
        std::cout << a.seqss[j] << "\t";
    }

    std::cout << a.rss << "\nDeg. of Freedom\t";

    for (int k = 0; k < m.k; k++) {
        std::cout << "1\t\t";
    }

    std::cout << m.n - m.k - 1 << '\n' << std::endl;

    std::cout << "Residual standard error: " << a.rse << std::endl;
    std::cout << "Estimated effects may be unbalanced" << std::endl;
}

void anova(Model m, Anova &a) {
    a.rss = m.res.squaredNorm();
    a.rse = std::sqrt(a.rss / (m.n - m.k - 1));

    a.seqss.resize(m.k + 1);
    a.fval.resize(m.k + 1);

    Eigen::HouseholderQR<Eigen::MatrixXd> qr(m.x);
    Eigen::MatrixXd i = Eigen::MatrixXd::Identity(m.n, m.k + 1);
    Eigen::MatrixXd q = qr.householderQ() * i;
    Eigen::VectorXd proj = q.transpose() * m.y;

    for (int i = 0; i <= m.k; i++) {
        a.seqss[i] = std::pow(proj[i], 2);
    }

    double se = (m.x.array() - m.bar_x[1]).square().sum();
    a.fval = (m.beta / se).array().square();

    print_anova(m, a);
}

void print_anova(Model m, Anova a) {
    std::cout << "Analysis of Variance Table\n" << std::endl;
    std::cout << "Response: " << m.names[0] << std::endl;;

    std::cout << "\t\tDf\tSum Sq\tMean Sq\tF value\tPr(>F)\n";

    for (int i = 1; i < m.beta.size(); i++) {
        std::cout << std::fixed << std::setprecision(4);

        std::cout << m.names[i] << '\t';

        if (m.names[i].size() < 8) {
            std::cout << '\t';
        }

        std::cout << "1\t" << a.seqss[i] << "\t0\t" << a.fval[i];
        
        std::cout << std::fixed << std::setprecision(5);
        std::cout << "\t0" << std::endl;
    }

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Residuals\t" << m.n - m.k - 1 << '\t' << a.rss;
    std::cout << "\t0\n---\n" << std::endl; 
}
