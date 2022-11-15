#include "Push.hpp"

bool Push::Run () {
    Stack->push (stoi(CommandText));

    return false;
}
