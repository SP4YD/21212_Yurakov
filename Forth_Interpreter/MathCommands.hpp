#pragma once

#include <iostream> //////////////////////////////////////trash

#include "ForthCommands.hpp"
#include "exceptions.hpp"

class MathCommands: private ForthCommands { 
public:
    static ForthCommands* Creation ();

    bool Run () override;

    void Plus ();

    void Multip ();

    void Sub ();

    void Division ();

    void Mod ();
};