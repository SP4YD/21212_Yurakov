#include "Point.hpp"

bool Point::Run () {
    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    std::cout << Stack->top () << " ";
    Stack->pop ();

    return true;
}
