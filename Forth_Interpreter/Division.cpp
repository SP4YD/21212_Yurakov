#include "Division.hpp"
#include "exceptions.hpp"

#include <memory>

bool Division::Run () {
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

    if (a == 0) {
        throw Exception_DivisionByZero();
    }

    GeneralDataForExecutors.Stack->push(b / a);

    return false;
}
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Division> Command_division ("/");
}