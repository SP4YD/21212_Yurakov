package ru.nsu.yurakov.Forth.Cr;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

/**
 * Moves to the next line
 */
public class Cr extends ForthCommands{
    
    @Override
    public boolean Run() {
        LOGGER.info("Was launched " + this.getClass().getName());
        GeneralDataForExecutors.outputFile.println();
        GeneralDataForExecutors.outputFile.print( "< ");
        
        return true;
    }

    private static final Logger LOGGER = LogManager.getLogger(Cr.class);
}
