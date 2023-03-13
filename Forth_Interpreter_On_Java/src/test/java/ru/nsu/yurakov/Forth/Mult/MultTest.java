package ru.nsu.yurakov.Forth.Mult;

import ru.nsu.yurakov.Forth.Factory.Factory;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.GeneralData.GeneralData;

import java.util.Stack;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class MultTest {

    @Test
    public void MultTests() {
        try {
            Stack<Integer> sharedStack = new Stack<Integer>();
            GeneralData data = new GeneralData(sharedStack, "",
                    "", System.out);
            ForthCommands instance = (ForthCommands) Factory.GetFactory().CreateInstance("*");
            instance.AddGeneralData(data);

            data.stack.push(3);
            data.stack.push(3);
            assertFalse(instance.Run());
            assertEquals(9, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());

            Exception ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());

            data.stack.push(1);

            ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());

            data.stack.pop();

            data.stack.push(200);
            data.stack.push(0);
            assertFalse(instance.Run());
            assertEquals(0, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());

            data.stack.push(-10);
            data.stack.push(5);
            assertFalse(instance.Run());
            assertEquals(-50, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());

            data.stack.push(-3);
            data.stack.push(-2);
            assertFalse(instance.Run());
            assertEquals(6, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());
        } catch (Exception ex) {
            System.out.println("Error: " + ex.getMessage());
        }
    }
}
