#include "api.hpp"
#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <set>
#include <map>


class Tree {
public: 
    Tree(std::string value = "", bool nl = false): value(value),
    nullable(nl) {}
    Tree * left = nullptr;
    Tree * right = nullptr;
    bool nullable;
    std::set < int > firstpos;
    std::set < int > lastpos;

    std::string get() const;
    void set(std::string value);

private:
    std::string value;
};

std::string Tree::get() const {
    return value;
}

void Tree::set(std::string _value) {
    value = _value;
}


int count = 1;

std::string insertEps(const std::string & s) {
    std::string new_s;
    int size = s.size();
    for (int i = 0; i < size; ++i) {
        if (s[i] == '|' && i == 0) {
            new_s.push_back('~');
        }
        new_s.push_back(s[i]);
        if (i + 1 < size && ((s[i] == '|' && s[i + 1] == '|') ||
                (s[i] == '|' && s[i + 1] == ')') ||
                (s[i] == '(' && s[i + 1] == '|'))) {
            new_s.push_back('~');
        }
    }
    if (size > 0 && s[size - 1] == '|')
        new_s.push_back('~');
    return new_s;
}

void first_last(Tree * tree) {
    if (tree == nullptr)
        return;
    if (tree -> left != nullptr)
        first_last(tree -> left);
    if (tree -> right != nullptr)
        first_last(tree -> right);

    if (tree -> get() == "|") {
        tree -> nullable = tree -> right -> nullable || tree -> left -> nullable;
        tree -> firstpos = tree -> right -> firstpos;
        tree -> firstpos.insert(tree -> left -> firstpos.begin(), tree -> left -> firstpos.end());
        tree -> lastpos = tree -> right -> lastpos;
        tree -> lastpos.insert(tree -> left -> lastpos.begin(), tree -> left -> lastpos.end());
    } else if (tree -> get() == ".") {
        tree -> nullable = tree -> right -> nullable && tree -> left -> nullable;
        tree -> firstpos = tree -> left -> firstpos;
        if (tree -> left -> nullable)
            tree -> firstpos.insert(tree -> right -> firstpos.begin(), tree -> right -> firstpos.end());
        tree -> lastpos = tree -> right -> lastpos;
        if (tree -> right -> nullable)
            tree -> lastpos.insert(tree -> left -> lastpos.begin(), tree -> left -> lastpos.end());
    } else if (tree -> get() == "*") {
        tree -> nullable = true;
        if (!tree -> right) {
            tree -> firstpos = tree -> left -> firstpos;
            tree -> lastpos = tree -> left -> lastpos;
        } else {
            tree -> firstpos = tree -> right -> firstpos;
            tree -> lastpos = tree -> right -> lastpos;
        }
    }
}

void follow(Tree * tree, std::map < int, std::set < int >> & table) {
    if (!tree || (tree -> left == nullptr && tree -> right == nullptr))
        return;

    follow(tree -> right, table);
    follow(tree -> left, table);

    if (tree -> get() == ".") {
        auto & left_lastpos = tree -> left -> lastpos;
        auto & right_firstpos = tree -> right -> firstpos;

        for (auto el: left_lastpos) {
            for (auto el1: right_firstpos)
                table[el].insert(el1);
        }
    } else if (tree -> get() == "*") {
        auto & left_lastpos = tree -> left -> lastpos;
        auto & left_firstpos = tree -> left -> firstpos;
        auto & right_lastpos = tree -> right -> lastpos;
        auto & right_firstpos = tree -> right -> firstpos;

        if (!tree -> right)
            for (auto el: left_lastpos) {
                for (auto el1: left_firstpos)
                    table[el].insert(el1);
            }
        else
            for (auto el: right_lastpos) {
                for (auto el1: right_firstpos)
                    table[el].insert(el1);
            }
    }
}

std::string postfix(const std::string & s,
    const std::map < int, char > & num_char) {
    std::string new_s;
    std::stack < char > st;
    bool is_prev_char_multiplier = false;
    int n = 1;

    for (auto c: s) {
        if (c == '*') {
            while (!st.empty() && st.top() == '*') {
                new_s += st.top();
                st.pop();
            }
            st.push(c);
            is_prev_char_multiplier = true;
        } else if (c == '|') {
            while (!st.empty() && (st.top() == '|' || st.top() == '*' || st.top() == '.')){
                new_s += st.top();
                st.pop();
            }
            st.push(c);
            is_prev_char_multiplier = false;
        } else if (c == '(') {
            if (is_prev_char_multiplier) {
                while (!st.empty() && (st.top() == '.' || st.top() == '*')) {
                    new_s += st.top();
                    st.pop();
                }
                st.push('.');
            }
            st.push(c);
            is_prev_char_multiplier = false;
        } else if (c == ')') {
            while (st.top() != '(') {
                new_s += st.top();
                st.pop();
            }
            st.pop();
            is_prev_char_multiplier = true;
        } else {
            if (is_prev_char_multiplier) {
                while (!st.empty() && (st.top() == '.' || st.top() == '*')) {
                    new_s += st.top();
                    st.pop();
                }
                st.push('.');
            }
            new_s += c;
            is_prev_char_multiplier = true;
        }
    }

    while (!st.empty()) {
        new_s += st.top();
        st.pop();
    }

    return new_s;
}

Tree * parse(std::string & s) {
    std::stack < Tree * > st;

    Tree * root = new Tree(s.substr(s.size() - 1, 1));
    Tree * tmp = root;
    st.push(root);

    for (int i = (int) s.size() - 2; i >= 0; i--) {

        if (s[i] == '|' || s[i] == '.') {
            if (!tmp -> right) {
                tmp -> right = new Tree(std::string(1, s[i]));
                tmp = tmp -> right;
            } else {
                tmp -> left = new Tree(std::string(1, s[i]));
                tmp = tmp -> left;
            }
            st.push(tmp);

        } else if (s[i] == '*') {
            if (!tmp -> right) {
                tmp -> right = new Tree(std::string(1, s[i]));
                tmp = tmp -> right;
            } else {
                tmp -> left = new Tree(std::string(1, s[i]));
                tmp = tmp -> left;
            }
        } else {
            if (!tmp -> right) {
                bool b = std::string(1, s[i]) == "~";
                tmp -> right = new Tree(std::string(1, s[i]), b);
                if (!b) {
                    tmp -> right -> firstpos.insert(count);
                    tmp -> right -> lastpos.insert(count);
                    count--;
                }
            } else {
                bool b = std::string(1, s[i]) == "~";
                tmp -> left = new Tree(std::string(1, s[i]), std::string(1, s[i]) == "~");
                if (!b) {
                    tmp -> left -> firstpos.insert(count);
                    tmp -> left -> lastpos.insert(count);
                    count--;
                }
            }

            if (st.top() != root) {
                tmp = st.top();
                st.pop();
            } else
                tmp = st.top();
        }
    }

    st.pop();
    return root;
}

void makeDFA(DFA & res, Alphabet & alphabet, Tree *tree, std::map < int, std::set < int >> & followpos, std::map < int, char > & num_char, int final_pos) {

    int state_num = 0;
    std::map < std::set < int > , int > state_to_int;

    state_to_int[tree -> firstpos] = state_num++;

    res.create_state(std::to_string(state_to_int[tree -> firstpos]));
    if (tree -> firstpos.find(final_pos) != tree -> firstpos.end())
        res.make_final("0");
    res.set_initial(std::to_string(state_to_int[tree -> firstpos]));

    std::queue < std::set < int >> state_queue;
    state_queue.push(tree -> firstpos);

    while (!state_queue.empty()) {
        auto cur_state = state_queue.front();
        int cur_int = state_to_int[cur_state];
        state_queue.pop();

        std::set < char > symbs;
        for (auto num: cur_state)
            if (num != final_pos)
                symbs.insert(num_char[num]);

        for (auto let: symbs) {
            std::set < int > new_state;
            for (auto num: cur_state)
                if (num_char[num] == let)
                    for (auto el: followpos[num])
                        new_state.insert(el);

            if (state_to_int.find(new_state) == state_to_int.end()) {
                state_to_int[new_state] = state_num++;
                res.create_state(std::to_string(state_num - 1));
                state_queue.push(new_state);
                if (new_state.find(final_pos) != new_state.end())
                    res.make_final(std::to_string(state_num - 1));
            }
            res.set_trans(std::to_string(cur_int),
                let, std::to_string(state_to_int[new_state]));
        }
    }
}

DFA re2dfa(const std::string & s) {

    if (s.empty()) {
        std::set < char > st;
        DFA res = DFA(Alphabet("$"));
        res.create_state("0");
        res.set_initial("0");
        res.make_final("0");
        return res;
    }

    Alphabet alphabet(s);
    DFA res = DFA(alphabet);
    std::map < int, char > num_char;
    std::string ns = insertEps(s);

    for (char c: ns)
        if (alphabet.has_char(c))
            num_char[count++] = c;

    int final_pos = count;

    std::string postf = postfix(ns, num_char) + "#.";

    Tree * tree = parse(postf);

    first_last(tree);

    std::map < int, std::set < int >> followpos;
    follow(tree, followpos);

    makeDFA(res, alphabet, tree, followpos, num_char, final_pos);
    return res;
}