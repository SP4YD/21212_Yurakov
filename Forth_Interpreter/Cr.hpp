#pragma once

#include <iostream>

#include "ForthCommands.hpp"
#include "exceptions.hpp"
// Moves to the next line
class Cr : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Cr> Command_cr ("cr");
}