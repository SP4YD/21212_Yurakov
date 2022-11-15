#include "Mod.hpp"

bool Mod::Run () {
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

    if (a == 0) {
        throw Exception_DivisionByZero();
    }

    Stack->push (b % a);

    return false;
}
