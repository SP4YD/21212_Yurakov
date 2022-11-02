#pragma once

#include <string>
#include <sstream>
#include <vector>

#include "exceptions.hpp"
// Splits a string into commands
std::vector <std::string> Parser (std::string str);
// Splits If in the necessary way
void ParserIf (std::string& result,
               std::string& tmp, 
               std::istringstream& ist, 
               std::vector <std::string>& splitStr);
// Splits DoLoop in the necessary way
void ParserDo (std::string& result,
               std::string& tmp, 
               std::istringstream& ist, 
               std::vector <std::string>& splitStr);