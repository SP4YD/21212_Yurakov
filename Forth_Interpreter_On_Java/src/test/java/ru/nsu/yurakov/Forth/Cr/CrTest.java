package ru.nsu.yurakov.Forth.Cr;

import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class CrTest {

    @Test
    public void CrTests() {
        try (ByteArrayOutputStream out = new ByteArrayOutputStream()) {
            PrintStream output = new PrintStream(out, true);
            InputStream input = null;

            ForthInterpreter forth = new ForthInterpreter(input, output);

            forth.InterpretString("100 200 . cr .");
            assertEquals("< 200 \n< 100 ", out.toString());
            out.reset();

        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}

