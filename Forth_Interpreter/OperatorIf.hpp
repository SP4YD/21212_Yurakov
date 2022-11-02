#pragma once

#include <vector>

#include "ForthCommands.hpp"
#include "Parser.hpp"
#include "exceptions.hpp"
// Contains a command that performs the necessary transformations with If
class OperatorIf: private ForthCommands { 
public:
    // Returns an instance of this classс
    static ForthCommands* Creation ();
    // Executing the invoked command
    bool Run () override;
    // if THEN_BRANCH then ;
    // If there is > 0 on the stack, THEN_BRANCH goes to secondary processing, else nothing
    //
    // if THEN_BRANCH else ELSE_BRANCH then ;
    // If there is > 0 on the stack, THEN_BRANCH goes to secondary processing, else ELSE_BRANCH
    void If ();
};