#include "Forth_Interpreter.hpp"

bool ForthInterpreter(std::string str) {
    static std::shared_ptr<std::stack <int>> generalStack = std::make_shared<std::stack <int>>();
    std::shared_ptr<ForthCommands> executableCommand;
    std::string nameCommand;
    std::shared_ptr<std::string> commandsForSecondProcessing = std::make_shared<std::string>();
    bool someCout = false;

    std::vector <std::string> commands = Parser (str);


    for (unsigned int i = 0; i < commands.size(); ++i) {
        if (IsNumber(commands[i])) {
            nameCommand = commands[i];
            commands[i] = "push";
        } else if (commands[i].length() > 1 && commands[i][0] == '.' && commands[i][1] == '"') {
            nameCommand = commands[i];
            commands[i] = ".\"";
        } else if (commands[i].length() > 1 && commands[i][0] == 'i' && commands[i][1] == 'f') {
            nameCommand = commands[i];
            commands[i] = "if";
        } else if (commands[i].length() > 1 && commands[i][0] == 'd' && commands[i][1] == 'o') {
            nameCommand = commands[i];
            commands[i] = "do";
        }

        commandsForSecondProcessing->clear();
        executableCommand = (std::shared_ptr<ForthCommands>) Factory::get().CreateExecutor (commands[i]);
        executableCommand->Stack = generalStack;
        executableCommand->CommandsForSecondProcessing = commandsForSecondProcessing;
        executableCommand->NameCommand = nameCommand;
        someCout += executableCommand->Run();

        if (commandsForSecondProcessing != nullptr && commandsForSecondProcessing->length() > 0) {
            someCout += ForthInterpreter (*commandsForSecondProcessing);
        }
    }

    return someCout;
}

// int main() {
//         bool someCout;
//         std::string str;
//         std::cout << "> ";
//         while (true) {
//             getline (std::cin, str, '\n');
//             std::cout << "< ";
//             someCout = ForthInterpreter(str);

//             if (!someCout) {
//                 std::cout << "ok";
//             }

//             std:: cout << std::endl << "> ";
//         }
// }