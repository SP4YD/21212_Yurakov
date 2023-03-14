package ru.nsu.yurakov.Forth.PrintingLine;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;

/**
 * Contains a command that outputs a string
 */
public class PrintingLine extends ForthCommands{
    
    @Override
    public boolean Run() {
        LOGGER.info("Was launched " + this.getClass().getName() + " <" + GeneralDataForExecutors.CommandText + ">");
        String command = GeneralDataForExecutors.CommandText;
        GeneralDataForExecutors.outputFile.print(command.substring(3, command.length() - 1) + " ");

        return true;
    }

    private static final Logger LOGGER = LogManager.getLogger(PrintingLine.class);
}
