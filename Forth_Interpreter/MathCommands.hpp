#pragma once

#include "ForthCommands.hpp"
#include "exceptions.hpp"
// Contains commands that perform simple arithmetic operations
class MathCommands: private ForthCommands { 
public:
    // Returns an instance of this classс
    static ForthCommands* Creation ();
    // Executing the invoked command
    bool Run () override;
protected:
    // Adds the first number from the stack with the second
    // Pushes the result on the stack
    void Plus ();
    // Multiplies the first number from the stack with the second
    // Pushes the result on the stack
    void Multip ();
    // Subtracts the first number from the stack from the second
    // Pushes the result on the stack
    void Sub ();
    // Division the first number from the stack from the second
    // Pushes the result on the stack
    void Division ();
    // Calculates the remainder of dividing the second number on the stack by the first
    // Pushes the result on the stack
    void Mod ();
};