#include "exceptions.hpp"

my_exception::my_exception(const TypeErrors err) {
    if (err == EmptyStack) {
        Msg = "There are not enough elements in the stack";
    }
    else if (err == UnknownCommand) {
        Msg = "Unknown command";
    }
}

my_exception::my_exception(const std::string msg) {
    Msg = msg;
}

const char* my_exception::what() const throw () 
{
    return Msg.c_str();
}
