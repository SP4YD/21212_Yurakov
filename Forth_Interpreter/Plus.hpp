#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Adds the first number from the stack with the second
// Pushes the result on the stack
class Plus : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};