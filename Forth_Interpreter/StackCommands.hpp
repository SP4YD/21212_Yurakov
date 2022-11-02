#pragma once

#include <iostream>

#include "ForthCommands.hpp"
#include "exceptions.hpp"
#include "FuncIsNumber.hpp"
//Contains commands that perform simple stack operations
class StackCommands: private ForthCommands {
public:
    // Returns an instance of this classс
    static ForthCommands* Creation ();
    // Executing the invoked command
    bool Run () override;
    // Push number on stack
    // Pushes the result on the stack
    void Push (const int a);
    // Copies the top of the stack and puts it on the top of the stack
    void Dup ();
    // Removes the top number from the stack
    void Drop ();
    // Prints the top number from the stack, and removes it
    void Point ();
    // Swaps the top and second numbers on the stack
    void Swap ();
    // Cyclically shifts the top three numbers
    void Rot ();
    // Copies the second number and puts a copy over the top one
    void Over ();
    // Prints the top number on the stack as an ASCII code and removes it from the stack
    void Emit ();
    // Moves to the next line
    void Cr ();
};