#include "Forth_Interpreter.hpp"

int main() {
    Factory factory;
    std::stack <int>* generalStack = new std::stack <int>;

    factory.RegistrationCommands();

    while (true) {
        ForthCommands* executableCommand;
        std::string str;
        std::cout << "> ";
        bool someCout = false;
        getline (std::cin, str, '\n');

        std::vector <std::string> commands = parser (str);
        for (int i = 0; i < commands.size(); ++i) {
            executableCommand = factory.CreateExecutor (commands[i]);
            executableCommand->Stack = generalStack;
            executableCommand->NameCommand = commands[i];
            someCout += executableCommand->Run();
            delete executableCommand;
        }

        if (!someCout) {
            std::cout << "< ok" << std::endl;
        }
    }
    
    return 0;
}