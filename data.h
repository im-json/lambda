#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <Eigen/Dense>

#include "model.h"
#include "summary.h"
#include "anova.h"

struct Column {
    std::string name;
    Eigen::VectorXd vals;
};

struct Object {
    int type;
    Column vec;
    Model mod;
    Summary sum;
    Anova ano;
};

struct Input {
    std::string obj;
    std::string fn;
    std::string args;
};

struct Memory {
    std::vector<Column> data;
    std::vector<Model> models;
    std::vector<Summary> summaries;
    std::vector<Anova> anovas;
};

void readline(Input &i, Memory &m);

void parse(Input &i);

void functions(Input i, Memory m, Object &o);

void objectify(Object o, Memory &m);

void find_memory(Input i, Memory m);

void find_vector(Input i, Memory m, Eigen::VectorXd &v);

void add_length(Input i, Memory m, Object &o);

void add_mean(Input i, Memory m, Object &o);

void add_model(Input i, Memory m, Object &o);

void add_summary(Input i, Memory m, Object &o);

void add_anova(Input i, Memory m, Object &o);

void add_vector(Input i, Memory m, Object &o);

void add_model(Input i, Memory m, Object &o);
