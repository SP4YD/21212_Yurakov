#include "Sub.hpp"

#include <memory>

bool Sub::Run () {
    if (GeneralDataForExecutors.Stack->empty ()) {
        throw Exception_EmptyStack();
    }

    int a = GeneralDataForExecutors.Stack->top ();
    GeneralDataForExecutors.Stack->pop ();

    if (GeneralDataForExecutors.Stack->empty ()) {
        throw Exception_EmptyStack();
    }

    int b = GeneralDataForExecutors.Stack->top ();
    GeneralDataForExecutors.Stack->pop ();

    GeneralDataForExecutors.Stack->push(b - a);

    return false;
}
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Sub> Command_sub ("-");
}