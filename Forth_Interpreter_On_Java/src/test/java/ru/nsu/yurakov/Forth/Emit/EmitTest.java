package ru.nsu.yurakov.Forth.Emit;

import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

public class EmitTest {

    @Test
    public void EmitTests() {
        try (ByteArrayOutputStream out = new ByteArrayOutputStream()) {
            PrintStream output = new PrintStream(out, true);
            InputStream input = null;

            ForthInterpreter forth = new ForthInterpreter(input, output);

            forth.InterpretString("65 66 67 emit emit emit");
            assertEquals("< C B A ", out.toString());
            out.reset();

            forth.InterpretString("emit");
            assertEquals("< Error: Stack is empty", out.toString());
            out.reset();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
