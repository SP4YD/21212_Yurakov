#include "LogOperMore.hpp"

bool LogOperMore::Run () {
    if (Stack->empty ()) {
        throw Exception_EmptyStack();
    }

    int a = Stack->top ();
    Stack->pop ();

    if (Stack->empty ()) {
        throw Exception_EmptyStack();
    }

    int b = Stack->top ();
    Stack->pop ();

    Stack->push (b > a);

    return false;
}
