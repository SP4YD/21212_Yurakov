package ru.nsu.yurakov.Forth.LogOperEqually;

import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

/**
 * Compares the equality of the first number on the stack and the second<br>
 * Pushes the result on the stack<br>
 * 0 if second != first<br>
 * 1 if second == first
 */
public class LogOperEqually extends ForthCommands {

    @Override
    public boolean Run() throws ForthRuntimeException {
        int a = 0;
        int b = 0;
        try {
            a = GeneralDataForExecutors.stack.peek();
            GeneralDataForExecutors.stack.pop();
        } catch (RuntimeException ex) {
            throw new ForthRuntimeException("Stack is empty");
        }
        try {
            b = GeneralDataForExecutors.stack.peek ();
            GeneralDataForExecutors.stack.pop ();
        } catch (RuntimeException ex) {
            GeneralDataForExecutors.stack.push(a);
            throw new ForthRuntimeException("Stack is empty");
        }

        GeneralDataForExecutors.stack.push ((b == a) ? 1 : 0);

        return false;
    }
}
