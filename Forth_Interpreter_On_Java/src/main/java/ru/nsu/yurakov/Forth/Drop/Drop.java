package ru.nsu.yurakov.Forth.Drop;

import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

import java.util.EmptyStackException;

/**
 * Removes the top number from the stack
 */
public class Drop extends ForthCommands{
    
    @Override
    public boolean Run() throws ForthRuntimeException {
        try {
            GeneralDataForExecutors.stack.pop();
        } catch (RuntimeException e) {
            throw new ForthRuntimeException("Stack is empty");
        }
    
        return false;
    }
}
