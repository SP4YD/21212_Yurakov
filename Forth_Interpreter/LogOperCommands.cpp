#include "LogOperCommands.hpp"

ForthCommands* LogOperCommands::Creation () {
    return new LogOperCommands;
}

bool LogOperCommands::Run () {  ///override
    if (NameCommand == ">") {
        LogOperMore();
    }
    else if (NameCommand == "<") {
        LogOperLess();
    }
    else if (NameCommand == "=") {
        LogOperEqually();
    }
    else {
        throw my_exception (UnknownCommand);
    }

    return false;
}

void LogOperCommands::LogOperMore () {
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

    Stack->push (b > a);
}

void LogOperCommands::LogOperLess () {
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

    Stack->push (b < a);
}

void LogOperCommands::LogOperEqually () {
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

    Stack->push (b == a);
}