#include "Factory.hpp"

void Factory::RegistrationCommands () { 
    ExistingCommands["dup"] = StackCommands::Creation;
    ExistingCommands["drop"] = StackCommands::Creation;
    ExistingCommands["."] = StackCommands::Creation;
    ExistingCommands["swap"] = StackCommands::Creation;
    ExistingCommands["rot"] = StackCommands::Creation;
    ExistingCommands["over"] = StackCommands::Creation;
    ExistingCommands["emit"] = StackCommands::Creation;
    ExistingCommands["cr"] = StackCommands::Creation;

    ExistingCommands["+"] = MathCommands::Creation;
    ExistingCommands["*"] = MathCommands::Creation;
    ExistingCommands["-"] = MathCommands::Creation;
    ExistingCommands["/"] = MathCommands::Creation;
    ExistingCommands["mod"] = MathCommands::Creation;

    ExistingCommands[">"] = LogOperCommands::Creation;
    ExistingCommands["<"] = LogOperCommands::Creation;
    ExistingCommands["="] = LogOperCommands::Creation;

    ExistingCommands["." + '"'] = PrintLine::Creation;
}

ForthCommands* Factory::CreateExecutor (std::string& NameExecutor) {
    if (NameExecutor.size() > 1 && NameExecutor[0] == '.' && NameExecutor[1] == '"') {
        NameExecutor.erase(NameExecutor.begin(), NameExecutor.begin() + 4);
        
        return ExistingCommands["." + '"']();
    }
    if (ExistingCommands.find (NameExecutor) == ExistingCommands.end()) {
        if (IsNumber(NameExecutor)) {
            return StackCommands::Creation();
        }
        else {
            throw my_exception(UnknownCommand); 
        }
    }
    else {
        return ExistingCommands[NameExecutor]();
    }
}