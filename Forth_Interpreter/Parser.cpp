#include "Parser.hpp"

#include <iostream> ////////TRASH TRASH TRASH TRASH TRASH TRASH TRASH TRASH TRASH TRASH TRASH TRASH TRASH TRASH TRASH 

std::vector <std::string> parser (const std::string str) {
    std::istringstream ist (str);
    std::vector <std::string> splitStr;

    std::string tmp;

    while (ist >> tmp) {
        std::string result;
        if (tmp == ".\"") {
            result = tmp;

            while ((ist >> tmp) && (tmp[tmp.size() - 1] != '"')) {
                result += " " + tmp;
            }

            splitStr.push_back (result + " " + tmp);
            result.clear();

            if (splitStr[splitStr.size() - 1].back() != '"') {
                throw my_exception ("Not found closing quotes");
            }
        }
        else if (tmp == "if") {
            ParserIf (result, tmp, ist, splitStr);
        }
        else if (tmp == "do") {
            ParserDo (result, tmp, ist, splitStr);
        }
        else {
           splitStr.push_back (tmp); 
        }   
    }

    return splitStr;
}

void ParserIf (std::string& result,
               std::string& tmp, 
               std::istringstream& ist, 
               std::vector <std::string>& splitStr) {
    result = tmp;
    int countIf = 1;
    int countThen = 0;
    int countSemicolon = 0;
    int countElse = 0;
    bool flagDoubleQuotes = false;

    while (((countIf != countThen) || (countIf != countSemicolon)) && (countIf >= countElse) && ist >> tmp) {
        if (tmp == ".\"") {
            flagDoubleQuotes = true;
        }
        else if (tmp[tmp.length() - 1] == '"') {
            flagDoubleQuotes = false;
        }

        if (!flagDoubleQuotes) {
            if (tmp == "if") {
                countIf++;
            }
            else if (tmp == "else") {
                countElse++;
            }
            else if (tmp == "then") {
                countThen++;
            }
            else if (tmp == ";") {
                countSemicolon++;
            }
        }

        result += " " + tmp;
    }

    splitStr.push_back (result);
    result.clear();

    if (countElse > countIf) {
        throw my_exception ("Amount \"else\" turned out to be more than \"if\"");
    }
    if (countIf > countThen) { 
        throw my_exception ("Not found closing \"then\"");
    }
    else if (countIf < countThen) {
        throw my_exception ("Amount \"then\" turned out to be more than \"if\"");
    }
    else if (countIf > countSemicolon) {
        throw my_exception ("Not found closing \";\"");
    }
    else if (countIf < countSemicolon) {
        throw my_exception ("Amount \";\" turned out to be more than \"if\"");
    }
}

void ParserDo (std::string& result,
               std::string& tmp, 
               std::istringstream& ist, 
               std::vector <std::string>& splitStr) {
    result = tmp;
    int countDo = 1;
    int countLoop = 0;
    int countSemicolon = 0;
    int countThen = 0;
    bool flagDoubleQuotes = false;

    while (((countDo != countLoop) || (countDo != (countSemicolon - countThen))) && ist >> tmp) {
        if (tmp == ".\"") {
            flagDoubleQuotes = true;
        }
        else if (tmp[tmp.length() - 1] == '"') {
            flagDoubleQuotes = false;
        }

        if (!flagDoubleQuotes) {
            if (tmp == "do") {
                countDo++;
            }
            else if (tmp == "loop") {
                countLoop++;
            }
            else if (tmp == "then") {
                countThen++;
            }
            else if (tmp == ";") {
                countSemicolon++;
            }
        }

        result += " " + tmp;
    }

    splitStr.push_back (result);
    result.clear();

    if (countDo > countLoop) { 
        throw my_exception ("Not found closing \"loop\"");
    }
    else if (countDo < countLoop) {
        throw my_exception ("Amount \"loop\" turned out to be more than \"do\"");
    }
    else if (countDo > (countSemicolon - countThen)) {
        throw my_exception ("Not found closing \";\"");
    }
    else if (countDo < (countSemicolon - countThen)) {
        throw my_exception ("Amount \";\" turned out to be more than \"do\"");
    }
}