#include "Dup.hpp"

bool Dup::Run () {
    if (Stack->empty()){
        throw Exception_EmptyStack();
    }

    Stack->push (Stack->top());

    return false;
}
