#include "PrintingLine.hpp"

#include <ostream>

bool PrintingLine::Run () {
    GeneralDataForExecutors.CommandText.erase(GeneralDataForExecutors.CommandText.begin(),
                                              GeneralDataForExecutors.CommandText.begin() + 3);
    GeneralDataForExecutors.CommandText.pop_back();

    *GeneralDataForExecutors.Output << GeneralDataForExecutors.CommandText << " ";

    return true;
}

namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<PrintingLine> Command_printLine (".\"");
}