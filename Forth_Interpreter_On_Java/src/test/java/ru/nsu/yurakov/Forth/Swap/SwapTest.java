package ru.nsu.yurakov.Forth.Swap;

import ru.nsu.yurakov.Forth.Factory.Factory;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.GeneralData.GeneralData;

import java.util.Stack;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class SwapTest {

    @Test
    public void SwapTests() {
        try {
            Stack<Integer> sharedStack = new Stack<Integer>();
            GeneralData data = new GeneralData(sharedStack, "",
                    "", System.out);
            ForthCommands instance = ForthCommands.class.cast(Factory.GetFactory().CreateInstance("swap"));
            instance.AddGeneralData(data);

            data.stack.push(1);
            data.stack.push(2);
            data.stack.push(3);
            assertFalse(instance.Run());
            assertEquals(2, data.stack.peek());
            data.stack.pop();
            assertEquals(3, data.stack.peek());
            data.stack.pop();
            assertEquals(1, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());

            Exception ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());

            data.stack.push(1);

            ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
