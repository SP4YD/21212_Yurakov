#pragma once

#include "ForthCommands.hpp"
#include "exceptions.hpp"

class LogOperCommands: private ForthCommands { 
public:
    static ForthCommands* Creation ();

    bool Run () override;

    void LogOperMore ();

    void LogOperLess ();

    void LogOperEqually ();
};