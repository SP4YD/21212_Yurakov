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

    ExistingCommands[".\""] = PrintingLine::Creation;

    ExistingCommands["if"] = OperatorIf::Creation;

    ExistingCommands["do"] = OperatorDoLoop::Creation;
}

ForthCommands* Factory::CreateExecutor (std::string& NameExecutor) {
    if (ExistingCommands.find (NameExecutor) != ExistingCommands.end()) {
        return ExistingCommands[NameExecutor]();
    }
    else {
        return HandlingSpecialCases (NameExecutor);
    }
}