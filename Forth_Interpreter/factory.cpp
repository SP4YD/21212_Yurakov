#pragma once
#include <map>
#include <string>

#include "StackCommands.cpp"
#include "ForthCommands.cpp"

class Factory {
public:
    void RegisterCommands () {   /////////////////////////////////////////
        ExistingCommands["drop"] = StackCommands::Creation;
        ////// Прописать все
    }

    ForthCommands* CreateExecutor (const std::string NameExecutor) {
        if (ExistingCommands.find (NameExecutor) == ExistingCommands.end()) {
            throw; ///////
        }
        else {
            return ExistingCommands[NameExecutor]();
        }
    }
private:
    std::map <std::string, ForthCommands*(*)()> ExistingCommands;
};