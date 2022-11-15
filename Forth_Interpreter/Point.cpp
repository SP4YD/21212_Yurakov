#include "Point.hpp"

bool Point::Run () {
    if (Stack->empty()){
        throw Exception_EmptyStack();
    }

    *Output << Stack->top () << " ";
    Stack->pop ();

    return true;
}
