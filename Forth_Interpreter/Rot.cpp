#include "Rot.hpp"

#include <memory>

bool Rot::Run () {
    if (GeneralDataForExecutors.Stack->empty()){
        throw Exception_EmptyStack();
    }

    int a = GeneralDataForExecutors.Stack->top();
    GeneralDataForExecutors.Stack->pop ();

    if (GeneralDataForExecutors.Stack->empty()){
        throw Exception_EmptyStack();
    }

    int b = GeneralDataForExecutors.Stack->top();
    GeneralDataForExecutors.Stack->pop ();

    if (GeneralDataForExecutors.Stack->empty()){
        throw Exception_EmptyStack();
    }

    int c = GeneralDataForExecutors.Stack->top();
    GeneralDataForExecutors.Stack->pop ();

    GeneralDataForExecutors.Stack->push (a);
    GeneralDataForExecutors.Stack->push (c);
    GeneralDataForExecutors.Stack->push (b);

    return false;
}
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Rot> Command_rot ("rot");
}