package ru.nsu.yurakov.Forth.LogOperMore;

import ru.nsu.yurakov.Forth.Factory.Factory;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.GeneralData.GeneralData;

import java.util.Stack;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class LogOperMoreTest {

    @Test
    public void LogOperMoreTests() {
        try {
            Stack<Integer> sharedStack = new Stack<Integer>();
            GeneralData data = new GeneralData(sharedStack, "",
                    "", System.out);
            ForthCommands instance = (ForthCommands) Factory.GetFactory().CreateInstance(">");
            instance.AddGeneralData(data);

            data.stack.push(3);
            data.stack.push(2);
            assertFalse(instance.Run());
            assertEquals(1, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());

            data.stack.push(2);
            data.stack.push(3);
            assertFalse(instance.Run());
            assertEquals(0, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());

            Exception ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());

            data.stack.push(1);

            ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());

            data.stack.pop();
        } catch (Exception ex) {
            System.out.println("Error: " + ex.getMessage());
        }
    }
}
