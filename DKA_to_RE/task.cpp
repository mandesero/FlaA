#include "api.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>   
#include <set>

using namespace std;


string conc_set(set<string> s) {
    string ans = "(";
    for (auto i = s.begin(); i != s.end(); i++) {
        if (i == s.begin()) {
            ans += *i;
        } else {
            ans += "|" + *i;
        }
    }
    ans += ")";
    return ans;
}

std::string dfa2re(DFA &d) {

    auto alph = d.get_alphabet();
    alph.insert('&');
    
    DFA new_d(alph);
    new_d.create_state("START");
    new_d.create_state("END");

    new_d.set_initial("START");
    new_d.make_final("END");
    for (auto& state: d.get_states()) {
        new_d.create_state(state);
    }

    new_d.set_trans("START", '&', d.get_initial_state());

    for (auto& state: d.get_states()) {
        for (auto& chr: d.get_alphabet()) {
            if (d.has_trans(state, chr)) {
                new_d.set_trans(state, chr, d.get_trans(state, chr));
            }
        }
        if (d.is_final(state)) {
            new_d.set_trans(state, '&', "END");
        }
    }

    map<string, map<string, set<string>>> df;
    map<string, set<string>> in_s;
    map<string, set<string>> out_s;
    for (auto& state: new_d.get_states()) {
        for (auto chr: new_d.get_alphabet().to_string()) {
            if (new_d.has_trans(state, chr)) {
                auto new_state = new_d.get_trans(state, chr);
                in_s[new_state].insert(state);
                out_s[state].insert(new_state);
                df[state][new_state].insert(string(1, chr));
            }
        }
    }

    string res;
    auto states = new_d.get_states();
    for (auto state: states) {
        if (new_d.is_initial(state) || new_d.is_final(state))
            continue;

        auto in_states = in_s[state];
        auto out_states = out_s[state];

        for (auto& in: in_states) {
            for (auto& out: out_states) {
                res = "";
                if (df.count(state) && df[state].count(state) && df[state][state].size()) {
                    res = conc_set(df[in][state]) + "(" + conc_set(df[state][state]) + ")*" + conc_set(df[state][out]);
                } else {
                    res = conc_set(df[in][state]) + conc_set(df[state][out]);
                }
                if (res.size()) {
                    df[in][out].insert(res);
                    out_s[in].insert(out);
                    in_s[out].insert(in);
                }
            }
        }
    }

    res = conc_set(df["START"]["END"]);

    while (res.find("&") != std::string::npos) {
        res.replace(res.find("&"), 1, "");
    }
    return res;
}
