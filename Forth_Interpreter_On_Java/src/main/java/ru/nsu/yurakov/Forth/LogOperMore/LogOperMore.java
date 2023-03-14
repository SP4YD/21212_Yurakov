package ru.nsu.yurakov.Forth.LogOperMore;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

/**
 * Calculates whether the second number on the stack is greater than the first<br>
 * Pushes the result on the stack<br>
 * 0 - second &#60; first<br>
 * 1 - second &#62; first
 */
public class LogOperMore extends ForthCommands{
    
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
            GeneralDataForExecutors.stack.pop ();
        } catch (RuntimeException ex) {
            GeneralDataForExecutors.stack.push(a);
            throw new ForthRuntimeException("Stack is empty");
        }

        GeneralDataForExecutors.stack.push ((b > a) ? 1 : 0);
        return false;
    }

    private static final Logger LOGGER = LogManager.getLogger(LogOperMore.class);
}
