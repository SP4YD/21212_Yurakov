#include "ForthCommands.hpp"

GeneralData::GeneralData (std::stack <int> *stack, std::string commandText, 
                 std::string *commandsForSecondProcessing, std::istream *in, std::ostream *out) 
                 : Stack(stack), CommandText(commandText), 
                   CommandsForSecondProcessing(commandsForSecondProcessing),
                   Input(in), Output(out) {}

void ForthCommands::AddGeneralData (GeneralData gendata) {
    GeneralDataForExecutors = gendata;
}