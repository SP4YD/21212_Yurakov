#include "PrintingLine.hpp"

ForthCommands* PrintingLine::Creation () {
    return new PrintingLine;
}

bool PrintingLine::Run () {
    Print (NameCommand);
    
    return true;
}

void PrintingLine::Print (std::string str) {
    NameCommand.pop_back();
    std::cout << NameCommand << " ";
}