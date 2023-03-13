package ru.nsu.yurakov.Forth.Division;

import java.util.EmptyStackException;

import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

/**
 * Division the first number from the stack from the second<br>
 * Pushes the result on the stack
 */
public class Division extends ForthCommands{
    
    @Override
    public boolean Run() throws ForthRuntimeException {
        int a = 0;
        int b = 0;
        try {
            a = GeneralDataForExecutors.stack.peek();
            GeneralDataForExecutors.stack.pop();
        } catch (RuntimeException ex) {
            throw new ForthRuntimeException("Stack is empty");
        }
        try {
            b = GeneralDataForExecutors.stack.peek ();
            GeneralDataForExecutors.stack.pop ();
        } catch (RuntimeException ex) {
            GeneralDataForExecutors.stack.push(a);
            throw new ForthRuntimeException("Stack is empty");
        }

        if (a == 0) {
            throw new ForthRuntimeException("Division by zero");
        }
        else {
            GeneralDataForExecutors.stack.push(b / a);
        }
    
        return false;
    }
}
