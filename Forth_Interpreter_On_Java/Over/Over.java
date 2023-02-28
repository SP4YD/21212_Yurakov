package Over;

import java.util.EmptyStackException;

import ForthCommands.ForthCommands;

public class Over extends ForthCommands{

    @Override
    public boolean Run() {
        try {
            int a = GeneralDataForExecutors.stack.peek();
            GeneralDataForExecutors.stack.pop ();
        
            int b = GeneralDataForExecutors.stack.peek();
        
            GeneralDataForExecutors.stack.push (a);
            GeneralDataForExecutors.stack.push (b);
        } catch (EmptyStackException e) {
            System.err.println(e.getMessage());
        }

        return false;
    }
    
}
