package Parser;
import java.util.ArrayList;

public class Parser {
    public static ArrayList<String> Parsing (String str) throws Exception{
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
                    throw new Exception("Syntax Error");
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
                                             String[] commands) throws Exception {
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
            throw new Exception("Syntax Error");
        }

        return splitStr;
    }
    
    private static ArrayList<String> ParsingDo (String result, 
                                            int i, 
                                            int countCommand, 
                                            ArrayList<String> splitStr, 
                                            String[] commands) throws Exception {
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
                throw new Exception("Syntax Error3");
        
        }

        return splitStr;
    }
}
