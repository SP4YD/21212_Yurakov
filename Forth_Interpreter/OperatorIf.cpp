#include "OperatorIf.hpp"

bool OperatorIf::Run () {
    NameCommand.erase(NameCommand.begin(), NameCommand.begin() + 3);
    NameCommand.erase(NameCommand.end() - 7, NameCommand.end());

    if (Stack->empty()) {
        throw my_exception (EmptyStack);    
    }
    
    std::istringstream ist (NameCommand);

    std::string tmp;
    std::string beforeElse;
    std::string afterElse;

    int balanceIfThen = 1;

    while (ist >> tmp && !((balanceIfThen == 1) && (tmp == "else"))) {
        if (tmp == "if") {
            balanceIfThen++;
        }
        else if (tmp == "then") {
            balanceIfThen--;
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

    return false;
}
