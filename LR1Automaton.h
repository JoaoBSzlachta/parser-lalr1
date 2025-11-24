#ifndef LR1AUTOMATON_H
#define LR1AUTOMATON_H

#include <bits/stdc++.h>
#include "Grammar.h"
#include "Rule.h"
using namespace std;

struct Item {
    int ruleIndex;
    int dot;
    string lookahead;

    bool operator<(Item const &o) const {
        return tie(ruleIndex, dot, lookahead) < tie(o.ruleIndex, o.dot, o.lookahead);
    }

    bool operator==(Item const &o) const {
        return ruleIndex == o.ruleIndex && dot == o.dot && lookahead == o.lookahead;
    }
};

class LR1Automaton {
public:
    Grammar *G;
    vector<set<Item>> states;
    map<pair<int,string>, int> GOTO;

    LR1Automaton(Grammar *grammar);

    set<Item> closure(set<Item> I);
    void buildLR1();
};

#endif
