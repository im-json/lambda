#include <iostream>
#include <Eigen/Dense>

#include "lambda.h"

int main() {
    int n, k;
    Model m;
    Summary s;

    lm(n, k, m);

    if (k == 1) {
        simple_summary(n, k, m, s);
    } else if (k > 1) {
        multiple_summary(n, k, m, s);
    }

    print_summary(n, k, s);

    return 0;
}
