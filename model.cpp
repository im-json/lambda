#include <iostream>
#include <string>

#include "model.h"
#include "data.h"

void add_model(Input i, Memory &d) {

    int tilde = i.args.find("~");

    std::string y = i.args.substr(0, tilde);
    std::string x = i.args.substr(tilde + 1, i.args.size() - tilde - 1);

    // std::cout << "y name: " << y << "\nx names: " << x << std::endl;

    std::stringstream stream(x);

    Model m;

    m.name = i.obj;

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

    d.models.push_back(m);
}
