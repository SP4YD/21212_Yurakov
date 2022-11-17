#pragma once

#include "FactoryRegistrationCommands.hpp"
#include "ForthCommands.hpp"
// Contains a command that outputs a string
class PrintingLine: public ForthCommands {
public:
    // Executing the invoked command
    bool Run () override;
};

namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<PrintingLine> Command_printLine (".\"");
}