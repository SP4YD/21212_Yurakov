#include "LogOperMore.hpp"

#include <memory>

bool LogOperMore::Run () {
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

    GeneralDataForExecutors.Stack->push (b > a);

    return false;
}
