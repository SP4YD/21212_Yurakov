#pragma once

#include <sstream>

#include "ForthCommands.hpp"
#include "exceptions.hpp"
// Contains a command that performs the necessary transformations with DoLoop
class OperatorDoLoop: private ForthCommands { 
public:
    // Returns an instance of this classс
    static ForthCommands* Creation ();
    // Executing the invoked command
    bool Run () override;
    // Unwinds the loop and substitutes the desired values instead of i.
    // And sends the result for secondary processing
    void DoLoop ();
};