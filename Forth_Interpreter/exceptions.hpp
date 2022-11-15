#pragma once

#include <string>
// An exception is when there are not enough numbers in the stack
class Exception_EmptyStack : public std::exception {
public:
    Exception_EmptyStack();

   virtual const char* what() const throw ();
private:
   std::string Msg;
};
// The exception is when a team came that is not in the database
class Exception_UnknownCommand : public std::exception {
public:
    Exception_UnknownCommand();

   virtual const char* what() const throw ();
private:
   std::string Msg;
};
// The exception is when an attempt was made to divide by zero
class Exception_DivisionByZero : public std::exception {
public:
    Exception_DivisionByZero();

   virtual const char* what() const throw ();
private:
   std::string Msg;
};
// Exception when a syntax error was made
class Exception_SyntaxError : public std::exception {
public:
    Exception_SyntaxError();

   virtual const char* what() const throw ();
private:
   std::string Msg;
};