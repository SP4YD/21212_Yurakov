#pragma once

#include <map>
#include <string>
#include <memory>

#include "StackCommands.hpp"
#include "MathCommands.hpp"
#include "LogOperCommands.hpp"
#include "PrintingLine.hpp"
#include "OperatorIf.hpp"
#include "OperatorDoLoop.hpp"
// Factory, stores and creates all executors
class Factory {
public:
    // Registers the names of teams and their executors
    void RegistrationCommands ();
    // Creates executors and returns them
    ForthCommands* CreateExecutor (std::string& NameExecutor);
    // Handles special cases and returns executors
    ForthCommands* HandlingSpecialCases (std::string& NameExecutor);
private:
    // Map storing existing commands
    // Returns executor by command name
    std::map <std::string, ForthCommands*(*)()> ExistingCommands;
};