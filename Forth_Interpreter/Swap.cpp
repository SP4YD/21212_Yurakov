#include "Swap.hpp"

#include <memory>

bool Swap::Run () {
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
    GeneralDataForExecutors.Stack->push (a);
    GeneralDataForExecutors.Stack->push (b);

    return false;
}
