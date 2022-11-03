#pragma once

#include "ForthCommands.hpp"
#include "exceptions.hpp"
// Calculates whether the second number in the stack is smaller than the first
// Pushes the result on the stack
// 0 - second > first
// 1 - second < first
class LogOperLess : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<LogOperLess> Command_logOperLess ("<");
}