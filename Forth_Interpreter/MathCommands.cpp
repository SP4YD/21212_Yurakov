#include "MathCommands.hpp"

ForthCommands* MathCommands::Creation () {
    return new MathCommands;
}

bool MathCommands::Run () {
    if (NameCommand == "+") {
        Plus();
    }
    else if (NameCommand == "*") {
        Multip();
    }
    else if (NameCommand == "-") {
        Sub();
    }
    else if (NameCommand == "/") {
        Division();
    }
    else if (NameCommand == "mod") {
        Mod();
    }
    else {
        throw my_exception (UnknownCommand);
    }

    return false;
}

void MathCommands::Plus () {
    if (Stack->empty ()) {
        throw my_exception(EmptyStack);
    }

    int a = Stack->top ();
    Stack->pop ();

    if (Stack->empty ()) {
        throw my_exception(EmptyStack);
    }

    int b = Stack->top ();
    Stack->pop ();

    Stack->push(b + a);
}

void MathCommands::Multip () {
    if (Stack->empty ()) {
        throw my_exception(EmptyStack);
    }

    int a = Stack->top ();
    Stack->pop ();

    if (Stack->empty ()) {
        throw my_exception(EmptyStack);
    }

    int b = Stack->top ();
    Stack->pop ();

    Stack->push(b * a);
}

void MathCommands::Sub () {
    if (Stack->empty ()) {
        throw my_exception(EmptyStack);
    }

    int a = Stack->top ();
    Stack->pop ();

    if (Stack->empty ()) {
        throw my_exception(EmptyStack);
    }

    int b = Stack->top ();
    Stack->pop ();

    Stack->push(b - a);
}

void MathCommands::Division () {
    if (Stack->empty ()) {
        throw my_exception(EmptyStack);
    }

    int a = Stack->top ();
    Stack->pop ();

    if (Stack->empty ()) {
        throw my_exception(EmptyStack);
    }

    int b = Stack->top ();
    Stack->pop ();

    if (a == 0) {
        throw my_exception ("Division by zero");
    }

    Stack->push(b / a);
}

void MathCommands::Mod () {
    if (Stack->empty ()) {
        throw my_exception(EmptyStack);
    }

    int a = Stack->top ();
    Stack->pop ();

    if (Stack->empty ()) {
        throw my_exception(EmptyStack);
    }

    int b = Stack->top ();
    Stack->pop ();

    if (a == 0) {
        throw my_exception ("Division by zero");
    }

    Stack->push (b % a);
}