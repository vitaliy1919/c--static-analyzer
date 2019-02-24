//
// Created by vitdmit on 2/24/19.
//

#ifndef LEXER_TRIEBASEDFINITEMACHINE_H
#define LEXER_TRIEBASEDFINITEMACHINE_H

#include "FiniteStateMachine.h"
#include "../Utils/trie.h"

class TrieBasedFiniteMachine: public FiniteStateMachine {
protected:
    Trie trie_;
    virtual void preProcess() = 0;
    virtual void init() = 0;
public:
    State processString(std::string str, int &i, int row) override;
};


#endif //LEXER_TRIEBASEDFINITEMACHINE_H
