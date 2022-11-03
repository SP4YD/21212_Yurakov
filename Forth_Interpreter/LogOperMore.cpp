#include "LogOperMore.hpp"

bool LogOperMore::Run () {
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

    Stack->push (b > a);

    return false;
}
