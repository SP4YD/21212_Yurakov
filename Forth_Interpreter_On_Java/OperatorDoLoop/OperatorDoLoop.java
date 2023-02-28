package OperatorDoLoop;

import java.util.EmptyStackException;
import java.util.ArrayList;

import ForthCommands.ForthCommands;

public class OperatorDoLoop extends ForthCommands{

    @Override
    public boolean Run() {
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

            for (int j = 0; j < commands.length; ++j) {
                command = commands[j];
                indexNow += command.length();

                if (command.equals(".\"")) {
                    flagDoubleQuotes = true;
                }
                else if (command.charAt(command.length() - 1) == '"') {
                    flagDoubleQuotes = false;
                }

                if (!flagDoubleQuotes) {
                    if (command.equals("do")) {
                        balanceDoLoop++;
                    }
                    else if (command.equals("loop")) {
                        balanceDoLoop--;
                    }
                    else if (balanceDoLoop == 1 && command.equals("i")) {
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
                                 + newCommand.substring(indexesI.get(j) + num.length(), newCommand.length());
                }

                result += newCommand + " ";
            }

            if (result.length() > 0) {
                result = result.substring(0, result.length() - 1);
            }

            GeneralDataForExecutors.CommandsForSecondProcessing = result;
        } catch (EmptyStackException e) {
            System.err.print(e.getMessage());
        }

        return false;
    }
    
}
