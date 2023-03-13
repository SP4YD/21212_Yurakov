package ru.nsu.yurakov.Forth.Sub;

import ru.nsu.yurakov.Forth.Factory.Factory;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.GeneralData.GeneralData;

import java.util.Stack;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class SubTest  {

    @Test
    public void SubTests() {
        try {
            Stack<Integer> sharedStack = new Stack<Integer>();
            GeneralData data = new GeneralData(sharedStack, "",
                    "", System.out);
            ForthCommands instance = (ForthCommands) Factory.GetFactory().CreateInstance("-");
            instance.AddGeneralData(data);

            data.stack.push(10);
            data.stack.push(3);
            assertFalse(instance.Run());
            assertEquals(7, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());

            Exception ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());

            data.stack.push(1);

            ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());

            data.stack.pop();

            data.stack.push(200);
            data.stack.push(-200);
            assertFalse(instance.Run());
            assertEquals(400, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());
        } catch (Exception ex) {
            System.out.println("Error: " + ex.getMessage());
        }
    }
}
