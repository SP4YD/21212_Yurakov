#include "PrintingLine.hpp"

bool PrintingLine::Run () {
    CommandText.erase(CommandText.begin(), CommandText.begin() + 3);
    CommandText.pop_back();

    *Output << CommandText << " ";

    return true;
}
