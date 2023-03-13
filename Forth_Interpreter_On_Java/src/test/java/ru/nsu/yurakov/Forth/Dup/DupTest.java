package ru.nsu.yurakov.Forth.Dup;

import ru.nsu.yurakov.Forth.Factory.Factory;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.GeneralData.GeneralData;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.util.Stack;

public class DupTest {

    @Test
    public void DupTests() {
        try {
            Stack<Integer> sharedStack = new Stack<Integer>();
            GeneralData data = new GeneralData(sharedStack, "",
                    "", System.out);
            ForthCommands instance = (ForthCommands) Factory.GetFactory().CreateInstance("dup");
            instance.AddGeneralData(data);

            data.stack.push(1);
            assertFalse(instance.Run());
            assertEquals(1, data.stack.peek());
            data.stack.pop();
            assertEquals(1, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());

            data.stack.push(2);
            data.stack.push(3);
            assertFalse(instance.Run());
            assertEquals(3, data.stack.peek());
            data.stack.pop();
            assertEquals(3, data.stack.peek());
            data.stack.pop();
            assertEquals(2, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());

            Exception ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());
        } catch (Exception ex) {
            System.out.println("Error: " + ex.getMessage());
        }
    }
}
