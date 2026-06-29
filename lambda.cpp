#include <iostream>
#include <Eigen/Dense>

#include "lambda.h"

int main() {
    Model m;
    Summary s;

    lm(m);
    summary(m, s);

    return 0;
}
