#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Moves to the next line
class Cr : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Cr> Command_cr ("cr");
}