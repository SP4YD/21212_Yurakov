#pragma once

#include "ForthCommands.hpp"
#include "exceptions.hpp"
// Copies the top of the stack and puts it on the top of the stack
class Dup : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Dup> Command_dup ("dup");
}