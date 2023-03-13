package ru.nsu.yurakov.Forth.Drop;

import ru.nsu.yurakov.Forth.Factory.Factory;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.GeneralData.GeneralData;

import java.util.Stack;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
public class DropTest {

    @Test
    public void DropTests() {
        try {
            Stack<Integer> sharedStack = new Stack<Integer>();
            GeneralData data = new GeneralData(sharedStack, "",
                    "", System.out);
            ForthCommands instance = ForthCommands.class.cast(Factory.GetFactory().CreateInstance("drop"));
            instance.AddGeneralData(data);

            data.stack.push(1);
            assertFalse(instance.Run());
            assertTrue(data.stack.empty());

            data.stack.push(2);
            data.stack.push(3);
            assertFalse(instance.Run());
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
