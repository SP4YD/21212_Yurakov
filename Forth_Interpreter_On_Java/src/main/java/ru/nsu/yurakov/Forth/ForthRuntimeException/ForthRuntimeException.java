package ru.nsu.yurakov.Forth.ForthRuntimeException;

/**
 * Exception that was received during the execution of the command
 */
public class ForthRuntimeException extends RuntimeException{

    /** Creates a RuntimeException with the passed message
     * @param message Error Message
     */
    public ForthRuntimeException(String message) {
        super(message);
    }
}