#pragma once

#include <map>
#include <string>

#include "StackCommands.hpp"
#include "MathCommands.hpp"
#include "LogOperCommands.hpp"
#include "PrintingLine.hpp"

class Factory {
public:
    void RegistrationCommands ();

    ForthCommands* CreateExecutor (std::string& NameExecutor);
private:
    std::map <std::string, ForthCommands*(*)()> ExistingCommands;
};