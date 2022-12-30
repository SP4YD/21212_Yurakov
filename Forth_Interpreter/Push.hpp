#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Push number on stack
// Pushes the result on the stack
class Push : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};