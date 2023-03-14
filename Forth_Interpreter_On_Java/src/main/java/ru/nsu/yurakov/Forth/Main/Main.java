package ru.nsu.yurakov.Forth.Main;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.PrintStream;

public class Main {
    public static void main(String[] args) {
        LOGGER.info("Was launched main(" + args + ")");
        InputStream inputFile = System.in;
        PrintStream outputFile = System.out;

        if (args.length == 2) {
            try {
                inputFile = new FileInputStream(args[0]);
                outputFile = new PrintStream(args[1]);
            } catch (FileNotFoundException e) {
                System.out.println("Error with open file");
                return;
            }
        } else if (args.length == 1) {
            try {
                inputFile = new FileInputStream(args[0]);
            } catch (FileNotFoundException e) {
                System.out.println("Error with open file");
                return;
            }
        }
        else if (args.length > 2) {
            System.out.println("Error with input arguments");
            return;
        }

        ForthInterpreter interpreter = new ForthInterpreter(inputFile, outputFile);
        interpreter.RunInterpretation();
    }

    private static final Logger LOGGER = LogManager.getLogger(Main.class);
}