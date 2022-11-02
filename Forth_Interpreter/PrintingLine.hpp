#pragma once

#include <iostream>

#include "ForthCommands.hpp"
// Contains a command that outputs a string
class PrintingLine: private ForthCommands {
public:
    // Returns an instance of this classс
    static ForthCommands* Creation ();
    // Executing the invoked command
    bool Run () override;
private:
    // Prints the specified string (without quotes)
    void Print (std::string str);
};