#include "OperatorDoLoop.hpp"

ForthCommands* OperatorDoLoop::Creation () {
    return new OperatorDoLoop;
}

bool OperatorDoLoop::Run () {
    DoLoop ();

    return false;
}

void OperatorDoLoop::DoLoop () {
    int i;
    int N;
    
    (*CommandsForSecondProcessing).clear();

    if (Stack->empty()) {
        throw my_exception (EmptyStack);    
    }

    i = Stack->top();
    Stack->pop();

    if (Stack->empty()) {
        throw my_exception (EmptyStack);    
    }

    N = Stack->top();
    Stack->pop();

    std::istringstream ist (NameCommand);
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
    std::string pattern = NameCommand;

    for (; i < N; ++i) {
        NameCommand = pattern;
        std::ostringstream ost;
        ost << i;

        for (int j = indexesI.size() - 1; j >= 0 ; --j) {
            NameCommand.replace(indexesI[j], 1, ost.str());
        }

        result += NameCommand + " ";
    }

    if (result.length() > 0) {
        result.pop_back();
    }

    *CommandsForSecondProcessing = result;
}