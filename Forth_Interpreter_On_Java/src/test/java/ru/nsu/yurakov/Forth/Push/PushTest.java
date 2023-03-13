package ru.nsu.yurakov.Forth.Push;

import ru.nsu.yurakov.Forth.Factory.Factory;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.GeneralData.GeneralData;

import java.util.Stack;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class PushTest {

    @Test
    public void PushTests() {
        try {
            Stack<Integer> sharedStack = new Stack<Integer>();
            GeneralData Data = new GeneralData(sharedStack, "",
                    "", System.out);
            ForthCommands instance = (ForthCommands) Factory.GetFactory().CreateInstance("push");
            instance.AddGeneralData(Data);

            Data.CommandText = "1";
            assertFalse(instance.Run());
            assertEquals(1, Data.stack.peek());

            Data.CommandText = "2";
            assertFalse(instance.Run());
            assertEquals(2, Data.stack.peek());

            Data.CommandText = "3";
            assertFalse(instance.Run());
            assertEquals(3, Data.stack.peek());

            Data.stack.pop();
            assertEquals(2, Data.stack.peek());
            Data.stack.pop();
            assertEquals(1, Data.stack.peek());
            Data.stack.pop();
            assertTrue(Data.stack.empty());

            Data.CommandText = "-200";
            assertFalse(instance.Run());
            assertEquals(-200, Data.stack.peek());
            Data.stack.pop();
            assertTrue(Data.stack.empty());
        } catch (Exception ex) {
            System.out.println("Error: " + ex.getMessage());
        }
    }
}
