#include <iostream>
#include <Eigen/Dense>

#include "lambda.h"

int main() {
    DataFrame d;
    Model m;
    Summary s;

    df(d);
    lm(m, d);
    summary(m, s);

    return 0;
}
