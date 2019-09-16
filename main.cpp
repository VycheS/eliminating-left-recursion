#include <iostream>
#include <string>
#include "grammar.h"

using namespace std;

void showHelp();

int main()
{

    showHelp();
    Grammar grammar;
    string str;
    cout << "INPUT:" << endl;

    getline(cin, str);
    while (str.length()) {
        grammar.insert(str);
        getline(cin, str);
    }

    try {
        cout << "OUTPUT:" << endl;
        grammar.start();
    } catch (string err) {
        cout << err;
    }

    cin.get();
    return 0;
}

void showHelp()
{
    cout << "---------------------------" << endl
         << "Format: A -> xxx | xxx" << endl
         << "Input an empty line for end" << endl
         << "---------------------------" << endl;
}
