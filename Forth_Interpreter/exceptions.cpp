#include "exceptions.hpp"

Exception_EmptyStack::Exception_EmptyStack() {
    Msg = "There are not enough elements in the stack";
}

Exception_UnknownCommand::Exception_UnknownCommand() {
    Msg = "Unknown command";
}

Exception_DivisionByZero::Exception_DivisionByZero() {
    Msg = "Division by zero";
}

Exception_SyntaxError::Exception_SyntaxError() {
    Msg = "Division by zero";
}

const char* Exception_EmptyStack::what() const throw () 
{
    return Msg.c_str();
}

const char* Exception_UnknownCommand::what() const throw () 
{
    return Msg.c_str();
}

const char* Exception_DivisionByZero::what() const throw () 
{
    return Msg.c_str();
}

const char* Exception_SyntaxError::what() const throw () 
{
    return Msg.c_str();
}
