#include "Push.hpp"

bool Push::Run () {
    Stack->push (stoi(NameCommand));

    return false;
}
