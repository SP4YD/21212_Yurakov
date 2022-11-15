#include "Factory.hpp"

Factory& Factory::get() {
    static Factory instance;
    return instance;
}

ForthCommands* Factory::CreateExecutor(std::string& NameExecutor) {
    if (ExistingCommands.find (NameExecutor) != ExistingCommands.end()) {
        return ExistingCommands[NameExecutor]();
    }
    else {
        throw Exception_UnknownCommand();
    }
 
    return nullptr;
}

bool Factory::RegisterGenerator(std::string NameCommand, const ForthExecutorsGenerator& funcCreate) {
    return ExistingCommands.insert(std::pair<std::string, ForthExecutorsGenerator> (NameCommand, funcCreate)).second;
}