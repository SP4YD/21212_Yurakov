package Drop;

import ForthCommands.ForthCommands;
import java.util.EmptyStackException;

public class Drop extends ForthCommands{
    
    @Override
    public boolean Run() {
        try {
            GeneralDataForExecutors.stack.pop();
        } catch (EmptyStackException e) {
            System.err.println(e.getMessage());
        }
    
        return false;
    }
}
