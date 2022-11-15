#include "ForthCommands.hpp"

void ForthCommands::AddInputOutput (std::istream* in, std::ostream* out) {
    Input = in;
    Output = out;
}

void ForthCommands::AddStack(std::shared_ptr<std::stack <int>> stack) {
    Stack = stack;
}

void ForthCommands::AddCommandText(std::string commandText) {
    CommandText = commandText;
}

void ForthCommands::AddCommandsForSecondProcessing (std::shared_ptr<std::string> commandsForSecondProcessing) {
    CommandsForSecondProcessing = commandsForSecondProcessing;
}