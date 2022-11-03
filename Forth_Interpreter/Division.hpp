#pragma once

#include "ForthCommands.hpp"
#include "exceptions.hpp"
// Division the first number from the stack from the second
// Pushes the result on the stack
class Division : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Division> Command_division ("/");
}