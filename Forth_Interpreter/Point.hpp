#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Prints the top number from the stack, and removes it
class Point : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};