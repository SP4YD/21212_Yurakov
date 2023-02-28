package LogOperEqually;

import ForthCommands.ForthCommands;
import java.util.EmptyStackException;

public class LogOperEqually extends ForthCommands{

    @Override
    public boolean Run() {
        try {
            int a = GeneralDataForExecutors.stack.peek ();
            GeneralDataForExecutors.stack.pop ();
        
            int b = GeneralDataForExecutors.stack.peek ();
            GeneralDataForExecutors.stack.pop ();

            GeneralDataForExecutors.stack.push ((b == a) ? 1 : 0);
        } catch (EmptyStackException e) {
            System.err.println(e.getMessage());
        }

        return false;
    }
}
