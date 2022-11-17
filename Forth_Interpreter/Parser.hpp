#pragma once

#include <vector>

// Splits a string into commands
std::vector <std::string> Parser (const std::string str);
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