package ru.nsu.yurakov.Forth.Push;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;

/**
 * Push number on stack<br>
 * Pushes the result on the stack
 */
public class Push extends ForthCommands {

    @Override
    public boolean Run () {
        LOGGER.info("Was launched " + this.getClass().getName());
        GeneralDataForExecutors.stack.push(Integer.valueOf(GeneralDataForExecutors.CommandText));
    
        return false;
    }

    private static final Logger LOGGER = LogManager.getLogger(Push.class);
}
