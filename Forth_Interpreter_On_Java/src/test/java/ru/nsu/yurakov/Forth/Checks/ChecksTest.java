package ru.nsu.yurakov.Forth.Checks;

import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class ChecksTest {

    @Test
    public void ChecksTests() {
        try (ByteArrayOutputStream out = new ByteArrayOutputStream()) {
            PrintStream output = new PrintStream(out, true);
            InputStream input = null;

            ForthInterpreter forth = new ForthInterpreter(input, output);

            forth.InterpretString("2147483648");
            assertEquals("< Error: Integer OverFlow", out.toString());
            out.reset();

            forth.InterpretString("-2147483649");
            assertEquals("< Error: Integer OverFlow", out.toString());
            out.reset();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}