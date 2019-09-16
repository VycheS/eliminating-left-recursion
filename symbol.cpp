#include "symbol.h"

Symbol::Symbol(){}

Symbol::Symbol(string str): Symbol()
{
    setSymbolStr(str);
}

string Symbol::getSymbolStr() const
{
    return _symbol;
}

void Symbol::setSymbolStr(string str)
{
    _symbol = str;
}






