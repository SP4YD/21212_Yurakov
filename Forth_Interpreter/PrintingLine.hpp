#include "ForthCommands.hpp"
#include <iostream>

class PrintLine: private ForthCommands {
public:
    static ForthCommands* Creation ();

    bool Run () override;

    void Print (std::string str);
};