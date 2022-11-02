#pragma once

#include "ForthCommands.hpp"
#include "exceptions.hpp"
// Contains commands that perform simple logical operations
class LogOperCommands: private ForthCommands { 
public:
    // Returns an instance of this classс
    static ForthCommands* Creation ();
    // Executing the invoked command
    bool Run () override;
    // Calculates whether the second number on the stack is greater than the first
    // Pushes the result on the stack
    // 0 - second < first
    // 1 - second > first
    void LogOperMore ();
    // Calculates whether the second number in the stack is smaller than the first
    // Pushes the result on the stack
    // 0 - second > first
    // 1 - second < first
    void LogOperLess ();
    // Compares the equality of the first number on the stack and the second
    // Pushes the result on the stack
    // 0 - second != first
    // 1 - second == first
    void LogOperEqually ();
};