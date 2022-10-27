#include "Parser.hpp"
#include <iostream>

std::vector <std::string> parser (std::string str) {
    std::istringstream ist (str);
    std::vector <std::string> splitStr;

    std::string tmp;

    while (ist >> tmp) {
        std::string patern = ".";
        patern += '"';
        std::string result = patern + ' ';
        if (tmp == patern) {
            while ((ist >> tmp) && (tmp[tmp.size() - 1] != '"')) {
                result += " " + tmp;
            }

            splitStr.push_back (result + " " + tmp);
            result.clear();

            if (splitStr[splitStr.size() - 1].back() != '"') {
                throw my_exception ("Not found closing quotes");
            }
        }
        else {
           splitStr.push_back (tmp); 
        }   
    }

    return splitStr;
}