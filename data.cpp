#include <iostream>

#include "data.h"
#include "summary.h"
#include "anova.h"

void readline(Input &i, Memory &m) {
    std::cout << "> ";

    std::string s;
    std::getline(std::cin, s);

    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());

    int arrow = s.find("<-");
    int l = s.find("(");
    int r = s.find(")");

    if (arrow == std::string::npos) {
        arrow = 0;
    }

    if (l == std::string::npos) {
        l = s.size() - 1;
    }

    if (r == std::string::npos) {
        r = l;
    }

    i.obj = s.substr(0, arrow);
    i.fn = s.substr(arrow, l - arrow + 1);
    i.args = s.substr(l + 1, r - l - 1);

    // std::cout << "i.obj: " << i.obj << std::endl;
    // std::cout << "i.func: " << i.func << std::endl;
    // std::cout << "i.args: " << i.args << std::endl;

    if (!i.obj.empty()) {
        if (i.fn.find("<-c(") != std::string::npos) {
            add_vector(i, m);
        }
        if (i.fn.find("<-lm(") != std::string::npos) {
            add_model(i, m);
        }
    }

    if (i.obj.empty()) {
        if (i.fn == "summary(") {
            add_summary(i, m);
        }
        if (i.fn == "aov(") {
            add_aov(i, m);
        }
        if (i.fn == "anova(") {
            add_anova(i, m);
        }
    }
}

void add_summary(Input i, Memory &m) {
    Summary s;

    for (int j = 0; j < m.models.size(); j++) {
        if (m.models[j].name == i.args) {
            summary(m.models[j], s);
            break;
        }
    }
}

void add_aov(Input i, Memory &m) {
    Anova a;

    for (int j = 0; j < m.models.size(); j++) {
        if (m.models[j].name == i.args) {
            aov(m.models[j], a);
            break;
        }
    }
}

void add_anova(Input i, Memory &m) {
    Anova a;

    for (int j = 0; j < m.models.size(); j++) {
        if (m.models[j].name == i.args) {
            anova(m.models[j], a);
            break;
        }
    }
}

void add_vector(Input i, Memory &d) {
    std::string num;
    std::vector<double> vec;
    Column c;

    c.name = i.obj;

    std::stringstream stream(i.args);

    while (std::getline(stream, num, ',')) {
        vec.push_back(std::stod(num));
    }

    c.vals.resize(vec.size());

    c.vals = Eigen::Map<Eigen::VectorXd>(vec.data(), vec.size());

    d.data.push_back(c);
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