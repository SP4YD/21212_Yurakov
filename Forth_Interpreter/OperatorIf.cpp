#include "OperatorIf.hpp"

#include <memory>
#include <sstream>

bool OperatorIf::Run () {
    GeneralDataForExecutors.CommandText.erase(GeneralDataForExecutors.CommandText.begin(), GeneralDataForExecutors.CommandText.begin() + 3);
    GeneralDataForExecutors.CommandText.erase(GeneralDataForExecutors.CommandText.end() - 7, GeneralDataForExecutors.CommandText.end());

    if (GeneralDataForExecutors.Stack->empty()) {
        throw Exception_EmptyStack();    
    }
    
    std::istringstream ist (GeneralDataForExecutors.CommandText);

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

    if (GeneralDataForExecutors.Stack->top()) {
        *GeneralDataForExecutors.CommandsForSecondProcessing = beforeElse;
    }
    else {
        *GeneralDataForExecutors.CommandsForSecondProcessing = afterElse;
    }

    return false;
}

namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<OperatorIf> Command_if ("if");
}