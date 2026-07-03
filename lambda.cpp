#include <iostream>
#include <Eigen/Dense>

#include "lambda.h"

int main() {
    DataFrame d;
    Model m;
    Summary s;
    Anova a;

    df(d);
    lm(m, d);
    summary(m, s);
    aov(m, a);
    anova(m, a);

    return 0;
}
