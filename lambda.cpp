#include <iostream>
#include <Eigen/Dense>

#include "lambda.h"

int main() {
    Input i;
    Memory m;

    while (i.func != "q(" && i.func != "quit(") {
        readline(i, m);
    }

    return 0;
}
