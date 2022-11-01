#include "Factory.hpp"

ForthCommands* Factory::HandlingSpecialCases (std::string& NameExecutor) {
    if (IsNumber(NameExecutor)) {
        return StackCommands::Creation();
    }
    else if (NameExecutor.length() > 1 && NameExecutor[0] == '.' && NameExecutor[1] == '"') {
        NameExecutor.erase(NameExecutor.begin(), NameExecutor.begin() + 3);
        
        return ExistingCommands[".\""]();
    }
    else if (NameExecutor.length() > 1 && NameExecutor[0] == 'i' && NameExecutor[1] == 'f') {
        NameExecutor.erase(NameExecutor.begin(), NameExecutor.begin() + 3);
        NameExecutor.erase(NameExecutor.end() - 7, NameExecutor.end());

        return ExistingCommands["if"]();
    }
    else if (NameExecutor.length() > 1 && NameExecutor[0] == 'd' && NameExecutor[1] == 'o') {
        NameExecutor.erase(NameExecutor.begin(), NameExecutor.begin() + 3);
        NameExecutor.erase(NameExecutor.end() - 7, NameExecutor.end());

        return ExistingCommands["do"]();
    }
    else {
        throw my_exception(UnknownCommand); 
    }
}
