#include "FuncIsNumber.hpp"

bool IsNumber(std::string str) {
    size_t num = 0;

    if (((str[0] == '-') && str.length() > 1) || (str[0] >= '0' && str[0] <= '9')) {
        if (str[0] != '-') {
            num *= 10;
            num += str[0] - '0';
        }
        for (unsigned int i = 1; i < str.length(); ++i) {
            if (str[i] < '0' || str[i] > '9') {
                return false;
            }
            num *= 10;
            num += str[i] - '0';
        }
    }
    else {
        return false;
    }

    if (num > INT_MAX) {
        throw my_exception("Stack overflow");
    }
    
    return true;
}