#pragma once

#include "Factory.hpp"

namespace ForthFactoryRegistrations {

    template <typename T>
    class FactoryRegistrationCommands
    {
    public:
        // Creating a class of function for Register Generator
        FactoryRegistrationCommands(const std::string NameCommand)
        {
            Factory::get().RegisterGenerator(NameCommand, []() { return static_cast  <ForthCommands*>(new T()); });
        }
    };
}