#include <iostream>

#include "data.h"

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

    std::cout << std::defaultfloat << std::setprecision(6);

    if (i.obj == "" && i.args == "") {
        find_memory(i, m);
    }

    if (i.fn.find("c(") != std::string::npos) {
        add_vector(i, m);
    } else if (i.fn.find("length(") != std::string::npos) {
        add_length(i, m);
    } else if (i.fn.find("mean(") != std::string::npos) {
        add_mean(i, m);
    } else if (i.fn.find("lm(") != std::string::npos) {
        add_model(i, m);
    } else if (i.fn.find("summary(") != std::string::npos) {
        add_summary(i, m);
    } else if (i.fn.find("aov(") != std::string::npos) {
        add_aov(i, m);
    } else if (i.fn.find("anova(") != std::string::npos) {
        add_anova(i, m);
    }
}

void find_memory(Input i, Memory m) {
    for (int j = 0; j < m.data.size(); j++) {
        if (m.data[j].name == i.fn) {
            for (int k = 0; k < m.data[j].vals.size(); k++) {
                std::cout << m.data[j].vals[k] << " ";
            }
            std::cout << std::endl;
            return;
        }
    }

    for (int j = 0; j < m.models.size(); j++) {
        if (m.models[j].name == i.fn) {
            return;
        }
    }

    for (int j = 0; j < m.summaries.size(); j++) {
        if (m.summaries[j].name == i.fn) {
            print_summary(m.summaries[j]);
            return;
        }
    }

    for (int j = 0; j < m.aovs.size(); j++) {
        if (m.aovs[j].name == i.fn) {
            print_aov(m.aovs[j]);
            return;
        }
    }

    for (int j = 0; j < m.anovas.size(); j++) {
        if (m.anovas[j].name == i.fn) {
            print_anova(m.anovas[j]);
            return;
        }
    }
}

void find_vector(Input i, Memory m, Eigen::VectorXd &v) {
    for (int j = 0; j < m.data.size(); j++) {
        if (m.data[j].name == i.args) {
            v = m.data[j].vals;
            break;
        }
    }
}

void find_model(Input i, Memory m, Model &mod) {
    for (int j = 0; j < m.data.size(); j++) {
        if (m.models[j].name == i.args) {
            mod = m.models[j];
            break;
        }
    }
}

void add_length(Input i, Memory &m) {
    Eigen::VectorXd v;

    find_vector(i, m, v);

    double len = v.size();

    if (i.obj.empty()) {
        std::cout << len << std::endl;
        return;
    }

    Column c;
    c.name = i.obj;
    c.vals.resize(1);
    c.vals << len;
    m.data.push_back(c);
}

void add_mean(Input i, Memory &m) {
    Eigen::VectorXd v;

    find_vector(i, m, v);

    double mean = v.sum() / v.size();

    if (i.obj.empty()) {
        std::cout << mean << std::endl;
        return;
    }

    Column c;
    c.name = i.obj;
    c.vals.resize(1);
    c.vals << mean;
    m.data.push_back(c);
}

void add_summary(Input i, Memory &m) {
    Model mod;
    Summary s;

    find_model(i, m, mod);
    summary(mod, s);

    if (i.obj.empty()) {
        print_summary(s);
        return;
    }

    s.name = i.obj;
    m.summaries.push_back(s);
}

void add_aov(Input i, Memory &m) {
    Model mod;
    Anova a;

    find_model(i, m, mod);
    aov(mod, a);

    if (i.obj.empty()) {        
        print_aov(a);
        return;
    }

    a.name = i.obj;
    m.aovs.push_back(a);
}

void add_anova(Input i, Memory &m) {
    Model mod;
    Anova a;

    find_model(i, m, mod);
    anova(mod, a);

    if (i.obj.empty()) {        
        print_anova(a);
        return;
    }

    a.name = i.obj;
    m.anovas.push_back(a);
}

void add_vector(Input i, Memory &d) {
    std::string num;
    std::vector<double> v;

    std::stringstream stream(i.args);

    while (std::getline(stream, num, ',')) {
        v.push_back(std::stod(num));
    }

    if (i.obj.empty()) {
        for (int j = 0; j < v.size(); j++) {
            std::cout << v[j] << " ";
        }
        std::cout << std::endl;
        return;
    }

    Column c;
    c.name = i.obj;
    c.vals.resize(v.size());
    c.vals = Eigen::Map<Eigen::VectorXd>(v.data(), v.size());
    d.data.push_back(c);
}

void add_model(Input i, Memory &d) {

    int tilde = i.args.find("~");

    std::string y = i.args.substr(0, tilde);
    std::string x = i.args.substr(tilde + 1, i.args.size() - tilde - 1);

    // std::cout << "y name: " << y << "\nx names: " << x << std::endl;

    std::stringstream stream(x);

    Model m;

    for (int i = 0; i < d.data.size(); i++) {
        if (d.data[i].name == y) {
            m.n = d.data[i].vals.size();
            m.y.resize(m.n);
            m.y = d.data[i].vals;
            m.call.push_back(d.data[i].name);
            break;
        }
    }

    m.bar_y = m.y.mean();

    std::string name;

    while (std::getline(stream, name, '+')) {
        m.call.push_back(name);
    }

    m.k = m.call.size() - 1;

    m.x.resize(m.n, m.k + 1);
    m.x.col(0).setOnes();

    for (int i = 1; i < m.x.cols(); i++) {
        for (int j = 0; j < d.data.size(); j++) {
            if (d.data[j].name == m.call[i]) {
                m.x.col(i) = d.data[j].vals;
                break;
            }
        }
    }

    m.bar_x = m.x.colwise().mean();

    // std::cout << "x.transpose:\n" << m.x.transpose() << std::endl;

    Eigen::MatrixXd xtx = m.x.transpose() * m.x;

    m.beta = xtx.inverse() * m.x.transpose() * m.y;
    m.res = m.y - (m.x * m.beta);

    if (!i.obj.empty()) {
        m.name = i.obj;
        d.models.push_back(m);
    }
}
