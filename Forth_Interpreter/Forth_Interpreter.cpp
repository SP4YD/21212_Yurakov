#include "Forth_Interpreter.hpp"

bool ForthInterpreter::InterpretCommand(std::string str) {
    std::shared_ptr<ForthCommands> executableCommand;
    std::string commandText;
    std::shared_ptr<std::string> commandsForSecondProcessing = std::make_shared<std::string>();
    bool someCout = false;

    std::vector <std::string> commands = Parser (str);


    for (unsigned int i = 0; i < commands.size(); ++i) {
        if (IsNumber(commands[i])) {
            commandText = commands[i];
            commands[i] = "push";
        } else if (commands[i].length() > 1 && commands[i][0] == '.' && commands[i][1] == '"') {
            commandText = commands[i];
            commands[i] = ".\"";
        } else if (commands[i].length() > 1 && commands[i][0] == 'i' && commands[i][1] == 'f') {
            commandText = commands[i];
            commands[i] = "if";
        } else if (commands[i].length() > 1 && commands[i][0] == 'd' && commands[i][1] == 'o') {
            commandText = commands[i];
            commands[i] = "do";
        }

        commandsForSecondProcessing->clear();
        executableCommand = (std::shared_ptr<ForthCommands>) Factory::get().CreateExecutor (commands[i]);
        executableCommand->AddStack (Stack);
        executableCommand->AddInputOutput (&In, &Out);
        executableCommand->AddCommandsForSecondProcessing (commandsForSecondProcessing);
        executableCommand->AddCommandText (commandText);
        someCout += executableCommand->Run();

        if (commandsForSecondProcessing != nullptr && commandsForSecondProcessing->length() > 0) {
            someCout += InterpretCommand (*commandsForSecondProcessing);
        }
    }

    return someCout;
}

ForthInterpreter::ForthInterpreter(std::istream& in, std::ostream& out) : In (in), Out (out) {};

void ForthInterpreter::InterpretString(std::string str) {
    InterpretCommand(str);
}

void ForthInterpreter::RunInterpretation(bool CinCout) {

    bool someCout;
    std::string str;
    Stack = std::make_shared<std::stack <int>>();

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