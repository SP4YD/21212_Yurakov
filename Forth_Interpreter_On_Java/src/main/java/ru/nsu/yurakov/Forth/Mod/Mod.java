package ru.nsu.yurakov.Forth.Mod;

import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

/**
 * Calculates the remainder of dividing the second number on the stack by the first<br>
 * Pushes the result on the stack
 */
public class Mod extends ForthCommands{

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

        GeneralDataForExecutors.stack.push (b % a);

        return false;
    }
    
}
