#include "Plus.hpp"

#include <memory>

bool Plus::Run () {
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

    GeneralDataForExecutors.Stack->push(b + a);

    return false;
}
