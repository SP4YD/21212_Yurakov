package Dup;

import ForthCommands.ForthCommands;
import java.util.EmptyStackException;

public class Dup extends ForthCommands{
    
    @Override
    public boolean Run() {
        try {
            GeneralDataForExecutors.stack.push (GeneralDataForExecutors.stack.peek());
        } catch (EmptyStackException e) {
            System.err.println(e.getMessage());
        }

        return false;
    }
}
