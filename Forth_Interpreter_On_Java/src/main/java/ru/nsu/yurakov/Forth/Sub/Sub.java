package ru.nsu.yurakov.Forth.Sub;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

/**
 * Subtracts the first number from the stack from the second
 * Pushes the result on the stack
 */
public class Sub extends ForthCommands{
    
    @Override 
    public boolean Run() throws ForthRuntimeException {
        LOGGER.info("Was launched " + this.getClass().getName());
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
            GeneralDataForExecutors.stack.pop();
        } catch (RuntimeException ex) {
            GeneralDataForExecutors.stack.push(a);
            throw new ForthRuntimeException("Stack is empty");
        }

        GeneralDataForExecutors.stack.push(b - a);

        return false;
    }

    private static final Logger LOGGER = LogManager.getLogger(Sub.class);
}
