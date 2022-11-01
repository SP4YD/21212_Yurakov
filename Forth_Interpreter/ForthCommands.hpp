#pragma once

#include <stack>
#include <string>
#include <vector>

class ForthCommands {
public:
    virtual bool Run () = 0;

    std::stack <int>* Stack;
    std::string NameCommand;
    std::string* CommandsForSecondProcessing;
};