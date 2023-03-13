package ru.nsu.yurakov.Forth.Rot;

import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;

/**
 * Cyclically shifts the top three numbers
 */
public class Rot extends ForthCommands{

    @Override
    public boolean Run() throws ForthRuntimeException {
        int a = 0;
        int b = 0;
        int c = 0;
        try {
            a = GeneralDataForExecutors.stack.peek();
            GeneralDataForExecutors.stack.pop();
        } catch (RuntimeException ex) {
            throw new ForthRuntimeException("Stack is empty");
        }
        try {
            b = GeneralDataForExecutors.stack.peek ();
            GeneralDataForExecutors.stack.pop();
        } catch (RuntimeException ex) {
            GeneralDataForExecutors.stack.push(a);
            throw new ForthRuntimeException("Stack is empty");
        }
        try {
            c = GeneralDataForExecutors.stack.peek ();
            GeneralDataForExecutors.stack.pop();
        } catch (RuntimeException ex) {
            GeneralDataForExecutors.stack.push(b);
            GeneralDataForExecutors.stack.push(a);
            throw new ForthRuntimeException("Stack is empty");
        }

        GeneralDataForExecutors.stack.push(a);
        GeneralDataForExecutors.stack.push(c);
        GeneralDataForExecutors.stack.push(b);

        return false;
    }
}
