#pragma once

#include "ForthCommands.hpp"
#include "exceptions.hpp"
// Cyclically shifts the top three numbers
class Rot : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Rot> Command_rot ("rot");
}