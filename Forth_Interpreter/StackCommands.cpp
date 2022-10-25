#pragma once
#include <iostream>

#include "ForthCommands.cpp"
#include "exceptions.cpp"

class StackCommands: private ForthCommands {
public:
    static ForthCommands* Creation () {
        return new StackCommands;
    }
private:
    void Run () {  ///override
        if (NameCommand == "drop") {
            Drop();
        }
        else if (NameCommand == "dup") {
            Dup();
        }
        else if (NameCommand == "point") {
            Point();
        }
        else if (NameCommand == "swap") {
            Swap();
        }
        else if (NameCommand == "rot") {
            Rot();
        }
        else if (NameCommand == "over") {
            Over();
        }
        else if (NameCommand == "emit") {
            Emit();
        }
        else if (NameCommand == "cr") {
            Cr();
        }
        else if (IsNumber(NameCommand)) { /// Реализовать функцию которая проверяет число ли это

        }
    }

    int Push (const int a) {
        Stack.push (a);

        return 0;
    }

    int Dup () {
        if (Stack.empty()){
            throw my_exception(EmptyStack);
        }
        Stack.push (Stack.top());
        return 0;
    }

    int Drop () {
        if (Stack.empty()){
            throw my_exception(EmptyStack);
        }
        Stack.pop ();
        return 0;
    }

    int Point () {
        if (Stack.empty()){
            throw my_exception(EmptyStack);
        }
        std::cout << "< " << Stack.top () << std::endl;
        Stack.pop ();
        return 0;
    }

    int Swap () {
        if (Stack.empty()){
            throw my_exception(EmptyStack);
        }

        int a = Stack.top();
        Stack.pop ();

        if (Stack.empty()){
            throw my_exception(EmptyStack);
        }

        int b = Stack.top();
        Stack.pop ();
        Stack.push (a);
        Stack.push (b);
        return 0;
    }

    int Rot () {
        if (Stack.empty()){
            throw my_exception(EmptyStack);
        }

        int a = Stack.top();
        Stack.pop ();

        if (Stack.empty()){
            throw my_exception(EmptyStack);
        }

        int b = Stack.top();
        Stack.pop ();

        if (Stack.empty()){
            throw my_exception(EmptyStack);
        }

        int c = Stack.top();
        Stack.pop ();

        Stack.push (a);
        Stack.push (c);
        Stack.push (b);
        return 0;
    }

    int Over () {
        if (Stack.empty()){
            throw my_exception(EmptyStack);
        }

        int a = Stack.top();
        Stack.pop ();

        if (Stack.empty()){
            throw my_exception(EmptyStack);
        }

        int b = Stack.top();

        Stack.push (a);
        Stack.push (b);
        return 0;
    }

    int Emit () {
        if (Stack.empty()){
            throw my_exception(EmptyStack);
        }

        std::cout << "< " << (char)Stack.top () << std::endl;
        Stack.pop ();

        return 0;
    }

    int Cr () {
        std::cout << std::endl;
    }
};