package ru.nsu.yurakov.Forth.Division;

import ru.nsu.yurakov.Forth.Factory.Factory;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.GeneralData.GeneralData;

import java.util.Stack;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class DivisionTest {

    @Test
    public void DivisionTests() throws Exception {
        Stack<Integer> sharedStack = new Stack<Integer>();
        GeneralData data = new GeneralData(sharedStack, "",
                "", System.out);
        ForthCommands instance = (ForthCommands) Factory.GetFactory().CreateInstance("/");


        instance.AddGeneralData(data);

        data.stack.push(15);
        data.stack.push(3);


        assertFalse(instance.Run());
        assertEquals(5, data.stack.peek());
        data.stack.pop();
        assertTrue(data.stack.empty());

        Exception ex = assertThrows(Exception.class, instance::Run);
        assertEquals("Stack is empty", ex.getMessage());

        data.stack.push(1);
        ex = assertThrows(Exception.class, instance::Run);
        assertEquals("Stack is empty", ex.getMessage());
        data.stack.pop();

        data.stack.push(15);
        data.stack.push(0);
        ex = assertThrows(Exception.class, instance::Run);
        assertEquals("Division by zero", ex.getMessage());

        data.stack.push(15);
        data.stack.push(-5);
        assertFalse(instance.Run());
        assertEquals(-3, data.stack.peek());
        data.stack.pop();
        assertTrue(data.stack.empty());

        data.stack.push(5);
        data.stack.push(10);
        assertFalse(instance.Run());
        assertEquals(0, data.stack.peek());
        data.stack.pop();
        assertTrue(data.stack.empty());

        data.stack.push(-21);
        data.stack.push(-3);
        assertFalse(instance.Run());
        assertEquals(7, data.stack.peek());
        data.stack.pop();
        assertTrue(data.stack.empty());

    }
}
