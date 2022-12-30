#pragma once

#include <stack>
#include <string>

// A common set of data required by executor
class GeneralData {
public:
    GeneralData () = default;
    GeneralData (std::stack <int> *stack, std::string commandText, 
                 std::string *commandsForSecondProcessing, std::istream *in, std::ostream *out);
    // Link to the general stack of the program
    std::stack <int> *Stack;
    // The name of the command to be executed or processed
    std::string CommandText;
    // A reference to a string that stores commands that need to be processed a second time
    std::string *CommandsForSecondProcessing;

    std::istream *Input;
    std::ostream *Output;
};
// Interface, with a basic set of functions and variables required by commands
class ForthCommands {
public:
    ForthCommands() = default;

    virtual ~ForthCommands() = default;

    // Executing the invoked command
    virtual bool Run () = 0;
    // Uploading basic data to the executor
    void AddGeneralData (GeneralData gendata);
protected:
    GeneralData GeneralDataForExecutors;
};