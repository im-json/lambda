#include <iostream>
#include <string>

#include "model.h"

void effects(Model m, Eigen::VectorXd &v) {
    Eigen::HouseholderQR<Eigen::MatrixXd> qr(m.x);
    Eigen::MatrixXd j = Eigen::MatrixXd::Identity(m.n, m.k + 1);
    Eigen::MatrixXd q = qr.householderQ() * j;

    v = q.transpose() * m.y;
}

void print_column(Column c) {
    if (c.vars.size()) {
        for (int i = 0; i < c.vars.size(); i++) {
            std::cout << c.vars[i] << '\t';
            if (c.vars[i].size() < 8) {
                std::cout << '\t';
            }
        }
        std::cout << std::endl;
    }

    for (int j = 0; j < c.vals.size(); j++) {
        std::cout << c.vals[j] << '\t';
    }

    std::cout << std::endl;
}

void print_column_precise(Column c) {
    if (c.vars.size()) {
        for (int i = 0; i < c.vars.size(); i++) {
            std::cout << c.vars[i] << '\t';
            if (c.vars[i].size() < 8) {
                std::cout << '\t';
            }
        }
    }

    std::cout << std::fixed << std::setprecision(8) << std::endl;

    for (int j = 0; j < c.vals.size(); j++) {
        std::cout << c.vals[j] << '\t';
    }

    std::cout << std::endl;
}

void print_formula(std::vector<std::string> call) {
    std::cout << "(formula = " << call[0] << " ~ ";

    for (int i = 1; i <= call.size(); i++) {
        std::cout << call[i];
        if (i == call.size() - 1) {
            break;
        }
        std::cout << " + ";
    }

    std::cout << ")\n" << std::endl;
}