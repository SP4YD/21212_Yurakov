package ru.nsu.yurakov.Forth.GeneralData;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

import java.io.PrintStream;
import java.util.Stack;

public class GeneralData {
    private GeneralData () {}

    /** Copies the passed parameters
     * @param newStack The stack that the instances will work with
     * @param commandText The command to be executed
     * @param commandsForSecondProcessing The command to be sent for secondary processing
     * @param output The output stream that the instances will work with
     */
    public GeneralData (Stack<Integer> newStack, String commandText, String commandsForSecondProcessing, PrintStream output) {
        LOGGER.info("Was launched GeneralData Constructor");
        stack = newStack; 
        CommandText = commandText; 
        CommandsForSecondProcessing = commandsForSecondProcessing;
        outputFile = output;
    }

    /**
     * Link to the general stack of the program
     */
    public Stack<Integer> stack;
    /**
     * The text of the command to be executed or processed
     */
    public String CommandText;
    /**
     * A reference to a string that stores commands that need to be processed a second time
     */
    public String CommandsForSecondProcessing;
    /**
     * The output stream that the instances will work with
     */
    public PrintStream outputFile;

    private static final Logger LOGGER = LogManager.getLogger(GeneralData.class);
}