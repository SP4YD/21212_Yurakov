package ru.nsu.yurakov.Forth.Rot;

import ru.nsu.yurakov.Forth.Factory.Factory;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.GeneralData.GeneralData;

import java.util.Stack;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class RotTest {

    @Test
    public void RotTests() {
        try {
            Stack<Integer> sharedStack = new Stack<Integer>();
            GeneralData data = new GeneralData(sharedStack, "",
                    "", System.out);
            ForthCommands instance = (ForthCommands) Factory.GetFactory().CreateInstance("rot");
            instance.AddGeneralData(data);

            data.stack.push(4);
            data.stack.push(1);
            data.stack.push(2);
            data.stack.push(3);
            assertFalse(instance.Run());
            assertEquals(2, data.stack.peek());
            data.stack.pop();
            assertEquals(1, data.stack.peek());
            data.stack.pop();
            assertEquals(3, data.stack.peek());
            data.stack.pop();
            assertEquals(4, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());

            Exception ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());

            data.stack.push(1);

            ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());

            data.stack.push(2);

            ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
