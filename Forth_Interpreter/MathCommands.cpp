#pragma once
#include "ForthCommands.cpp"
#include "exceptions.cpp"

class MathCommands: private ForthCommands { 
    static ForthCommands* Creation () {
        return new MathCommands;
    }

    int Plus () {
        if (Stack.empty ()) {
            throw my_exception(EmptyStack);
        }

        int a = Stack.top ();
        Stack.pop ();

        if (Stack.empty ()) {
            throw my_exception(EmptyStack);
        }

        int b = Stack.top ();
        Stack.pop ();

        Stack.push(b + a);

        return 0;
    }

    int Multip () {
        if (Stack.empty ()) {
            throw my_exception(EmptyStack);
        }

        int a = Stack.top ();
        Stack.pop ();

        if (Stack.empty ()) {
            throw my_exception(EmptyStack);
        }

        int b = Stack.top ();
        Stack.pop ();

        Stack.push(b * a);

        return 0;
    }

    int Sub () {
        if (Stack.empty ()) {
            throw my_exception(EmptyStack);
        }

        int a = Stack.top ();
        Stack.pop ();

        if (Stack.empty ()) {
            throw my_exception(EmptyStack);
        }

        int b = Stack.top ();
        Stack.pop ();

        Stack.push(b - a);
        
        return 0;
    }

    int Division () {
        if (Stack.empty ()) {
            throw my_exception(EmptyStack);
        }

        int a = Stack.top ();
        Stack.pop ();

        if (Stack.empty ()) {
            throw my_exception(EmptyStack);
        }

        int b = Stack.top ();
        Stack.pop ();

        Stack.push(b / a);

        return 0;
    }

    int Mod () {
        if (Stack.empty ()) {
            throw my_exception(EmptyStack);
        }

        int a = Stack.top ();
        Stack.pop ();

        if (Stack.empty ()) {
            throw my_exception(EmptyStack);
        }

        int b = Stack.top ();
        Stack.pop ();

        Stack.push (b % a);

        return 0;
    }
};