#include "Grammar.h"

Grammar::Grammar() {}

bool Grammar::isTerminal(const string &s) const {
    return !nonterminals.count(s);
}

void Grammar::computeFIRST() {
    bool changed = true;

    for (auto &nt : nonterminals) FIRST[nt];
    for (auto &t : terminals) FIRST[t].insert(t);
    FIRST["ε"].insert("ε");

    while (changed) {
        changed = false;
        for (auto &r : rules) {
            auto &A = r.lhs;

            for (int i = 0; i < r.rhs.size(); i++) {
                auto &X = r.rhs[i];

                for (auto f : FIRST[X]) {
                    if (f != "ε" && !FIRST[A].count(f)) {
                        FIRST[A].insert(f);
                        changed = true;
                    }
                }

                if (!FIRST[X].count("ε"))
                    break;

                if (i == r.rhs.size() - 1) {
                    if (!FIRST[A].count("ε")) {
                        FIRST[A].insert("ε");
                        changed = true;
                    }
                }
            }
        }
    }
}

void Grammar::computeFOLLOW() {
    FOLLOW[startSymbol].insert("$");
    bool changed = true;

    while (changed) {
        changed = false;

        for (auto &r : rules) {
            auto &A = r.lhs;

            for (int i = 0; i < r.rhs.size(); i++) {
                auto &B = r.rhs[i];

                if (nonterminals.count(B)) {
                    bool allNullable = true;

                    for (int j = i + 1; j < r.rhs.size(); j++) {
                        auto &C = r.rhs[j];

                        for (auto f : FIRST[C]) {
                            if (f != "ε" && !FOLLOW[B].count(f)) {
                                FOLLOW[B].insert(f);
                                changed = true;
                            }
                        }

                        if (!FIRST[C].count("ε")) {
                            allNullable = false;
                            break;
                        }
                    }

                    if (allNullable) {
                        for (auto f : FOLLOW[A]) {
                            if (!FOLLOW[B].count(f)) {
                                FOLLOW[B].insert(f);
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    }
}