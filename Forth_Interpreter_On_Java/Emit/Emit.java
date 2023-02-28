package Emit;

import java.util.EmptyStackException;

import ForthCommands.ForthCommands;

public class Emit extends ForthCommands{

    @Override
    public boolean Run() {
        try {
            System.out.print((char)(int)GeneralDataForExecutors.stack.peek() + " ");
            GeneralDataForExecutors.stack.pop ();
        } catch (EmptyStackException e) {
            System.err.println();
        }

        return true;
    }
}
