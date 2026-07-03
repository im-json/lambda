#include <string>

#include "data.h"

void df(DataFrame &d) {
    Column c;
    std::vector<Column> data;

    std::cout << "Enter number of vectors: ";
    std::cin >> d.m;

    std::cout << "Enter length of vectors: ";
    std::cin >> d.n;

    c.vals.resize(d.n);

    std::cout << "Enter vectors in csv format: ";
    std::cout << "name,v1,v2,v3,..." << std::endl;

    for (int i = 0; i < d.m; i++) {
        std::cout << "Enter vector " << i + 1 << ": ";
        std::cin.ignore();

        vectorize(c);
        d.data.push_back(c);
    }

    std::cout << std::endl;
}

void vectorize(Column &c) {
    double num;
    char comma;
    std::string name;

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
