package ru.nsu.yurakov.Forth.OperatorIf;

import org.junit.jupiter.api.Test;
import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

public class OperatorIfTest {

    @Test
    public void OperatorIfTests() {
        try (ByteArrayOutputStream out = new ByteArrayOutputStream()) {
            PrintStream output = new PrintStream(out, true);
            InputStream input = null;

            ForthInterpreter forth = new ForthInterpreter(input, output);

            forth.InterpretString("1 if .\" Yes\" then ; .\" No\"");
            assertEquals("< Yes No ", out.toString());
            out.reset();

            forth.InterpretString("0 if .\" Yes\" then ; .\" No\"");
            assertEquals( "< No ", out.toString());
            out.reset();

            forth.InterpretString("1 if .\" Yes\" else .\" No\" then ;");
            assertEquals( "< Yes ", out.toString());
            out.reset();

            forth.InterpretString("0 if .\" Yes\" else .\" No\" then ;");
            assertEquals( "< No ", out.toString());
            out.reset();

            forth.InterpretString("if .\" Yes\" else .\" No\" then ;");
            assertEquals("< Error: Stack is empty", out.toString());
            out.reset();

            forth.InterpretString("1 if 2 . 3 if 4 . 5 . else 0 . then ; then ;");
            assertEquals( "< 2 4 5 ", out.toString());
            out.reset();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
