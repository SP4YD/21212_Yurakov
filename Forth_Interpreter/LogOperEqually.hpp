#pragma once

#include "ForthCommands.hpp"
#include "exceptions.hpp"
// Compares the equality of the first number on the stack and the second
// Pushes the result on the stack
// 0 - second != first
// 1 - second == first
class LogOperEqually : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<LogOperEqually> Command_logOperEqually ("=");
}