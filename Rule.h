#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>
using namespace std;

struct Rule {
    string lhs;
    vector<string> rhs;
};

#endif