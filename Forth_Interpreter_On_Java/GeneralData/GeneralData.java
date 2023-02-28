package GeneralData;

import java.util.Stack;

public class GeneralData {
    public GeneralData () {}
    public GeneralData (Stack<Integer> newStack, String commandText, String commandsForSecondProcessing) {
        stack = newStack; 
        CommandText = commandText; 
        CommandsForSecondProcessing = commandsForSecondProcessing;
    }
    
    // Link to the general stack of the program
    public Stack<Integer> stack;
    // The name of the command to be executed or processed
    public String CommandText;
    // A reference to a string that stores commands that need to be processed a second time
    public String CommandsForSecondProcessing;
}