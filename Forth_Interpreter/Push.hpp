#pragma once

#include <climits>

#include "ForthCommands.hpp"
// Push number on stack
// Pushes the result on the stack
class Push : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Push> Command_push ("push");
}