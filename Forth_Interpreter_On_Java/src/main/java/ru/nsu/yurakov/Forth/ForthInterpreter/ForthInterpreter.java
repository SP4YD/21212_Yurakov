package ru.nsu.yurakov.Forth.ForthInterpreter;

import java.io.InputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Scanner;
import java.util.Stack;

import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.LogManager;

import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.Parser.Parser;
import ru.nsu.yurakov.Forth.GeneralData.GeneralData;
import ru.nsu.yurakov.Forth.Checks.Checks;
import ru.nsu.yurakov.Forth.Factory.Factory;

public class ForthInterpreter {
    private ForthInterpreter() {}

    private ForthInterpreter (ForthInterpreter other) {}

    /** A standard constructor that sets the input and output flow
     * @param in Input stream
     * @param out Output stream
     */
    public ForthInterpreter(InputStream in, PrintStream out) {
        LOGGER.info("Was launched ForthInterpreter");
        isConsole = System.in.equals(in);
        inputFile = in;
        outputFile = out;
    }

    /** Executes the incoming string
     * @param input The line to be executed
     */
    public void InterpretString(String input) {
        LOGGER.info("Was launched InterpretString");
        sharedStack = new Stack<>();
        outputFile.print("< ");

        boolean someCout = InterpretCommand(input);

        if (!someCout) {
            outputFile.print("ok");
        }
    }

    /**
     * Starts the interpreter to work with the specified threads
     */
    public void RunInterpretation() {
        LOGGER.info("Was launched RunInterpretation");
        boolean someCout;
        String str;
        sharedStack = new Stack<>();

        if (isConsole) {
            outputFile.print("> ");
        }

        try {
            Scanner scan = new Scanner(inputFile);
            str = scan.nextLine();
            while (!str.equals("exit")) {
                outputFile.print("< ");

                someCout = InterpretCommand(str);

                if (!someCout) {
                    outputFile.print("ok");
                }
                outputFile.println();
                if (isConsole) {
                    outputFile.print("> ");
                }
                str = scan.nextLine();
            }
        } catch (Exception ex) {
            if (Objects.equals(ex.getMessage(), "No line found")) {
                return;
            }
            outputFile.println("ERROR: " + ex.getMessage());
        }
    }

    /** Executing the passed command for RunInterpretation
     * @param str The line to be executed
     * @return true if something was output to out else false
     */
    boolean InterpretCommand(String str) {
        LOGGER.info("Was launched InterpretCommand with command " + str);
        ForthCommands executableCommand = null;
        String commandText = "";
        String commandsForSecondProcessing = "";
        boolean someCout = false;

        ArrayList<String> commands;

        try {
            commands = Parser.Parsing(str);
        } catch (RuntimeException e) {
            outputFile.print("Error in Parser: " + e.getMessage());
            return true;
        }

        GeneralData gendata = new GeneralData(sharedStack, commandText, 
                            commandsForSecondProcessing, outputFile);

        for (int i = 0; i < commands.size(); ++i) {
            gendata.CommandText = commands.get(i);
            String command = gendata.CommandText.split(" ")[0];
            try {
                if (Checks.IsNumber(command)) {
                    command = "push";
                }

                executableCommand = (ForthCommands) Factory.GetFactory().CreateInstance(command);

                executableCommand.AddGeneralData(gendata);
                someCout = executableCommand.Run() || someCout;

                if (gendata.CommandsForSecondProcessing.length() > 0) {
                    someCout = InterpretCommand(gendata.CommandsForSecondProcessing) || someCout;
                }
                gendata.CommandsForSecondProcessing = "";
            } catch (ClassNotFoundException ex) {
                outputFile.print("Error in factory: " + ex.getMessage());
                return true;
            } catch (RuntimeException ex) {
                outputFile.print("Error: " + ex.getMessage());
                return true;
            }
        }
        return someCout;
    }

    /**
     * Shared stack for all instances
     */
    private Stack<Integer> sharedStack;
    /**
     * Output to the console or not
     */
    private boolean isConsole;
    /**
     * Then where will the reading be conducted from
     */
    private InputStream inputFile;
    /**
     * Where will the recording be conducted
     */
    private PrintStream outputFile;

    private static final Logger LOGGER = LogManager.getLogger(ForthInterpreter.class);
}
