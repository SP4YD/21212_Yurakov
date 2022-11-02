#pragma once

#include <string>

enum TypeErrors {
    EmptyStack,
    UnknownCommand
};

class my_exception : public std::exception {
public:
    // Returns an error depending on the type of error
    my_exception(const TypeErrors err);
    // Returns an error with the text that was passed
    my_exception(const std::string msg);
    
   virtual const char* what() const throw ();
private:
   std::string Msg;
};