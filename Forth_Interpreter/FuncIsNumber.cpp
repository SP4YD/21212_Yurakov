#include "FuncIsNumber.hpp"

bool IsNumber(std::string str) {
    if (str[0] == '-' || (str[0] >= '0' && str[0] <= '9')) {
        for (int i = 1; i < str.length(); ++i) {
            if (str[i] < '0' || str[i] > '9') {
                return false;
            }
        }
    }
    else {
        return false;
    }
    
    return true;
}