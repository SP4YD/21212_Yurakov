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

class Factory {
public:
    void RegistrationCommands ();

    ForthCommands* CreateExecutor (std::string& NameExecutor);
    ForthCommands* HandlingSpecialCases (std::string& NameExecutor);
private:
    std::map <std::string, ForthCommands*(*)()> ExistingCommands;
};