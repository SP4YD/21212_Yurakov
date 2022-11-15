#pragma once

#include <fstream>
#include <iostream>
#include <stack>
#include <memory>

#include "Parser.hpp"
#include "Factory.hpp"
#include "ForthCommands.hpp"
#include "FuncIsNumber.hpp"

class ForthInterpreter {
public:
    ForthInterpreter() = delete;

    ForthInterpreter(std::istream& in, std::ostream& out);

    ForthInterpreter(const ForthInterpreter&) = delete;

    ForthInterpreter(ForthInterpreter&&) = delete;

    ~ForthInterpreter() = default;
    // Interpretation of a certain string
    void InterpretString(std::string str);
    // Running the program from an unlimited number of lines
    // Accepts bool as input
    // true: istream = cin, ostream = cout
    // else false
    void RunInterpretation(bool CinCout);
private:
    bool InterpretCommand(std::string str);

    std::istream& In;
    std::ostream& Out;

    std::shared_ptr<std::stack <int>> Stack;
};

int main(int argc, char** argv);