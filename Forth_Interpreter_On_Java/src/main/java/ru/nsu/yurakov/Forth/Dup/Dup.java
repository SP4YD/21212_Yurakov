package ru.nsu.yurakov.Forth.Dup;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

import java.util.EmptyStackException;

/**
 * Copies the top of the stack and puts it on the top of the stack
 */
public class Dup extends ForthCommands{
    
    @Override
    public boolean Run() throws ForthRuntimeException {
        LOGGER.info("Was launched " + this.getClass().getName());
        try {
            GeneralDataForExecutors.stack.push (GeneralDataForExecutors.stack.peek());
        } catch (RuntimeException e) {
            throw new ForthRuntimeException("Stack is empty");
        }

        return false;
    }

    private static final Logger LOGGER = LogManager.getLogger(Dup.class);
}
