#include "OperatorIf.hpp"

ForthCommands* OperatorIf::Creation () {
    return new OperatorIf;
}

bool OperatorIf::Run () {
    If ();
    return false;
}

void OperatorIf::If () {
    if (Stack->empty()) {
        throw my_exception (EmptyStack);    
    }
    
    std::istringstream ist (NameCommand);

    std::string tmp;
    std::string beforeElse;
    std::string afterElse;

    int countIf = 1;
    int countThen = 0;
    int countSemicolon = 0;

    while (ist >> tmp && !((countIf - countThen == 1) && (tmp == "else"))) {
        if (tmp == "if") {
            countIf++;
        }
        else if (tmp == "then") {
            countThen++;
        }

        beforeElse += tmp + " ";
    }
    beforeElse.pop_back();

    while (ist >> tmp) {
        afterElse += tmp + " ";
    }
    if (afterElse.length() > 0) {
        afterElse.pop_back();
    }

    if (Stack->top()) {
        *CommandsForSecondProcessing = beforeElse;
    }
    else {
        *CommandsForSecondProcessing = afterElse;
    }
}