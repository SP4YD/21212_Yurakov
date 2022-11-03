#include "Forth_Interpreter.hpp"



int main() {
    std::stack <int>* generalStack = new std::stack <int>;

    while (true) {
        ForthCommands* executableCommand;
        std::string str;
        std::string nameCommand;
        std::string* commandsForSecondProcessing = new std::string();
        std::cout << "> ";
        bool someCout = false;
        getline (std::cin, str, '\n');

        std::vector <std::string> commands = Parser (str);
        std::cout << "< ";

        for (int i = 0; i < commands.size(); ++i) {
            if (IsNumber(commands[i])) {
                nameCommand = commands[i];
                commands[i] = "push";
            } else if (commands[i].length() > 1 && commands[i][0] == '.' && commands[i][1] == '"') {
                commands[i].erase(commands[i].begin(), commands[i].begin() + 3);
                
                nameCommand = commands[i];
                commands[i] = ".\"";
            } else if (commands[i].length() > 1 && commands[i][0] == 'i' && commands[i][1] == 'f') {
                commands[i].erase(commands[i].begin(), commands[i].begin() + 3);
                commands[i].erase(commands[i].end() - 7, commands[i].end());

                nameCommand = commands[i];
                commands[i] = "if";
            } else if (commands[i].length() > 1 && commands[i][0] == 'd' && commands[i][1] == 'o') {
                commands[i].erase(commands[i].begin(), commands[i].begin() + 3);
                commands[i].erase(commands[i].end() - 7, commands[i].end());

                nameCommand = commands[i];
                commands[i] = "do";
            }

            commandsForSecondProcessing->clear();
            executableCommand = Factory::get().CreateExecutor (commands[i]);
            executableCommand->Stack = generalStack;
            executableCommand->CommandsForSecondProcessing = commandsForSecondProcessing;
            executableCommand->NameCommand = nameCommand;
            someCout += executableCommand->Run();
            //std::cout << "namecommand: " << commands[i] << std::endl;
            if (commandsForSecondProcessing != nullptr && commandsForSecondProcessing->length() > 0) {
                //std::cout << "Begin secondaryprocessing" << std::endl;
                someCout += SecondaryProcessing (commandsForSecondProcessing, generalStack);
                //std::cout << "End secondaryprocessing" << std::endl;
            }

            delete executableCommand;
        }

        if (!someCout) {
            std::cout << "ok";
        }

        std:: cout << std::endl;

        delete commandsForSecondProcessing;
    }

    delete generalStack;
    
    return 0;
}

bool SecondaryProcessing (std::string* comm, std::stack <int>* generalStack) {
    ForthCommands* executableCommand;
    std::string nameCommand;
    std::string* commandsForSecondProcessing = new std::string();
    std::vector <std::string> commands = Parser (*comm);
    bool someCout = 0;

    for (int i = 0; i < commands.size(); ++i) {
        //std::cout << "commands[i]: " << commands[i] << std::endl;
        if (IsNumber(commands[i])) {
            nameCommand = commands[i];
            commands[i] = "push";
        } else if (commands[i].length() > 1 && commands[i][0] == '.' && commands[i][1] == '"') {
            commands[i].erase(commands[i].begin(), commands[i].begin() + 3);
            
            nameCommand = commands[i];
            commands[i] = ".\"";
        } else if (commands[i].length() > 1 && commands[i][0] == 'i' && commands[i][1] == 'f') {
            commands[i].erase(commands[i].begin(), commands[i].begin() + 3);
            commands[i].erase(commands[i].end() - 7, commands[i].end());

            nameCommand = commands[i];
            commands[i] = "if";
        } else if (commands[i].length() > 1 && commands[i][0] == 'd' && commands[i][1] == 'o') {
            commands[i].erase(commands[i].begin(), commands[i].begin() + 3);
            commands[i].erase(commands[i].end() - 7, commands[i].end());

            nameCommand = commands[i];
            commands[i] = "do";
        }

        commandsForSecondProcessing->clear();
        executableCommand = Factory::get().CreateExecutor (commands[i]);
        executableCommand->Stack = generalStack;
        executableCommand->CommandsForSecondProcessing = commandsForSecondProcessing;
        executableCommand->NameCommand = nameCommand;
        someCout += executableCommand->Run();

        //std::cout << "namecommand: " << commands[i] << std::endl;
            if (commandsForSecondProcessing != nullptr && commandsForSecondProcessing->length() > 0) {
                //std::cout << "Begin secondaryprocessing" << std::endl;
                someCout += SecondaryProcessing (commandsForSecondProcessing, generalStack);
                //std::cout << "End secondaryprocessing" << std::endl;
            }

        delete executableCommand;
    }

    delete commandsForSecondProcessing;

    return someCout;
}