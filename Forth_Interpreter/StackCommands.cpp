#include "StackCommands.hpp"

ForthCommands* StackCommands::Creation () {
    return new StackCommands;
}

bool StackCommands::Run () {
    if (NameCommand == "drop") {
        Drop();
    }
    else if (NameCommand == "dup") {
        Dup();
    }
    else if (NameCommand == ".") {
        Point();
        return true;
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
        return true;
    }
    else if (NameCommand == "cr") {
        Cr();
        return true;
    }
    else if (IsNumber(NameCommand)) {
        Push (stoi(NameCommand));
    }
    else {
        throw my_exception (UnknownCommand);
    }

    return false;
}

void StackCommands::Push (const int a) {
    Stack->push (a);
}

void StackCommands::Dup () {
    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    Stack->push (Stack->top());
}

void StackCommands::Drop () {
    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    Stack->pop ();
}

void StackCommands::Point () {
    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    std::cout << "< " << Stack->top () << std::endl;
    Stack->pop ();
}

void StackCommands::Swap () {
    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    int a = Stack->top();
    Stack->pop ();

    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    int b = Stack->top();
    Stack->pop ();
    Stack->push (a);
    Stack->push (b);
}

void StackCommands::Rot () {
    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    int a = Stack->top();
    Stack->pop ();

    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    int b = Stack->top();
    Stack->pop ();

    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    int c = Stack->top();
    Stack->pop ();

    Stack->push (a);
    Stack->push (c);
    Stack->push (b);
}

void StackCommands::Over () {
    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    int a = Stack->top();
    Stack->pop ();

    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    int b = Stack->top();

    Stack->push (a);
    Stack->push (b);
}

void StackCommands::Emit () {
    if (Stack->empty()){
        throw my_exception(EmptyStack);
    }

    std::cout << "< " << (char)Stack->top () << std::endl;
    Stack->pop ();
}

void StackCommands::Cr () {
    std::cout << "< " << std::endl;
}