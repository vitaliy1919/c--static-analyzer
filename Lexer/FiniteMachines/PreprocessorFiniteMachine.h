//
// Created by vitdmit on 2/25/19.
//

#ifndef LEXER_PREPROCESSORFINITEMACHINE_H
#define LEXER_PREPROCESSORFINITEMACHINE_H


#include "FiniteStateMachine.h"
#include "../Utils/trie.h"

class PreprocessorFiniteMachine: public FiniteStateMachine {
private:
    Trie preprocessorDirectives_;
    void trieInit();
public:
    PreprocessorFiniteMachine();

    State processString(const string &str, int &i, int row) override;

};


#endif //LEXER_PREPROCESSORFINITEMACHINE_H
