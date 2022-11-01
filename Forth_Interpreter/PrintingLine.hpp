#pragma once

#include <iostream>

#include "ForthCommands.hpp"


class PrintingLine: private ForthCommands {
public:
    static ForthCommands* Creation ();

    bool Run () override;

    void Print (std::string str);
};