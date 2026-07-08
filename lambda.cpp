#include <iostream>
#include <Eigen/Dense>

#include "lambda.h"

int main() {
    Input i;
    Memory m;

    while (i.fn != "q" && i.fn != "quit") {
        readline(i, m);
    }

    return 0;
}
