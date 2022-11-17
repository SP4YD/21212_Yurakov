#include "Drop.hpp"
#include "exceptions.hpp"

#include <memory>

bool Drop::Run () {
    if (GeneralDataForExecutors.Stack->empty()){
        throw Exception_EmptyStack();
    }

    GeneralDataForExecutors.Stack->pop ();

    return false;
}
