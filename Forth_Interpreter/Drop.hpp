#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Removes the top number from the stack
class Drop : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};