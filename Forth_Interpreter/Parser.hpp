#pragma once

#include <string>
#include <sstream>
#include <vector>

#include "exceptions.hpp"

std::vector <std::string> parser (std::string str);

void ParserIf (std::string& result,
               std::string& tmp, 
               std::istringstream& ist, 
               std::vector <std::string>& splitStr);

void ParserDo (std::string& result,
               std::string& tmp, 
               std::istringstream& ist, 
               std::vector <std::string>& splitStr);