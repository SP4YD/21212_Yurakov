#pragma once

#include <iostream>

#include "ForthCommands.hpp"
#include "exceptions.hpp"
// Prints the top number on the stack as an ASCII code and removes it from the stack
class Emit : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Emit> Command_emit ("emit");
}