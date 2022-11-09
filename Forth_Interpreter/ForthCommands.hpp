#pragma once

#include <stack>
#include <string>
#include <vector>
#include <memory>

#include "FactoryRegistrationCommands.hpp"
// Interface, with a basic set of functions and variables required by commands
class ForthCommands {
public:
    // Executing the invoked command
    virtual bool Run () = 0;
    // Link to the general stack of the program
     std::shared_ptr<std::stack <int>> Stack;
    // The name of the command to be executed or processed
    std::string NameCommand;
    // A reference to a string that stores commands that need to be processed a second time
    std::shared_ptr<std::string> CommandsForSecondProcessing;
};