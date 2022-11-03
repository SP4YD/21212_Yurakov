#include "Drop.hpp"

bool Drop::Run () {
    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    Stack->pop ();

    return false;
}
