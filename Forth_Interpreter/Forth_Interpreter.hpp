#pragma once

#include <iostream>
#include <stack>
#include <memory>

#include "Parser.hpp"
#include "Factory.hpp"
#include "ForthCommands.hpp"
#include "FuncIsNumber.hpp"

// Executes the passed string
bool ForthInterpreter(std::string str);

int main();