package Point;

import java.util.EmptyStackException;
import ForthCommands.ForthCommands;

public class Point extends ForthCommands{

    @Override
    public boolean Run() {
        try {
            System.out.print(GeneralDataForExecutors.stack.peek() + " ");
            GeneralDataForExecutors.stack.pop();
        } catch (EmptyStackException e) {
            System.err.print(e.getMessage());
        }
    
        return true;
    }
    
}
