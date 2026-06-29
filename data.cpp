#include <iostream>
#include <string>

#include "data.h"

void setup(DataFrame &df) {
    int c, n;
    std::string name;
    Data d;
    std::vector<Data> vec;

    std::cout << "Enter number of vectors: ";
    std::cin >> c;

    std::cout << "Enter length of vectors: ";
    std::cin >> n;

    d.v.resize(n);

    for (int i = 0; i < c; i++) {
        std::cout << "Enter vector " << i + 1 << " in csv format: ";
        std::cout << "name,v1,v2,v3,..." << std::endl;
        std::cin.ignore();

        vectorize(d);
        vec.push_back(d);
    }

    df = {c, n, vec};
}

void vectorize(Data &d) {
    std::string name;
    double num;
    char c;

    std::getline(std::cin, name, ',');
    d.name = name;

    for (int i = 0; i < d.v.size(); i++) {
        std::cin >> num;
        d.v(i) = num;
        if (i == d.v.size() - 1) {
            break;
        }
        std::cin >> c;
    }
}

void lm(Model &m, DataFrame df) {
    int k;
    double bar_y;
    
    std::string name;

    Eigen::VectorXd y, beta, epsilon, bar_x;
    Eigen::MatrixXd x, xtx;

    std::cout << "Enter number of predictors: ";
    std::cin >> k;

    y.resize(df.n);
    x.resize(df.n, k + 1);

    std::cout << "Enter y vector name: " << std::endl;
    std::cin >> name;

    for (int i = 0; i < df.c; i++) {
        if (df.col[i].name == name) {
            y = df.col[i].v;
            break;
        }
    }

    std::cout << "y vector is: " << y.transpose() << std::endl;

    design(x, df);

    xtx = x.transpose() * x;

    std::cout << "x.transpose:\n" << x.transpose() << std::endl;

    beta = xtx.inverse() * x.transpose() * y;
    epsilon = y - (x * beta);

    bar_y = y.mean();
    bar_x.resize(k + 1);
    bar_x = x.colwise().mean();

    std::cout << std::endl;

    m = {df.n, k, bar_y, bar_x, beta, epsilon, y, x};
}

void design(Eigen::MatrixXd &x, DataFrame df) {
    std::string name;
    x.col(0).setOnes();

    for (int i = 1; i < x.cols(); i++) {
        std::cout << "Enter vector name for x_{i" << i << "}: ";
        std::cin >> name;

        for (int j = 0; j < df.c; j++) {
            if (df.col[j].name == name) {
                x.col(i) = df.col[j].v;
                break;
            }
        }
    }
}
