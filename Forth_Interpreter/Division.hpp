#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Division the first number from the stack from the second
// Pushes the result on the stack
class Division : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};