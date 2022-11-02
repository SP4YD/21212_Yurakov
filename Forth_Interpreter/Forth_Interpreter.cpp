#include "Forth_Interpreter.hpp"

int main() {
    Factory factory;
    std::stack <int>* generalStack = new std::stack <int>;

    factory.RegistrationCommands();

    while (true) {
        ForthCommands* executableCommand;
        std::string str;
        std::string* commandsForSecondProcessing = new std::string();
        std::cout << "> ";
        bool someCout = false;
        getline (std::cin, str, '\n');

        std::vector <std::string> commands = Parser (str);
        std::cout << "< ";

        for (int i = 0; i < commands.size(); ++i) {
            commandsForSecondProcessing->clear();
            executableCommand = factory.CreateExecutor (commands[i]);
            executableCommand->Stack = generalStack;
            executableCommand->CommandsForSecondProcessing = commandsForSecondProcessing;
            executableCommand->NameCommand = commands[i];
            someCout += executableCommand->Run();

            if (commandsForSecondProcessing != nullptr && commandsForSecondProcessing->length() > 0) {
                someCout += SecondaryProcessing (commandsForSecondProcessing, generalStack, factory);
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

bool SecondaryProcessing (std::string* comm, std::stack <int>* generalStack, Factory& factory) {
    ForthCommands* executableCommand;
    std::string* commandsForSecondProcessing = new std::string();
    std::vector <std::string> commands = Parser (*comm);
    bool someCout = 0;

    for (int i = 0; i < commands.size(); ++i) {
        commandsForSecondProcessing->clear();
        executableCommand = factory.CreateExecutor (commands[i]);
        executableCommand->Stack = generalStack;
        executableCommand->CommandsForSecondProcessing = commandsForSecondProcessing;
        executableCommand->NameCommand = commands[i];
        someCout += executableCommand->Run();

        if (commandsForSecondProcessing->length() > 0) {
            someCout += SecondaryProcessing (commandsForSecondProcessing, generalStack, factory);
        }

        delete executableCommand;
    }

    delete commandsForSecondProcessing;

    return someCout;
}