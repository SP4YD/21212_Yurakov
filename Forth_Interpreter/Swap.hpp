#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Swaps the top and second numbers on the stack
class Swap : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};