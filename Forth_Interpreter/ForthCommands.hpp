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
    // Changes Stack to incoming
    void AddStack(std::shared_ptr<std::stack <int>> stack);
    // Changes CommandText to incoming
    void AddCommandText(std::string commandText);
    // Changes CommandsForSecondProcessing to incoming
    void AddCommandsForSecondProcessing (std::shared_ptr<std::string> commandsForSecondProcessing);
    // Changes Input and Output to incoming
    void AddInputOutput (std::istream* in, std::ostream* out);
protected:
    // Link to the general stack of the program
    std::shared_ptr<std::stack <int>> Stack;
    // The name of the command to be executed or processed
    std::string CommandText;
    // A reference to a string that stores commands that need to be processed a second time
    std::shared_ptr<std::string> CommandsForSecondProcessing;

    std::istream* Input;
    std::ostream* Output;
};