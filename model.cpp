#include <iostream>
#include <string>

#include "model.h"

void lm(Model &m, DataFrame d) {
    m.n = d.n;
    
    m.y.resize(m.n);
    response(m, d);

    std::cout << "Enter number of predictors: ";
    std::cin >> m.k;

    m.x.resize(m.n, m.k + 1);
    design(m, d);

    Eigen::MatrixXd xtx = m.x.transpose() * m.x;

    m.beta = xtx.inverse() * m.x.transpose() * m.y;
    m.res = m.y - (m.x * m.beta);

    std::cout << std::endl;
}

void response(Model &m, DataFrame d) {
    std::string name;

    std::cout << "Enter y vector name: ";
    std::cin >> name;

    m.call.push_back(name);

    for (int i = 0; i < d.m; i++) {
        if (d.data[i].name == name) {
            m.y = d.data[i].vals;
            break;
        }
    }

    m.bar_y = m.y.mean();

    std::cout << "y is: " << m.y.transpose() << std::endl;
}

void design(Model &m, DataFrame d) {
    std::string name;
    m.x.col(0).setOnes();

    for (int i = 1; i < m.x.cols(); i++) {
        std::cout << "Enter vector name for x_" << i << ": ";
        std::cin >> name;

        m.call.push_back(name);

        for (int j = 0; j < d.m; j++) {
            if (d.data[j].name == name) {
                m.x.col(i) = d.data[j].vals;
                break;
            }
        }
    }

    m.bar_x = m.x.colwise().mean();

    std::cout << "x.transpose:\n" << m.x.transpose() << std::endl;
}
