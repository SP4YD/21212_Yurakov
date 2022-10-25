#pragma once
#include "ForthCommands.cpp"
#include "exceptions.cpp"


class LogOperCommands: private ForthCommands { 
private:
    static ForthCommands* Creation () {
        return new LogOperCommands;
    }

    int LogOperMore () {
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

        Stack.push (b > a);

        return 0;
    }

    int LogOperLess () {
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

        Stack.push (b < a);

        return 0;
    }

    int LogOperEqually () {
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

        Stack.push (b == a);

        return 0;
    }
};