#pragma once

#include "ForthCommands.hpp"

#include <memory>

class ForthInterpreter {
public:
    ForthInterpreter() = delete;

    ForthInterpreter(std::istream& in, std::ostream& out);

    ForthInterpreter(const ForthInterpreter&) = delete;

    ForthInterpreter(ForthInterpreter&&) = delete;

    ~ForthInterpreter() = default;
    // Interpretation of a certain string
    void InterpretString(const std::string str);
    // Running the program from an unlimited number of lines
    // Accepts bool as input
    // true: istream = cin, ostream = cout
    // else false
    void RunInterpretation(const bool CinCout);
private:
    bool InterpretCommand(const std::string str);

    std::istream& In;
    std::ostream& Out;

    std::unique_ptr<std::stack <int>> Stack;
};

int main(int argc, char** argv);