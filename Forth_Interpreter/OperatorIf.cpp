#include "OperatorIf.hpp"

bool OperatorIf::Run () {
    CommandText.erase(CommandText.begin(), CommandText.begin() + 3);
    CommandText.erase(CommandText.end() - 7, CommandText.end());

    if (Stack->empty()) {
        throw Exception_EmptyStack();    
    }
    
    std::istringstream ist (CommandText);

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
