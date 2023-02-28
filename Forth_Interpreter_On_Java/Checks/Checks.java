package Checks;

public class Checks {
    public static boolean IsNumber(String str) throws StackOverflowError{
        long num;

        try {
            num = Integer.valueOf(str);
        } catch (NumberFormatException e) {
            return false;
        }

        if (num > Integer.MAX_VALUE || num < Integer.MIN_VALUE) {
            throw new StackOverflowError();
        }
        
        return true;
    }
}
