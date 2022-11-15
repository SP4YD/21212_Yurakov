#include "OperatorDoLoop.hpp"

bool OperatorDoLoop::Run () {
    int i;
    int N;

    CommandText.erase(CommandText.begin(), CommandText.begin() + 3);
    CommandText.erase(CommandText.end() - 7, CommandText.end());
    
    (*CommandsForSecondProcessing).clear();

    if (Stack->empty()) {
        throw Exception_EmptyStack();    
    }

    i = Stack->top();
    Stack->pop();

    if (Stack->empty()) {
        throw Exception_EmptyStack();    
    }

    N = Stack->top();
    Stack->pop();

    std::istringstream ist (CommandText);
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
    std::string pattern = CommandText;

    for (; i < N; ++i) {
        CommandText = pattern;
        std::ostringstream ost;
        ost << i;

        for (int j = indexesI.size() - 1; j >= 0 ; --j) {
            CommandText.replace(indexesI[j], 1, ost.str());
        }

        result += CommandText + " ";
    }

    if (result.length() > 0) {
        result.pop_back();
    }

    *CommandsForSecondProcessing = result;

    return false;
}