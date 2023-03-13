package ru.nsu.yurakov.Forth.ForthCommands;

import ru.nsu.yurakov.Forth.ForthRuntimeException.ForthRuntimeException;
import ru.nsu.yurakov.Forth.GeneralData.GeneralData;

public abstract class ForthCommands {
    public ForthCommands() {}

    /** Executing the invoked command
     * @return true if something was output to out else false
     * @throws ForthRuntimeException If something went wrong during the execution of the command
     */
    public abstract boolean Run() throws ForthRuntimeException;

    /** Uploading basic data to the executor
     * @param gendata Data to be copied
     */
    public void AddGeneralData (GeneralData gendata) {
        GeneralDataForExecutors = gendata;
    }

    protected GeneralData GeneralDataForExecutors;
}