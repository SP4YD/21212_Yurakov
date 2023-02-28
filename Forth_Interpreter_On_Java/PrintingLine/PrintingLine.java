package PrintingLine;

import ForthCommands.ForthCommands;

public class PrintingLine extends ForthCommands{
    
    @Override
    public boolean Run() {
        String command = GeneralDataForExecutors.CommandText;
        System.out.print(command.substring(3, command.length() - 1));

        return true;
    }
}
