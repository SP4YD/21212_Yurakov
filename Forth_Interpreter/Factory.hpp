#pragma once

#include <string>
#include <map>
#include <utility>

#include "exceptions.hpp"
 // The factory was taken from the https://derydoca.com/2019/03/c-tutorial-auto-registering-factory/
class ForthCommands;
 
typedef ForthCommands*(*ForthExecutorsGenerator)();

class Factory {
public:
    // Returns the only shared instance of the factory
    static Factory& get();
    // Creates the executor of the required command
    ForthCommands* CreateExecutor(std::string& NameExecutor);
    // Registers functions in the database
    bool RegisterGenerator(std::string typeName, const ForthExecutorsGenerator& funcCreate);
private:
    Factory() = default;
    Factory(const Factory&);
    ~Factory() = default;;

    std::map<std::string, ForthExecutorsGenerator> ExistingCommands;
};