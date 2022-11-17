#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Unwinds the loop and substitutes the desired values instead of i.
// And sends the result for secondary processing
class OperatorDoLoop: public ForthCommands { 
public:
    // Executing the invoked command
    bool Run () override;
};

namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<OperatorDoLoop> Command_do ("do");
}