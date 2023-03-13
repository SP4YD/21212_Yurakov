package ru.nsu.yurakov.Forth.Push;

import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;

/**
 * Push number on stack<br>
 * Pushes the result on the stack
 */
public class Push extends ForthCommands {
    public Push() {};

    @Override
    public boolean Run () {
        GeneralDataForExecutors.stack.push(Integer.valueOf(GeneralDataForExecutors.CommandText));
    
        return false;
    }
}
