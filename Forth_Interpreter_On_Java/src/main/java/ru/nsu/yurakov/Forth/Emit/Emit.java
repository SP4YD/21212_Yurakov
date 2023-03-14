package ru.nsu.yurakov.Forth.Emit;

import java.util.EmptyStackException;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

/**
 * Prints the top number on the stack as an ASCII code and removes it from the stack
 */
public class Emit extends ForthCommands{

    @Override
    public boolean Run() throws ForthRuntimeException {
        LOGGER.info("Was launched " + this.getClass().getName());
        try {
            GeneralDataForExecutors.outputFile.print((char)(int)GeneralDataForExecutors.stack.peek() + " ");
            GeneralDataForExecutors.stack.pop ();
        } catch (RuntimeException e) {
            throw new ForthRuntimeException("Stack is empty");
        }

        return true;
    }

    private static final Logger LOGGER = LogManager.getLogger(Emit.class);
}
