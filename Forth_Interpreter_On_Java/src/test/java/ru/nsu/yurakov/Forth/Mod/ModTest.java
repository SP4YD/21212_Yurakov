package ru.nsu.yurakov.Forth.Mod;

import ru.nsu.yurakov.Forth.Factory.Factory;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.GeneralData.GeneralData;

import java.util.Stack;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class ModTest {

    @Test
    public void ModTests() {
        try {
            Stack<Integer> sharedStack = new Stack<Integer>();
            GeneralData data = new GeneralData(sharedStack, "",
                    "", System.out);
            ForthCommands instance = (ForthCommands) Factory.GetFactory().CreateInstance("mod");
            instance.AddGeneralData(data);

            data.stack.push(10);
            data.stack.push(3);
            assertFalse(instance.Run());
            assertEquals(1, data.stack.peek());
            data.stack.pop();
            assertTrue(data.stack.empty());

            Exception ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());

            data.stack.push(1);

            ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Stack is empty", ex.getMessage());

            data.stack.pop();

            data.stack.push(0);
            data.stack.push(3);
            assertFalse(instance.Run());
            assertEquals(data.stack.peek(), 0);
            data.stack.pop();
            assertTrue(data.stack.empty());

            data.stack.push(100);
            data.stack.push(0);

            ex = assertThrows(Exception.class, instance::Run);
            assertEquals("Division by zero", ex.getMessage());
        } catch (Exception ex) {
            System.out.println("Error: " + ex.getMessage());
        }
    }
}
