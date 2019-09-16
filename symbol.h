#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <vector>

using namespace std;

class Symbol
{
public:
    Symbol();
    Symbol(string);
    string getSymbolStr() const;
    void setSymbolStr(string);
    bool operator==(Symbol arg){return arg._symbol == _symbol;}
protected:
    string _symbol;
};

#endif // SYMBOL_H
