package ru.nsu.yurakov.Forth.Drop;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

/**
 * Removes the top number from the stack
 */
public class Drop extends ForthCommands{
    
    @Override
    public boolean Run() throws ForthRuntimeException {
        LOGGER.info("Was launched " + this.getClass().getName());
        try {
            GeneralDataForExecutors.stack.pop();
        } catch (RuntimeException e) {
            throw new ForthRuntimeException("Stack is empty");
        }
    
        return false;
    }

    private static final Logger LOGGER = LogManager.getLogger(Drop.class);
}
