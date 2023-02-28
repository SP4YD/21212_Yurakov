package Push;

import ForthCommands.ForthCommands;

public class Push extends ForthCommands {
    public Push() {};

    @Override
    public boolean Run () {
        GeneralDataForExecutors.stack.push(Integer.valueOf(GeneralDataForExecutors.CommandText));
    
        return false;
    }
}
