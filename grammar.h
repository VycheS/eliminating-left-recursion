#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "symbol.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Grammar
{
protected://свои типы данных!
    enum class Name
    {
        B,
        a,
    };
    struct Group{
        vector<Symbol> group;
        Name name;
    };
public:
    Grammar();
    void insert(string);
    void start();
    void output();
protected://приватные переменные, обьекты
    vector<vector<Symbol>> _rules;
protected://приватные методы
    vector<Symbol> format(const string &str);
    void removingLeftRecursion();
    bool checkLeftRecursion(const vector<Symbol> &rule);
    vector<Group> splitIntoGroups(const vector<Symbol> &rule);

};

#endif // GRAMMAR_H
