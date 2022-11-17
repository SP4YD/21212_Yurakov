#include "Dup.hpp"
#include "exceptions.hpp"

#include <memory>

bool Dup::Run () {
    if (GeneralDataForExecutors.Stack->empty()){
        throw Exception_EmptyStack();
    }

    GeneralDataForExecutors.Stack->push (GeneralDataForExecutors.Stack->top());

    return false;
}
