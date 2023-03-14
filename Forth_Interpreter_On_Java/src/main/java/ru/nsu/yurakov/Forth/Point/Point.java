package ru.nsu.yurakov.Forth.Point;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

/**
 * Prints the top number from the stack, and removes it
 */
public class Point extends ForthCommands{

    @Override
    public boolean Run() throws ForthRuntimeException {
        LOGGER.info("Was launched " + this.getClass().getName());
        try {
            GeneralDataForExecutors.outputFile.print(GeneralDataForExecutors.stack.peek() + " ");
            GeneralDataForExecutors.stack.pop();
        } catch (RuntimeException e) {
            throw new ForthRuntimeException("Stack is empty");
        }
    
        return true;
    }

    private static final Logger LOGGER = LogManager.getLogger(Point.class);
}
