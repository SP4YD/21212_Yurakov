package ru.nsu.yurakov.Forth.OperatorDoLoop;

import java.util.EmptyStackException;
import java.util.ArrayList;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

/**
 * Unwinds the loop and substitutes the desired values instead of i.<br>
 * And sends the result for secondary processing
 */
public class OperatorDoLoop extends ForthCommands{

    @Override
    public boolean Run() throws ForthRuntimeException {
        LOGGER.info("Was launched " + this.getClass().getName() + " <" + GeneralDataForExecutors.CommandText + ">");
        try {
            String command = GeneralDataForExecutors.CommandText;
            command = command.substring(3, command.length() - 7);
            String[] commands = command.split(" ");
            String pattern = command;

            int i = GeneralDataForExecutors.stack.peek();
            GeneralDataForExecutors.stack.pop();

            int N = GeneralDataForExecutors.stack.peek();
            GeneralDataForExecutors.stack.pop();

            ArrayList<Integer> indexesI = new ArrayList<>();
            int balanceDoLoop = 1;
            boolean flagDoubleQuotes = false;
            int indexNow = -1;

            for (String s : commands) {
                command = s;
                indexNow += command.length();

                if (command.equals(".\"")) {
                    flagDoubleQuotes = true;
                } else if (command.charAt(command.length() - 1) == '"') {
                    flagDoubleQuotes = false;
                }

                if (!flagDoubleQuotes) {
                    if (command.equals("do")) {
                        balanceDoLoop++;
                    } else if (command.equals("loop")) {
                        balanceDoLoop--;
                    } else if (balanceDoLoop == 1 && command.equals("i")) {
                        indexesI.add(indexNow);
                    }
                }

                ++indexNow;
            }

            String result = "";

            for (; i < N; ++i) {
                String newCommand = pattern;

                for (int j = indexesI.size() - 1; j >= 0 ; --j) {
                    String num = Integer.toString(i);
                    newCommand = newCommand.substring(0, indexesI.get(j)) 
                                 + num 
                                 + newCommand.substring(indexesI.get(j) + num.length());
                }

                result += newCommand + " ";
            }

            if (result.length() > 0) {
                result = result.substring(0, result.length() - 1);
            }

            GeneralDataForExecutors.CommandsForSecondProcessing = result;
        } catch (EmptyStackException e) {
            throw new ForthRuntimeException("Stack is empty");
        }

        return false;
    }

    private static final Logger LOGGER = LogManager.getLogger(OperatorDoLoop.class);
}
