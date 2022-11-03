#include "Emit.hpp"

bool Emit::Run () {
    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    std::cout << (char)Stack->top () << " ";
    Stack->pop ();

    return true;
}
