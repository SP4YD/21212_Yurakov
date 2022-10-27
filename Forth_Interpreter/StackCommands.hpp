#pragma once

#include <iostream>

#include "ForthCommands.hpp"
#include "exceptions.hpp"
#include "FuncIsNumber.hpp"

class StackCommands: private ForthCommands {
public:
    static ForthCommands* Creation ();

    bool Run () override;

    void Push (const int a);

    void Dup ();

    void Drop ();

    void Point ();

    void Swap ();

    void Rot ();

    void Over ();

    void Emit ();

    void Cr ();
};