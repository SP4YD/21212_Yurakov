#include "OperatorDoLoop.hpp"

#include <sstream>
#include <vector>

bool OperatorDoLoop::Run () {
    GeneralDataForExecutors.CommandText.erase(GeneralDataForExecutors.CommandText.begin(), GeneralDataForExecutors.CommandText.begin() + 3);
    GeneralDataForExecutors.CommandText.erase(GeneralDataForExecutors.CommandText.end() - 7, GeneralDataForExecutors.CommandText.end());
    
    (*GeneralDataForExecutors.CommandsForSecondProcessing).clear();

    if (GeneralDataForExecutors.Stack->empty()) {
        throw Exception_EmptyStack();    
    }

    int i = GeneralDataForExecutors.Stack->top();
    GeneralDataForExecutors.Stack->pop();

    if (GeneralDataForExecutors.Stack->empty()) {
        throw Exception_EmptyStack();    
    }

    int N = GeneralDataForExecutors.Stack->top();
    GeneralDataForExecutors.Stack->pop();

    std::istringstream ist (GeneralDataForExecutors.CommandText);
    std::string tmp;
    std::vector <int> indexesI;
    int balanceDoLoop = 1;
    bool flagDoubleQuotes = false;
    int indexNow = -1;

    while (ist >> tmp) {
        indexNow += tmp.length();

        if (tmp == ".\"") {
            flagDoubleQuotes = true;
        }
        else if (tmp[tmp.length() - 1] == '"') {
            flagDoubleQuotes = false;
        }

        if (!flagDoubleQuotes) {
            if (tmp == "do") {
                balanceDoLoop++;
            }
            else if (tmp == "loop") {
                balanceDoLoop--;
            }
            else if (balanceDoLoop == 1 && tmp == "i") {
                indexesI.push_back(indexNow);
            }
        }

        indexNow++;
    }

    std::string result;
    std::string pattern = GeneralDataForExecutors.CommandText;

    for (; i < N; ++i) {
        GeneralDataForExecutors.CommandText = pattern;
        std::ostringstream ost;
        ost << i;

        for (int j = indexesI.size() - 1; j >= 0 ; --j) {
            GeneralDataForExecutors.CommandText.replace(indexesI[j], 1, ost.str());
        }

        result += GeneralDataForExecutors.CommandText + " ";
    }

    if (result.length() > 0) {
        result.pop_back();
    }

    *GeneralDataForExecutors.CommandsForSecondProcessing = result;

    return false;
}

namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<OperatorDoLoop> Command_do ("do");
}