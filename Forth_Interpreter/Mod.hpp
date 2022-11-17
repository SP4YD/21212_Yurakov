#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Calculates the remainder of dividing the second number on the stack by the first
// Pushes the result on the stack
class Mod : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Mod> Command_mod ("mod");
}