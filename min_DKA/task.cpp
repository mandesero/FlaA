#include "api.hpp"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <set>
#include <algorithm>
#include <queue>

// #include "output.h"

using namespace std;


int to_state(vector<set<string>> &groups, const string &state) {
    for (int i = 0; i < groups.size(); i++) {
        if (groups[i].count(state)) {
            return i;
        }
    }
    return 0;
}


map<string, vector<string>> get_transition(DFA &d, vector<set<string>> &groups, set<string> &group) {
    map<string, vector<string>> transition;
    for (auto& state: group) {
        for (auto& chr: d.get_alphabet().to_string()) {
            int to_st = to_state(groups, d.get_trans(state, chr));
            transition[state].push_back(to_string(to_st));
        }
    }
    return transition;
 }


void dfs(DFA &d, set<string> &visited, const string &current) {
    visited.insert(current);
    for (auto& chr: d.get_alphabet()) {
        if (d.has_trans(current, chr)) {
            string t = d.get_trans(current, chr);
            if (!visited.count(t))
                dfs(d, visited, d.get_trans(current, chr));
        }
    }
}

void delete_dead_states(DFA &d) {
    set<string> dead;
    bool flag;
    for (auto& state: d.get_states()) {
        flag = true;
        for (auto& chr: d.get_alphabet()) {
            if (d.has_trans(state, chr)) {
                flag = flag && (state == d.get_trans(state, chr));
            }
        }
        if (flag && !d.is_final(state) && !d.is_initial(state)) {
            dead.insert(state);
        }
    }
    for (auto& state: dead) {
        d.delete_state(state);
    }
}


DFA dfa_minim(DFA &d) {

    set<string> visited;
    dfs(d, visited, d.get_initial_state());
    for (auto& state: d.get_states()) {
        if (!visited.count(state)) {
            d.delete_state(state);
        }
    }

    d.create_state("DEAD");
    for (auto& chr: d.get_alphabet().to_string()) {
        d.set_trans("DEAD", chr, "DEAD");
    }

    for (auto& state: d.get_states()) {
        for (auto& chr: d.get_alphabet().to_string()) {
            if (!d.has_trans(state, chr)) {
                d.set_trans(state, chr, "DEAD");
            }
        }
    }

    set<string> F;
    set<string> S;
    for (auto& state: d.get_states()) {
        if (d.is_final(state)) {
            F.insert(state);
        } else {
            S.insert(state);
        }
    }

    vector<set<string>> groups;

    if (F.size())
        groups.push_back(F);
    if (S.size())
        groups.push_back(S);
    
    bool changed = true;
    while (changed) {
        changed = false;
        vector<set<string>> new_groups;

        for (auto& group: groups) {
            if (group.size() == 1) {
                new_groups.push_back(group);
                continue;
            }
            
            auto transition = get_transition(d, groups, group);

            map<vector<string>, set<string>> tmp;
            for (auto& [k, v]: transition) {
                tmp[v].insert(k);
            }
            
            for (auto& [k, v]: tmp) {
                new_groups.push_back(v);
            }
        }
        if (new_groups.size() > groups.size()) {
            groups = move(new_groups);
            changed = true;
        }
    }

    DFA dfa(d.get_alphabet());

    for (int i = 0; i < groups.size(); i++) {
        if (!groups[i].count("DEAD")) {
            dfa.create_state(to_string(i));
            
            for (auto& s: groups[i]) {
                if (d.is_final(s)) {
                    dfa.make_final(to_string(i));
                    break;
                }
                if (d.is_initial(s)) {
                    dfa.set_initial(to_string(i));
                    break;
                }
            }
        }
    }

    auto alf = d.get_alphabet().to_string();

    for (int i = 0; i < groups.size(); i++) {
        auto transition = get_transition(d, groups, groups[i]);
        auto ways = transition[*groups[i].begin()];
        for (int j = 0; j < alf.size(); j++) {
            dfa.set_trans(to_string(i), alf[j], ways[j]);
        }
    }

    visited.clear();
    dfs(dfa, visited, dfa.get_initial_state());
    delete_dead_states(dfa);
    for (auto& state: dfa.get_states()) {
        if (!visited.count(state)) {
            dfa.delete_state(state);
        }
    }

    return dfa;

}
