#include "Push.hpp"

bool Push::Run () {
    GeneralDataForExecutors.Stack->push (stoi(GeneralDataForExecutors.CommandText));

    return false;
}

namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Push> Command_push ("push");
}