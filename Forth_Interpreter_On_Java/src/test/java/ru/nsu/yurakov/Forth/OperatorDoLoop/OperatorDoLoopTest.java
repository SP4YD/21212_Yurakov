package ru.nsu.yurakov.Forth.OperatorDoLoop;

import org.junit.jupiter.api.Test;
import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

public class OperatorDoLoopTest {

    @Test
    public void OperatorDoLoopTests() {
        try (ByteArrayOutputStream out = new ByteArrayOutputStream()) {
            PrintStream output = new PrintStream(out, true);
            InputStream input = null;

            ForthInterpreter forth = new ForthInterpreter(input, output);

            forth.InterpretString("10 0 do i . loop ;");
            assertEquals("< 0 1 2 3 4 5 6 7 8 9 ", out.toString());
            out.reset();

            forth.InterpretString("0 do i . loop ;");
            assertEquals("< Error: Stack is empty", out.toString());
            out.reset();

            forth.InterpretString("do i . loop ;");
            assertEquals("< Error: Stack is empty", out.toString());
            out.reset();

            forth.InterpretString("6 0 do i 1 + 0 do i . loop ; cr loop ;");
            assertEquals( "< 0 \n< 0 1 \n< 0 1 2 \n< 0 1 2 3 \n< 0 1 2 3 4 \n< 0 1 2 3 4 5 \n< ", out.toString());
            out.reset();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
