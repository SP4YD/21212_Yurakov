package ru.nsu.yurakov.Forth.Point;

import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class PointTest {

    @Test
    public void PointTests() {
        try (ByteArrayOutputStream out = new ByteArrayOutputStream()) {
            PrintStream output = new PrintStream(out, true);
            InputStream input = null;

            ForthInterpreter forth = new ForthInterpreter(input, output);

            forth.InterpretString("1 2 3 4 5 . .");
            assertEquals("< 5 4 ", out.toString());
            out.reset();

            forth.InterpretString(".");
            assertEquals("< Error: Stack is empty", out.toString());
            out.reset();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
