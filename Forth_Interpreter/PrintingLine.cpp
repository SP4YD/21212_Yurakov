#include "PrintingLine.hpp"

bool PrintingLine::Run () {
    NameCommand.erase(NameCommand.begin(), NameCommand.begin() + 3);
    NameCommand.pop_back();

    std::cout << NameCommand << " ";

    return true;
}
