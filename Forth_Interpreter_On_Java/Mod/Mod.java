package Mod;

import java.util.EmptyStackException;

import ForthCommands.ForthCommands;

public class Mod extends ForthCommands{

    @Override
    public boolean Run() {
        try {
            int a = GeneralDataForExecutors.stack.peek ();
            GeneralDataForExecutors.stack.pop ();

            int b = GeneralDataForExecutors.stack.peek ();
            GeneralDataForExecutors.stack.pop ();

            if (a == 0) {
                System.out.println("Division by zero");
            }

            GeneralDataForExecutors.stack.push (b % a);
        } catch (EmptyStackException e) {
            System.err.println(e.getMessage());
        }

        return false;
    }
    
}
