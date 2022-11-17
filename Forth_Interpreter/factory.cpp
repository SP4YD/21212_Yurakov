#include "Factory.hpp"

Factory& Factory::get() {
    static Factory instance;
    return instance;
}

ForthCommands* Factory::CreateInstance(const std::string NameInstance) {
    if (ExistingCommands.find (NameInstance) != ExistingCommands.end()) {
        return ExistingCommands[NameInstance]();
    }
    else {
        throw Exception_UnknownCommand();
    }
 
    return nullptr;
}

bool Factory::RegisterGenerator(const std::string NameCommand, const ForthExecutorsGenerator& funcCreate) {
    return ExistingCommands.insert(std::pair<std::string, ForthExecutorsGenerator> (NameCommand, funcCreate)).second;
}