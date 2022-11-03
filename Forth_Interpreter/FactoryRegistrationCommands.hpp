#pragma once

#include "Factory.hpp"

namespace ForthFactoryRegistrations {

    template <typename T>
    class FactoryRegistrationCommands
    {
    public:
        FactoryRegistrationCommands(const std::string NameCommand)
        {
            Factory::get().RegisterGenerator(NameCommand, []() { return static_cast  <ForthCommands*>(new T()); });
        }
    };
}