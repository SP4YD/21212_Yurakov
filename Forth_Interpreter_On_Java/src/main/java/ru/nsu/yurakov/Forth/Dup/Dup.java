package ru.nsu.yurakov.Forth.Dup;

import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

import java.util.EmptyStackException;

/**
 * Copies the top of the stack and puts it on the top of the stack
 */
public class Dup extends ForthCommands{
    
    @Override
    public boolean Run() throws ForthRuntimeException {
        try {
            GeneralDataForExecutors.stack.push (GeneralDataForExecutors.stack.peek());
        } catch (RuntimeException e) {
            throw new ForthRuntimeException("Stack is empty");
        }

        return false;
    }
}
