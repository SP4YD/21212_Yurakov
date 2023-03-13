package ru.nsu.yurakov.Forth.Over;

import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

/**
 * Copies the second number and puts a copy over the top one
 */
public class Over extends ForthCommands{

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
        } catch (RuntimeException ex) {
            GeneralDataForExecutors.stack.push(a);
            throw new ForthRuntimeException("Stack is empty");
        }

        GeneralDataForExecutors.stack.push(a);
        GeneralDataForExecutors.stack.push(b);

        return false;
    }
    
}
