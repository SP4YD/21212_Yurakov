#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Calculates whether the second number on the stack is greater than the first
// Pushes the result on the stack
// 0 - second < first
// 1 - second > first
class LogOperMore : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};