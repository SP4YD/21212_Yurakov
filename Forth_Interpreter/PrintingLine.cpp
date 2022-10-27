#include "PrintingLine.hpp"

ForthCommands* PrintLine::Creation () {
    return new PrintLine;
}

bool PrintLine::Run () {
    Print (NameCommand);
    
    return true;
}

void PrintLine::Print (std::string str) {
    NameCommand.pop_back();
    std::cout << "< " << NameCommand << std::endl;
}