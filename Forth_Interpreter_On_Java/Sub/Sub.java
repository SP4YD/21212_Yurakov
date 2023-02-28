package Sub;

import java.util.EmptyStackException;
import ForthCommands.ForthCommands;

public class Sub extends ForthCommands{
    
    @Override 
    public boolean Run() {
        try {
            int a = GeneralDataForExecutors.stack.peek ();
            GeneralDataForExecutors.stack.pop ();

            int b = GeneralDataForExecutors.stack.peek ();
            GeneralDataForExecutors.stack.pop ();

            GeneralDataForExecutors.stack.push(b - a);

        } catch (EmptyStackException e) {
            System.err.print(e.getMessage());
        }

        return false;
    }
}
