#include <iostream>
#include <string>

#include "data.h"

void df(DataFrame &d) {
    int m, n;
    std::string name;
    Column c;
    std::vector<Column> data;

    std::cout << "Enter number of vectors: ";
    std::cin >> m;

    std::cout << "Enter length of vectors: ";
    std::cin >> n;

    c.vals.resize(n);

    std::cout << "Enter vectors in csv format: ";
    std::cout << "name,v1,v2,v3,..." << std::endl;

    for (int i = 0; i < m; i++) {
        std::cout << "Enter vector " << i + 1 << ": ";
        std::cin.ignore();

        vectorize(c);
        data.push_back(c);
    }

    d = {m, n, data};
}

void vectorize(Column &c) {
    std::string name;
    double num;
    char comma;

    std::getline(std::cin, name, ',');
    c.name = name;

    for (int i = 0; i < c.vals.size(); i++) {
        std::cin >> num;
        c.vals(i) = num;
        if (i == c.vals.size() - 1) {
            break;
        }
        std::cin >> comma;
    }
}

void lm(Model &m, DataFrame d) {
    int k;
    double bar_y;
    
    std::string name;

    Eigen::VectorXd y, beta, epsilon, bar_x;
    Eigen::MatrixXd x, xtx;

    std::cout << std::endl;
    std::cout << "Enter number of predictors: ";
    std::cin >> k;

    y.resize(d.n);
    x.resize(d.n, k + 1);

    std::cout << "Enter y vector name: ";
    std::cin >> name;

    for (int i = 0; i < d.m; i++) {
        if (d.data[i].name == name) {
            y = d.data[i].vals;
            break;
        }
    }

    std::cout << "y is: " << y.transpose() << std::endl;

    design(x, d);

    xtx = x.transpose() * x;

    std::cout << "x.transpose:\n" << x.transpose() << std::endl;

    beta = xtx.inverse() * x.transpose() * y;
    epsilon = y - (x * beta);

    bar_y = y.mean();
    bar_x.resize(k + 1);
    bar_x = x.colwise().mean();

    std::cout << std::endl;

    m = {d.n, k, bar_y, bar_x, beta, epsilon, y, x};
}

void design(Eigen::MatrixXd &x, DataFrame d) {
    std::string name;
    x.col(0).setOnes();

    for (int i = 1; i < x.cols(); i++) {
        std::cout << "Enter vector name for x_" << i << ": ";
        std::cin >> name;

        for (int j = 0; j < d.m; j++) {
            if (d.data[j].name == name) {
                x.col(i) = d.data[j].vals;
                break;
            }
        }
    }
}
