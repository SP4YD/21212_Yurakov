#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Subtracts the first number from the stack from the second
// Pushes the result on the stack
class Sub : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Sub> Command_sub ("-");
}