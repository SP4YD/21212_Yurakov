#include "Rot.hpp"

bool Rot::Run () {
    if (Stack->empty()){
        throw Exception_EmptyStack();
    }

    int a = Stack->top();
    Stack->pop ();

    if (Stack->empty()){
        throw Exception_EmptyStack();
    }

    int b = Stack->top();
    Stack->pop ();

    if (Stack->empty()){
        throw Exception_EmptyStack();
    }

    int c = Stack->top();
    Stack->pop ();

    Stack->push (a);
    Stack->push (c);
    Stack->push (b);

    return false;
}
