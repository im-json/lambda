#pragma once

#include <Eigen/Dense>

#include "math.h"

void lm(Model &m);

void summary(Model m, Summary &s);

void print_summary(Model m, Summary s);
