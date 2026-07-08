#include <iostream>

#include "data.h"

void readline(Input &i, Memory &m) {
    parse(i);

    Object o;

    functions(i, m, o);

    if (!i.obj.empty()) {
        objectify(o, m);
    }
}

void functions(Input i, Memory m, Object &o) {
    std::cout << std::defaultfloat << std::setprecision(6);

    size_t t = std::string::npos;

    if (i.obj == "" && i.args == "") {
        find_memory(i, m);
    }

    if (i.fn.find("c(") != t) {
        add_vector(i, m, o);
    } else if (i.fn.find("length(") != t) {
        add_length(i, m, o);
    } else if (i.fn.find("mean(") != t) {
        add_mean(i, m, o);
    } else if (i.fn.find("lm(") != t) {
        add_model(i, m, o);
    } else if (i.fn.find("summary(") != t) {
        add_summary(i, m, o);
    } else if (i.fn.find("aov(") != t || i.fn.find("anova(") != t) {
        add_anova(i, m, o);
    }
}

void parse(Input &i) {
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
}

void objectify(Object o, Memory &m) {
    switch(o.type) {
        case 0:
            m.data.push_back(o.vec);
            break;
        case 1:
            m.models.push_back(o.mod);
            break;
        case 2:
            m.summaries.push_back(o.sum);
            break;
        case 3:
            m.anovas.push_back(o.ano);
            break;
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

    for (int j = 0; j < m.anovas.size(); j++) {
        if (m.anovas[j].name == i.fn) {
            if (m.anovas[j].isAov) {
                print_aov(m.anovas[j]);
            } else {
                print_anova(m.anovas[j]);
            }
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

void add_length(Input i, Memory m, Object &o) {
    o.type = 0;

    Eigen::VectorXd v;

    find_vector(i, m, v);

    double len = v.size();

    Column c;

    if (i.obj.empty()) {
        std::cout << len << std::endl;
        return;
    }

    c.name = i.obj;
    c.vals.resize(1);
    c.vals << len;
    
    o.vec = c;
}

void add_mean(Input i, Memory m, Object &o) {
    o.type = 0;

    Eigen::VectorXd v;

    find_vector(i, m, v);

    double mean = v.sum() / v.size();

    Column c;

    if (i.obj.empty()) {
        std::cout << mean << std::endl;
        return;
    }

    c.name = i.obj;
    c.vals.resize(1);
    c.vals << mean;

    o.vec = c;
}

void add_summary(Input i, Memory m, Object &o) {
    o.type = 2;

    Model mod;
    Summary s;

    find_model(i, m, mod);
    summary(mod, s);

    if (i.obj.empty()) {
        print_summary(s);
        return;
    }

    s.name = i.obj;

    o.sum = s;
}

void add_anova(Input i, Memory m, Object &o) {
    o.type = 3;

    bool isAov;
    if (i.fn.find("aov(") != std::string::npos) {
        isAov = true;
    } else if (i.fn.find("anova(") != std::string::npos) {
        isAov = false;
    }

    Anova a;
    Model mod;

    if (i.args.find("~") == std::string::npos) {
        find_model(i, m, mod);
    } else {
        add_model(i, m, o);
        mod = m.temp;
    }

    anova(mod, a, isAov);

    if (i.obj.empty()) {
        if (a.isAov) {
            print_aov(a);
        } else {
            print_anova(a);
        }
        return;
    }

    a.name = i.obj;
    
    o.ano = a;
}

void add_vector(Input i, Memory d, Object &o) {
    o.type = 0;

    std::string num;
    std::vector<double> v;

    std::stringstream stream(i.args);

    while (std::getline(stream, num, ',')) {
        v.push_back(std::stod(num));
    }
    
    Column c;

    if (i.obj.empty()) {
        for (int j = 0; j < v.size(); j++) {
            std::cout << v[j] << " ";
        }
        std::cout << std::endl;
        return;
    }

    c.name = i.obj;
    c.vals.resize(v.size());
    c.vals = Eigen::Map<Eigen::VectorXd>(v.data(), v.size());
    
    o.vec = c;
}

void add_model(Input i, Memory d, Object &o) {
    o.type = 1;

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

    d.temp = m;
    m.name = i.obj;

    o.mod = m;
}
