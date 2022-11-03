#pragma once

#include "ForthCommands.hpp"
#include "exceptions.hpp"
// Copies the second number and puts a copy over the top one
class Over : public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Over> Command_over ("over");
}