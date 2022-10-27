#pragma once

#include <string>

enum TypeErrors {
    EmptyStack,
    UnknownCommand
};

class my_exception : public std::exception {
public:
    my_exception(const TypeErrors err);

    my_exception(const std::string msg);

   virtual const char* what() const throw ();
private:
   std::string Msg;
};