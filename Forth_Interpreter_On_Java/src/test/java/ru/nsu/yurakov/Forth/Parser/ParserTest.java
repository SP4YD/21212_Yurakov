package ru.nsu.yurakov.Forth.Parser;

import org.junit.jupiter.api.Test;
import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

public class ParserTest {

    @Test
    public void ParserTests() {
        try (ByteArrayOutputStream out = new ByteArrayOutputStream()) {
            PrintStream output = new PrintStream(out, true);
            InputStream input = null;

            ForthInterpreter forth = new ForthInterpreter(input, output);

            forth.InterpretString("10 0 do i . loop loop ;");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();

            forth.InterpretString("10 0 do i . loop");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();

            forth.InterpretString("10 0 do i . ;");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();

            forth.InterpretString("10 0 do do i . loop ;");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();

            forth.InterpretString("10 0 do i .");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();

            forth.InterpretString("0 if 1 . else 0 . then then ;");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();

            forth.InterpretString("0 if 1 . else else 0 . then ;");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();

            forth.InterpretString("0 if 1 . else 0 . then else ;");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();

            forth.InterpretString("0 if if 1 . else 0 . then ;");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();

            forth.InterpretString("0 if 1 . else if 0 . then ;");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();

            forth.InterpretString("0 if 1 . else 0 . ;");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();

            forth.InterpretString("0 if 1 . else 0 . then");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();

            forth.InterpretString("0 if 1 . else 0 .");
            assertEquals("< Error in Parser: Syntax Error", out.toString());
            out.reset();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
