#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Multiplies the first number from the stack with the second
// Pushes the result on the stack
class Multip : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};