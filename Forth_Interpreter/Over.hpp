#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Copies the second number and puts a copy over the top one
class Over : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};