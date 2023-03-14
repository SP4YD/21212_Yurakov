package ru.nsu.yurakov.Forth.OperatorIf;

import java.util.EmptyStackException;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

/**
 * if THEN_BRANCH then ;<br>
 * If there is > 0 on the stack, THEN_BRANCH goes to secondary processing, else nothing<br>
 * <br>
 * if THEN_BRANCH else ELSE_BRANCH then ;<br>
 * If there is > 0 on the stack, THEN_BRANCH goes to secondary processing, else ELSE_BRANCH
 */
public class OperatorIf extends ForthCommands{
    
    @Override
    public boolean Run() throws ForthRuntimeException {
        LOGGER.info("Was launched " + this.getClass().getName() + " <" + GeneralDataForExecutors.CommandText + ">");
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
            throw new ForthRuntimeException("Stack is empty");
        }

        return false;
    }

    private static final Logger LOGGER = LogManager.getLogger(OperatorIf.class);
}
