package ru.nsu.yurakov.Forth.Parser;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.ArrayList;

/**
 * Splits a string into commands
 */
public class Parser {
    /** Splits a string into commands
     * @param str The string that will be parsed
     * @return Array of strings parsed by a special method
     * @throws RuntimeException If there were syntax errors in the if or do loop
     */
    public static ArrayList<String> Parsing (String str) throws RuntimeException{
        LOGGER.info("Was launched Parsing(" + str + ")");
        ArrayList <String> splitStr = new ArrayList<>();
        String[] commands = str.split(" ");

        for (int i = 0; i < commands.length; ++i) {
            String command = commands[i];
            String result;
            if (command.equals(".\"")) {
                result = command;

                ++i;
                for (; i < commands.length; ++i) {
                    command = commands[i];
                    if (command.charAt(command.length() - 1) == '"') {
                        break;
                    }
                    result += " " + command;
                }

                splitStr.add(result + " " + command);
                result = "";

                String tmp = splitStr.get(splitStr.size() - 1);
                if (tmp.charAt(tmp.length() - 1) != '"') {
                    throw new RuntimeException("Syntax Error");
                }
            }
            else if (command.equals("if")) {
                result = "";
                splitStr = ParsingIf(command, i + 1, commands.length, splitStr, commands);
                i += splitStr.get(splitStr.size() - 1).split(" ").length - 1;
            }
            else if (command.equals("do")) {
                result = "";
                splitStr = ParsingDo(command, i + 1, commands.length, splitStr, commands);
                i += splitStr.get(splitStr.size() - 1).split(" ").length - 1;
            }
            else {
                splitStr.add(command); 
            }   
        }

        return splitStr;
    }

    private static ArrayList<String> ParsingIf (String result, 
                                             int i, 
                                             int countCommand, 
                                             ArrayList<String> splitStr, 
                                             String[] commands) throws RuntimeException {
        LOGGER.info("Was launched ParsingIf");
        result = "if";
        int countIf = 1;
        int countThen = 0;
        int countSemicolon = 0;
        int countElse = 0;
        boolean flagDoubleQuotes = false;
        String tmp;

        for (;((countIf != countThen) || (countIf != countSemicolon)) && (countIf >= countElse) && i < countCommand; ++i) {
            tmp = commands[i];
            if (tmp.equals(".\"")) {
                flagDoubleQuotes = true;
            }
            else if (tmp.charAt(tmp.length() - 1) == '"') {
                flagDoubleQuotes = false;
            }

            if (!flagDoubleQuotes) {
                if (tmp.equals("if")) {
                    countIf++;
                }
                else if (tmp.equals("else")) {
                    countElse++;
                }
                else if (tmp.equals("then")) {
                    countThen++;
                }
                else if (tmp.equals(";")) {
                    countSemicolon++;
                }
            }

            result += " " + tmp;
        }

        splitStr.add(result);

        if (countElse > countIf || countIf > countThen || countIf < countThen || 
            countIf > countSemicolon || countIf < countSemicolon) {
            throw new RuntimeException("Syntax Error");
        }

        return splitStr;
    }
    
    private static ArrayList<String> ParsingDo (String result, 
                                            int i, 
                                            int countCommand, 
                                            ArrayList<String> splitStr, 
                                            String[] commands) throws RuntimeException {
        LOGGER.info("Was launched ParsingDo");
        result = "do";
        int countDo = 1;
        int countLoop = 0;
        int countSemicolon = 0;
        int countThen = 0;
        boolean flagDoubleQuotes = false;
        String tmp;

        for (;((countDo != countLoop) || (countDo != (countSemicolon - countThen))) && i < countCommand; ++i) {
            tmp = commands[i];
            if (tmp.equals(".\"")) {
                flagDoubleQuotes = true;
            }
            else if (tmp.charAt(tmp.length() - 1) == '"') {
                flagDoubleQuotes = false;
            }

            if (!flagDoubleQuotes) {
                if (tmp.equals("do")) {
                    countDo++;
                }
                else if (tmp.equals("loop")) {
                    countLoop++;
                }
                else if (tmp.equals("then")) {
                    countThen++;
                }
                else if (tmp.equals(";")) {
                    countSemicolon++;
                }
            }

            result += " " + tmp;
        }

        splitStr.add(result);

        if (countDo > countLoop || countDo < countLoop ||
            countDo > (countSemicolon - countThen) || countDo < (countSemicolon - countThen)) { 
                throw new RuntimeException("Syntax Error");
        }

        return splitStr;
    }

    private static final Logger LOGGER = LogManager.getLogger(Parser.class);
}
