#include "Emit.hpp"
#include "exceptions.hpp"

#include <ostream>

bool Emit::Run () {
    if (GeneralDataForExecutors.Stack->empty()){
        throw Exception_EmptyStack();
    }

    *GeneralDataForExecutors.Output << (char)GeneralDataForExecutors.Stack->top () << " ";
    GeneralDataForExecutors.Stack->pop ();

    return true;
}
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Emit> Command_emit ("emit");
}