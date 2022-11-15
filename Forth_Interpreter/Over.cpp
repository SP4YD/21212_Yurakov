#include "Over.hpp"

bool Over::Run () {
    if (Stack->empty()){
        throw Exception_EmptyStack();
    }

    int a = Stack->top();
    Stack->pop ();

    if (Stack->empty()){
        throw Exception_EmptyStack();
    }

    int b = Stack->top();

    Stack->push (a);
    Stack->push (b);
    
    return false;
}
