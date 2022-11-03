#pragma once

#include <iostream>
#include <stack>

#include "Parser.hpp"
#include "Factory.hpp"
#include "ForthCommands.hpp"
#include "FuncIsNumber.hpp"

int main();
// Performs secondary processing of transmitted commands
bool SecondaryProcessing (std::string* comm, std::stack <int>* generalStack);