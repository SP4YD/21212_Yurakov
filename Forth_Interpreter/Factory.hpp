#pragma once

#include <string>
#include <map>
#include <utility>
 // The factory was taken from the https://derydoca.com/2019/03/c-tutorial-auto-registering-factory/
class ForthCommands;
 
typedef ForthCommands*(*ForthExecutorsGenerator)();

class Factory {
public:
    static Factory& get();
 
    ForthCommands* CreateExecutor(std::string& NameExecutor);
 
    bool RegisterGenerator(std::string typeName, const ForthExecutorsGenerator& funcCreate);
private:
    Factory() = default;
    Factory(const Factory&);
    ~Factory() = default;;
 
    std::map<std::string, ForthExecutorsGenerator> ExistingCommands;
};