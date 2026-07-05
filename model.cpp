#include <iostream>
#include <string>

#include "model.h"

void print_formula(std::vector<std::string> call) {
    std::cout << "(formula = " << call[0] << " ~ ";

    for (int i = 1; i <= call.size(); i++) {
        std::cout << call[i];
        if (i == call.size() - 1) {
            break;
        }
        std::cout << " + ";
    }

    std::cout << ")\n" << std::endl;
}