#include "LR1Automaton.h"

LR1Automaton::LR1Automaton(Grammar *grammar) : G(grammar) {}

set<Item> LR1Automaton::closure(set<Item> I) {
    bool changed = true;

    while (changed) {
        changed = false;
        set<Item> add;

        for (auto &it : I) {
            auto &r = G->rules[it.ruleIndex];

            if (it.dot >= r.rhs.size())
                continue;

            string B = r.rhs[it.dot];
            if (G->terminals.count(B)) continue;

            set<string> lookaheads;
            bool nullable = true;

            for (int k = it.dot + 1; k < r.rhs.size(); k++) {
                auto &sym = r.rhs[k];
                for (auto f : G->FIRST[sym])
                    lookaheads.insert(f);

                if (!G->FIRST[sym].count("ε")) {
                    nullable = false;
                    break;
                }
            }

            if (nullable)
                lookaheads.insert(it.lookahead);

            for (int j = 0; j < G->rules.size(); j++) {
                if (G->rules[j].lhs == B) {
                    for (auto a : lookaheads)
                        add.insert({j, 0, a});
                }
            }
        }

        for (auto &x : add)
            if (!I.count(x)) {
                I.insert(x);
                changed = true;
            }
    }

    return I;
}

void LR1Automaton::buildLR1() {
    set<Item> S = closure({{0, 0, "$"}});
    states.push_back(S);

    bool changed = true;

    while (changed) {
        changed = false;

        for (int i = 0; i < states.size(); i++) {
            map<string, set<Item>> transitions;

            for (auto &it : states[i]) {
                auto &r = G->rules[it.ruleIndex];
                if (it.dot < r.rhs.size()) {
                    string X = r.rhs[it.dot];
                    transitions[X].insert({it.ruleIndex, it.dot+1, it.lookahead});
                }
            }

            for (auto &[sym, items] : transitions) {
                set<Item> C = closure(items);

                int found = -1;
                for (int j = 0; j < states.size(); j++)
                    if (states[j] == C)
                        found = j;

                if (found == -1) {
                    states.push_back(C);
                    found = states.size() - 1;
                    changed = true;
                }

                GOTO[{i, sym}] = found;
            }
        }
    }
}
