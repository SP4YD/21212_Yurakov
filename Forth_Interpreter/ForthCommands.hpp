#pragma once
#include <stack>
#include <string>

class ForthCommands {
public:
    virtual bool Run () = 0;

    std::stack <int>* Stack;
    std::string NameCommand;
};