package ru.nsu.yurakov.Forth.Checks;

import java.math.BigInteger;

public class Checks {
    /** Checks whether this string is a number
     * @param str The string that is being checked
     * @return true - number, false - not a number
     * @throws RuntimeException If the number is greater or less than int
     */
    public static boolean IsNumber(String str) throws RuntimeException {
        BigInteger num;

        try {
            num = new BigInteger(str);
        } catch (NumberFormatException e) {
            return false;
        }

        if ((num.compareTo(BigInteger.valueOf(Integer.MIN_VALUE)) < 0) || (BigInteger.valueOf(Integer.MAX_VALUE).compareTo(num) < 0)) {
            throw new RuntimeException("Integer OverFlow");
        }

        return true;
    }
}
