#pragma once

#include <vector>

#include "ForthCommands.hpp"
#include "Parser.hpp"
#include "exceptions.hpp"

class OperatorIf: private ForthCommands { 
public:
    static ForthCommands* Creation ();

    bool Run () override;

    void If ();
};