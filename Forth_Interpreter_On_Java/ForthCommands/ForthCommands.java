package ForthCommands;

import GeneralData.GeneralData;

public abstract class ForthCommands {
    public ForthCommands() {}

    // Executing the invoked command
    public abstract boolean Run();
    // Uploading basic data to the executor
    public void AddGeneralData (GeneralData gendata) {
        GeneralDataForExecutors = gendata;
    }
    public GeneralData GetGenetalData () {
        return GeneralDataForExecutors;
    }
    protected GeneralData GeneralDataForExecutors;
}