package Division;

import java.util.EmptyStackException;

import ForthCommands.ForthCommands;

public class Division extends ForthCommands{
    
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
            else {
                GeneralDataForExecutors.stack.push(b / a);
            }
        } catch (EmptyStackException e) {
            System.err.print(e.getMessage());
        }
    
        return false;
    }
}
