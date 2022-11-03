#include "Division.hpp"

bool Division::Run () {
    if (Stack->empty ()) {
        throw my_exception(EmptyStack);
    }

    int a = Stack->top ();
    Stack->pop ();

    if (Stack->empty ()) {
        throw my_exception(EmptyStack);
    }

    int b = Stack->top ();
    Stack->pop ();

    if (a == 0) {
        throw my_exception ("Division by zero");
    }

    Stack->push(b / a);

    return false;
}
