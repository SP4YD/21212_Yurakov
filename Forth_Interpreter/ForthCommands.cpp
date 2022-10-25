#pragma once
#include <stack> 

class ForthCommands {
public:
    virtual void Run ();

    std::stack <int> Stack;
};