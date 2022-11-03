#include "Dup.hpp"

bool Dup::Run () {
    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    Stack->push (Stack->top());

    return false;
}
