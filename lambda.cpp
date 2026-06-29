#include <iostream>
#include <Eigen/Dense>

#include "lambda.h"

int main() {
    DataFrame df;
    Model m;
    Summary s;

    setup(df);

    lm(m, df);
    summary(m, s);

    return 0;
}
