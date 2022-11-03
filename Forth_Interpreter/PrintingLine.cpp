#include "PrintingLine.hpp"

bool PrintingLine::Run () {
    NameCommand.pop_back();
    std::cout << NameCommand << " ";

    return true;
}
