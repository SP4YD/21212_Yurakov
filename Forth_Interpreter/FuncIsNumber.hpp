#pragma once

#include <string>
#include <climits>
#include <stdexcept>

#include "exceptions.hpp"
// Checks whether this string is a number
// Returns:
// true - number
// false - not a number
bool IsNumber(std::string str);