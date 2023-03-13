package ru.nsu.yurakov.Forth.PrintingLine;

import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class PrintingLineTest {

    @Test
    public void PrintingLineTest() {
        try (ByteArrayOutputStream out = new ByteArrayOutputStream()) {
            PrintStream output = new PrintStream(out, true);
            InputStream input = null;

            ForthInterpreter forth = new ForthInterpreter(input, output);

            forth.InterpretString(".\" Hello World\"");
            assertEquals("< Hello World ", out.toString());
            out.reset();

            forth.InterpretString(".\" \"");
            assertEquals("<  ", out.toString());
            out.reset();

            forth.InterpretString(".\" Hello\"World\"");
            assertEquals("< Hello\"World ", out.toString());
            out.reset();

            forth.InterpretString(".\" Hello\" .\" World\"");
            assertEquals("< Hello World ", out.toString());
            out.reset();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
