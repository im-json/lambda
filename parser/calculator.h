#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <cmath>

#include "../parser/parser_impl.h"

using namespace grammar;

template <typename T>
class Calculator : public Grammar<T> {
        static T add(T lhs, T rhs) { return lhs + rhs; }
        static T sub(T lhs, T rhs) { return lhs - rhs; }
        static T mul(T lhs, T rhs) { return lhs * rhs; }
        static T div(T lhs, T rhs) { return lhs / rhs; }
        static T neg(T lhs) { return -lhs; }
        static T pos(T lhs) { return lhs; }
        static T pow(T lhs, T rhs) { return std::pow(lhs, rhs); }
        static T fac(T lhs) { return std::tgamma(lhs + 1); }
    public:
        Calculator() : Grammar<T>("(end)") {
            Grammar<T>::add_symbol_to_dict("(number)", 0)\
            .set_scanner(
            [](const std::string& str, size_t pos) -> size_t {
            std::string::size_type i = pos;
            bool hasDot = false;
                while(i < str.length() && (isdigit(str[i]) || str[i] == '.')) {
                    if (str[i] == '.') {
                        if (hasDot) break;
                        hasDot = true;
                    }
                    ++i;
                }
                if (i == pos) return pos;

                if (i < str.length() && std::isalpha(static_cast<unsigned char>(str[i]))) {
                    throw std::runtime_error("");
                }

                return i;
            })\
            .set_parser(
            [](const std::string& str, size_t beg, size_t end) -> T {
                std::string sub = str.substr(beg, end - beg);
                size_t valid = 0;
                T result;
                if constexpr (std::is_same_v<T, float>) {
                    result = std::stof(sub, &valid);
                } else {
                    result = std::stod(sub, &valid);
                }

                if (valid != sub.length()) {
                    throw std::runtime_error("");
                }

                return result;
            });

            this->infix("+", 10, add); this->infix("-", 10, sub);
            this->infix("*", 20, mul); this->infix("/", 20, div);
            this->prefix("+", 30, pos, keep_symbol_lbp);
            this->prefix("-", 30, neg, keep_symbol_lbp);
            this->infix_r("^", 40, pow); this->postfix("!", 50, fac);
            this->constant("PI", static_cast<T>(M_PI));
            this->constant("pi", static_cast<T>(M_PI));
            this->constant("Pi", static_cast<T>(M_PI));
            Grammar<T>::brackets("(",")", std::numeric_limits<int>::max(),[](int x){return x;});
        }
};
