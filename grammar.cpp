#include "grammar.h"

Grammar::Grammar(){}

void Grammar::insert(string str)
{
    _rules.push_back(format(str));
}

void Grammar::start()
{
    removingLeftRecursion();
    output();
}

void Grammar::output()
{
    for (auto rule : _rules) {
        string outputStr = "";
        for (auto symbol : rule) {
            outputStr.append(symbol.getSymbolStr());
            if ((symbol.getSymbolStr() == "->") || (symbol.getSymbolStr() == "|")) {
                string str;
                if (symbol.getSymbolStr() == "->") {
                    outputStr.pop_back();
                    str = "->";
                } else {
                    str = "|";
                }
                outputStr.pop_back();
                outputStr.append(" ");
                outputStr.append(str);
                outputStr.append(" ");
            }
        }
        cout << outputStr << endl;
    }
}


//проверка наличия левой рекурсии
bool Grammar::checkLeftRecursion(const vector<Symbol> &rule)
{
    Symbol left = rule[0];
    bool first = true;
    for (auto it = rule.begin() + 2; it != rule.end(); ++it) {
        if (first) {
            if (it->getSymbolStr() == left.getSymbolStr()) {
                return true;
            } else {
                first = false;
            }
        } else if (it->getSymbolStr() == "|") {
            first = true;
        }
    }
    return false;
}

//разделение на группы
vector<Grammar::Group> Grammar::splitIntoGroups(const vector<Symbol> &rule)
{
    //группы груп
    vector<Group> groups;
    //временный символ левого нетерминала
    Symbol left = rule[0];
    //временное хранение группы
    vector<Symbol> symbolGroup;
    //разложение правила по группам
    Name nameGroup = Name::B;
    //флаг первой итерации
    bool firstIter = true;
    //разложение правила по группам
    for (auto it = rule.begin() + 2; it != rule.end(); ++it) {
        if (it->getSymbolStr() == "|") {
            groups.push_back(Group{symbolGroup, nameGroup});
            symbolGroup.clear();
            firstIter = true;
        } else if (firstIter && (left == *it)) {
            nameGroup = Name::a;
            firstIter = false;
        } else if (firstIter && !(left == *it)) {
            nameGroup = Name::B;
            firstIter = false;
            symbolGroup.push_back(*it);
        } else {
            symbolGroup.push_back(*it);
        }
    }
    groups.push_back(Group{symbolGroup, nameGroup});
    return groups;
}

//устранение левой рекурсии
void Grammar::removingLeftRecursion()
{
    //новые правила
    vector<vector<Symbol>> newRules;

    //устранение левой рекурсии с последующим вкладыванием в новые правила
    for (auto rule : _rules) {
        if (checkLeftRecursion(rule)) {

            vector<Group> groups = splitIntoGroups(rule);//группы груп
            Symbol left = rule[0];//символ левого нетерминала
            Symbol newLeft(left.getSymbolStr() + "\'");//символ нового левого нетерминала

            //лямда. Алгоритм для создание нового правила из групп
            auto createRules = [&](Symbol first, Name nameGroup)
            {
                vector<Symbol> tmpRule;//новые правила
                tmpRule.push_back(first);
                tmpRule.push_back(Symbol("->"));
                for (auto symbols : groups) {
                    if (symbols.name == nameGroup) {
                        for (auto symbol : symbols.group) {
                            tmpRule.push_back(symbol);
                        }
                        tmpRule.push_back(Symbol("|"));

                        for (auto symbol : symbols.group) {
                            tmpRule.push_back(symbol);
                        }
                        tmpRule.push_back(newLeft);
                        tmpRule.push_back(Symbol("|"));
                    }
                }
                tmpRule.pop_back(); //удаление в конце "|"
                newRules.push_back(tmpRule);
            };

            createRules(left, Name::B);//создание для первой группы
            createRules(newLeft, Name::a);//создание для первой группы

        } else { // если не было левой рекурсии
            newRules.push_back(rule);
        }
    }
    _rules = newRules;
}

//приведение к нужному формату для последующей обработки
vector<Symbol> Grammar::format(const string &str)
{
    string strRule;
    vector<Symbol> resultRule;
    //складывание результата без пробела и табуляции
    for (auto c : str) {
        if (c != ' ' && c != '\t') {
            strRule += c;
        }
    }
    //проверка нужного формата. В случае ошибки кидаем исключение
    auto i = str.find('-');
    if (str[i + 1] != '>') {
        throw "Wrong input format";
    }

    //разбитие на символы с последующим вложением в вектор
    for (auto c : strRule) {
        if (c == '-') { // для того чтобы полностью стрелочку положить в символ
            string tmp;
            tmp.push_back(c);
            tmp.push_back('>');
            Symbol symbol(tmp);
            resultRule.push_back(symbol);
        } else if (c == '>') { // пропускается, т.к. выше мы добавили её после дефиса
            continue;
        } else {
            //одинарная кавычка не может быть одной,
            //т.к. она существует вместе с символом
            if (c == '\'') {//добавление к предыдущему символу
                string tmp = resultRule.back().getSymbolStr();
                resultRule.pop_back();
                tmp.push_back(c);
                Symbol symbol(tmp);
                resultRule.push_back(symbol);
            } else { //добавляется одинарный символ
                string tmp;
                tmp.push_back(c);
                Symbol symbol(tmp);
                resultRule.push_back(symbol);
            }
        }
    }

    return resultRule;
}
