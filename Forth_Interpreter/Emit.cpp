#include "Emit.hpp"

bool Emit::Run () {
    if (Stack->empty()){
        throw Exception_EmptyStack();
    }

    *Output << (char)Stack->top () << " ";
    Stack->pop ();

    return true;
}
