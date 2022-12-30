#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// if THEN_BRANCH then ;
// If there is > 0 on the stack, THEN_BRANCH goes to secondary processing, else nothing
//
// if THEN_BRANCH else ELSE_BRANCH then ;
// If there is > 0 on the stack, THEN_BRANCH goes to secondary processing, else ELSE_BRANCH
class OperatorIf: public ForthCommands { 
public:
    // Executing the invoked command
    bool Run () override;
};