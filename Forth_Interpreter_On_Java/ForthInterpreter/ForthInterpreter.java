package ForthInterpreter;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

import ForthCommands.ForthCommands;
import Parser.Parser;
import GeneralData.GeneralData;
import Checks.Checks;
import Factory.Factory;

public class ForthInterpreter { 
    public ForthInterpreter() {} // нужно потом приват

    ForthInterpreter(ForthInterpreter other) {}

    public void RunInterpretation() {
        boolean someCout;
        String str;
        sharedStack = new Stack<>();

        System.out.print("> ");

        Scanner scan = new Scanner(System.in);
        while (true) {
            str = scan.nextLine();
            System.out.print("< ");
            someCout = InterpretCommand(str);

            if (!someCout) {
                System.out.print("ok");
            }
            System.out.println();
            System.out.print("> ");
        }
    }

    boolean InterpretCommand(String str) {
        ForthCommands executableCommand = null;
        String commandText = "";
        String commandsForSecondProcessing = "";
        boolean someCout = false;

        ArrayList<String> commands;

        try {
            commands = Parser.Parsing(str);
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return true;
        }

        GeneralData gendata = new GeneralData(sharedStack, commandText, 
                            commandsForSecondProcessing);

        for (int i = 0; i < commands.size(); ++i) {
            String command = commands.get(i);
            if (Checks.IsNumber(command)) {
                gendata.CommandText = commands.get(i);
                command = "push";
            } else if (command.length() > 1 && command.charAt(0) == '.' && command.charAt(1) == '"') {
                gendata.CommandText = command;
                command = ".\"";
            } else if (command.length() > 1 && command.charAt(0) == 'i' && command.charAt(1) == 'f') {
                gendata.CommandText = command;
                command = "if";
            } else if (command.length() > 1 && command.charAt(0) == 'd' && command.charAt(1) == 'o') {
                gendata.CommandText = command;
                command = "do";
            }

            executableCommand = ForthCommands.class.cast(Factory.GetFactory().CreateInstance(command));
            if (executableCommand == null) {
                System.out.print("Unknown command \"" + command + "\"");
                return true;
            }
            executableCommand.AddGeneralData(gendata);
            someCout = executableCommand.Run() || someCout;
            gendata = executableCommand.GetGenetalData();

            if (gendata.CommandsForSecondProcessing.length() > 0) {
                someCout = InterpretCommand (gendata.CommandsForSecondProcessing) || someCout;
            }
            gendata.CommandsForSecondProcessing = "";
        }

        return someCout;
    }

    private Stack<Integer> sharedStack;
}
