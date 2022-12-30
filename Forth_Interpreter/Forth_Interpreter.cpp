#include "Factory.hpp"
#include "Forth_Interpreter.hpp"
#include "FuncIsNumber.hpp"
#include "Parser.hpp"

#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

bool ForthInterpreter::InterpretCommand(const std::string &str) {
    std::unique_ptr<ForthCommands> executableCommand;
    std::string commandText;
    std::unique_ptr<std::string> commandsForSecondProcessing = std::make_unique<std::string>();
    bool someCout = false;

    std::vector <std::string> commands = Parser (str);

    GeneralData gendata (Stack.get(), commandText, 
                         commandsForSecondProcessing.get(), &In, &Out);

    for (unsigned int i = 0; i < commands.size(); ++i) {
        if (IsNumber(commands[i])) {
            gendata.CommandText = commands[i];
            commands[i] = "push";
        } else if (commands[i].length() > 1 && commands[i][0] == '.' && commands[i][1] == '"') {
            gendata.CommandText = commands[i];
            commands[i] = ".\"";
        } else if (commands[i].length() > 1 && commands[i][0] == 'i' && commands[i][1] == 'f') {
            gendata.CommandText = commands[i];
            commands[i] = "if";
        } else if (commands[i].length() > 1 && commands[i][0] == 'd' && commands[i][1] == 'o') {
            gendata.CommandText = commands[i];
            commands[i] = "do";
        }

        commandsForSecondProcessing->clear();
        executableCommand.reset(Factory::get().CreateInstance (commands[i]));
        executableCommand->AddGeneralData (gendata);
        someCout += executableCommand->Run();

        if (commandsForSecondProcessing != nullptr && commandsForSecondProcessing->length() > 0) {
            someCout += InterpretCommand (*commandsForSecondProcessing);
        }
    }

    return someCout;
}

ForthInterpreter::ForthInterpreter(std::istream& in, std::ostream& out) : In (in), Out (out) {}

void ForthInterpreter::InterpretString(const std::string& str) {
    Stack = std::make_unique<std::stack <int>>();
    InterpretCommand(str);
}

void ForthInterpreter::RunInterpretation(bool CinCout) {

    bool someCout;
    std::string str;
    Stack = std::make_unique<std::stack <int>>();

    if (CinCout) {
        Out << "> ";
    }

    while (getline (In, str, '\n')) {
        Out << "< ";
        someCout = InterpretCommand(str);

        if (!someCout) {
            Out << "ok";
        }
        Out << std::endl;
        if (CinCout) {
            Out << "> ";
        }
    }
}

int main(int argc, char** argv) {    
    if (argc == 1) {
        ForthInterpreter interpreter(std::cin, std::cout);
        interpreter.RunInterpretation(true);
    } else if (argc == 2) {
        std::ifstream in(argv[1]);
        ForthInterpreter interpreter(in, std::cout);
        interpreter.RunInterpretation(false);
    } else if (argc == 3) {
        std::ifstream in(argv[1]);
        std::ofstream out(argv[2]);
        ForthInterpreter interpreter(in, out);
        interpreter.RunInterpretation(false);
    } else {
        std::cout << "Undefined work mode" << std::endl;
        return -1;
    }

    return 0;
}