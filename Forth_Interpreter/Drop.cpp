#include "Drop.hpp"

bool Drop::Run () {
    if (Stack->empty()){
        throw Exception_EmptyStack();
    }

    Stack->pop ();

    return false;
}
