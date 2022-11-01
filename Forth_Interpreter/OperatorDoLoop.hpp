#pragma once

#include <sstream>

#include "ForthCommands.hpp"
#include "exceptions.hpp"

class OperatorDoLoop: private ForthCommands { 
public:
    static ForthCommands* Creation ();

    bool Run () override;

    void DoLoop ();
};