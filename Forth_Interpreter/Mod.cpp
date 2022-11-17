#include "Mod.hpp"

#include <memory>

bool Mod::Run () {
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

    GeneralDataForExecutors.Stack->push (b % a);

    return false;
}
