package ru.nsu.yurakov.Forth.Cr;

import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;

/**
 * Moves to the next line
 */
public class Cr extends ForthCommands{
    
    @Override
    public boolean Run() {
        GeneralDataForExecutors.outputFile.println();
        GeneralDataForExecutors.outputFile.print( "< ");
        
        return true;
    }
}
