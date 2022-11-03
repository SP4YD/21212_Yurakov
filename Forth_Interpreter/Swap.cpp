#include "Swap.hpp"

bool Swap::Run () {
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
    Stack->push (a);
    Stack->push (b);

    return false;
}
