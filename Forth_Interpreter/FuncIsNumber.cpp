#include "FuncIsNumber.hpp"

#include <stdexcept>
#include <string>
#include <climits>

bool IsNumber(const std::string str) {
    if (((str[0] == '-') && str.length() > 1) || isdigit(str[0])) {
        for (unsigned int i = 1; i < str.length(); ++i) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
    }
    else {
        return false;
    }

    long long num = stoll(str);

    if (num > INT_MAX || num < INT_MIN) {
        throw std::overflow_error("Stack overflow!");
    }
    
    return true;
}