#include "Rot.hpp"

bool Rot::Run () {
    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    int a = Stack->top();
    Stack->pop ();

    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    int b = Stack->top();
    Stack->pop ();

    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    int c = Stack->top();
    Stack->pop ();

    Stack->push (a);
    Stack->push (c);
    Stack->push (b);

    return false;
}
