#pragma once

#include <iostream>

#include "ForthCommands.hpp"
#include "exceptions.hpp"
// Prints the top number from the stack, and removes it
class Point : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Point> Command_point (".");
}