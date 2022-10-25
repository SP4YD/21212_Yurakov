#pragma once
#include <string>

enum TypeErrors {
    EmptyStack = 0    
};

class my_exception : public std::exception {
public:
    my_exception(const TypeErrors err) {
        if (err == EmptyStack) {
            Msg = "There are not enough elements in the stack";
        }
    }

    my_exception(const std::string msg) {
        Msg = msg;
    }

   virtual const char* what() const throw () 
   {
        return Msg.c_str();
   }
private:
   std::string Msg;
};