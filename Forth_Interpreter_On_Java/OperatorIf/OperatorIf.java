package OperatorIf;

import java.util.EmptyStackException;

import ForthCommands.ForthCommands;

public class OperatorIf extends ForthCommands{
    
    @Override
    public boolean Run() {
        try {
            String command = GeneralDataForExecutors.CommandText;
            command = command.substring(3, command.length() - 7);
            String[] commands = command.split(" ");

            String tmp;
            String beforeElse = "";
            String afterElse = "";
            int balanceIfThen = 1;
            int i = 0;
            
            tmp = commands[i];
            for (; i < commands.length; ++i) {
                tmp = commands[i];
                if ((balanceIfThen == 1) && (tmp.equals("else"))) {
                    break;
                }

                if (tmp.equals("if")) {
                    balanceIfThen++;
                }
                else if (tmp.equals("then")) {
                    balanceIfThen--;
                }
    
                beforeElse += tmp + " ";
            }
            beforeElse = beforeElse.substring(0, beforeElse.length() - 1);

            ++i;
            for (; i < commands.length; ++i) {
                tmp = commands[i];
                afterElse += tmp + " ";
            }

            if (afterElse.length() > 0) {
                afterElse = afterElse.substring(0, afterElse.length() - 1);
            }

            if (GeneralDataForExecutors.stack.peek() > 0) {
                GeneralDataForExecutors.CommandsForSecondProcessing = beforeElse;
            }
            else {
                GeneralDataForExecutors.CommandsForSecondProcessing = afterElse;
            }
        } catch (EmptyStackException e) {
            System.err.print(e.getMessage());
        }

        return false;
    }
}
