#include "Point.hpp"

#include <memory>
#include <ostream>

bool Point::Run () {
    if (GeneralDataForExecutors.Stack->empty()){
        throw Exception_EmptyStack();
    }

    *GeneralDataForExecutors.Output << GeneralDataForExecutors.Stack->top () << " ";
    GeneralDataForExecutors.Stack->pop ();

    return true;
}
