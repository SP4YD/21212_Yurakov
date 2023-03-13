package ru.nsu.yurakov.Forth.Factory;

import org.junit.jupiter.api.Test;
import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

public class FactoryTest {

    @Test
    public void FactoryTests() {
        try (ByteArrayOutputStream out = new ByteArrayOutputStream()) {
            PrintStream output = new PrintStream(out, true);
            InputStream input = null;

            ForthInterpreter forth = new ForthInterpreter(input, output);

            forth.InterpretString("moda");
            assertEquals("< Error in factory: in CreateInstance with the name - \"moda\"", out.toString());
            out.reset();

            forth.InterpretString("sdfsdg");
            assertEquals("< Error in factory: in CreateInstance with the name - \"sdfsdg\"", out.toString());
            out.reset();

            forth.InterpretString("ifa");
            assertEquals("< Error in factory: in CreateInstance with the name - \"ifa\"", out.toString());
            out.reset();

        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
