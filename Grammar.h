#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <bits/stdc++.h>
#include "Rule.h"
using namespace std;

class Grammar {
public:
    vector<Rule> rules;
    map<string, set<string>> FIRST, FOLLOW;
    set<string> terminals, nonterminals;
    string startSymbol;

    Grammar();

    bool isTerminal(const string &s) const;

    void computeFIRST();
    void computeFOLLOW();
};

#endif