#pragma once

#include "Parser.hpp"
#include "Factory.hpp"

int main();
// Performs secondary processing of transmitted commands
bool SecondaryProcessing (std::string* comm, std::stack <int>* generalStack, Factory& factory);