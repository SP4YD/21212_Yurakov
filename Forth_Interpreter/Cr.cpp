#include "Cr.hpp"

#include <ostream>

bool Cr::Run () {
    *GeneralDataForExecutors.Output << std::endl << "< ";

    return true;
}
 
namespace ForthFactoryRegistrations {
    FactoryRegistrationCommands<Cr> Command_cr ("cr");
}