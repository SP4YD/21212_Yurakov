package ru.nsu.yurakov.Forth.PrintingLine;

import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;

/**
 * Contains a command that outputs a string
 */
public class PrintingLine extends ForthCommands{
    
    @Override
    public boolean Run() {
        String command = GeneralDataForExecutors.CommandText;
        GeneralDataForExecutors.outputFile.print(command.substring(3, command.length() - 1) + " ");

        return true;
    }
}
