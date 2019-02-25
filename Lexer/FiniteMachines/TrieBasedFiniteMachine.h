//
// Created by vitdmit on 2/24/19.
//

#ifndef LEXER_TRIEBASEDFINITEMACHINE_H
#define LEXER_TRIEBASEDFINITEMACHINE_H

#include "FiniteStateMachine.h"
#include "../Utils/trie.h"

class TrieBasedFiniteMachine: public FiniteStateMachine {
private:
    bool findMaxSubstring(std::string str, int& i) {
        TrieNode *iter = trie_.getRoot();
        bool flag = false;
        int cur_max = -1;
        int start = i;
        do {
            auto &letters = iter->children;
            if (letters.in(str[i])) {
                iter = letters[str[i]];
                if (iter->isEndOfWord)
                    cur_max = i;
                i++;
            } else {
                flag = true;
                if (advance(str[i]))
                    i++;
            }
        } while (!flag);
        if (cur_max != -1)
            i = cur_max + 1;
        return cur_max != -1;
    }
protected:
    Trie trie_;
    virtual void preProcess() = 0;
    virtual void init() = 0;
    virtual bool advance(char symbol) = 0;
public:
    State processString(const string &str, int &i, int row) override;
};


#endif //LEXER_TRIEBASEDFINITEMACHINE_H
