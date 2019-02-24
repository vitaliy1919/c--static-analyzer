//
// Created by vitdmit on 2/24/19.
//

#ifndef LEXER_OPERATORSFINITESTATEMACHINE_H
#define LEXER_OPERATORSFINITESTATEMACHINE_H


#include "FiniteStateMachine.h"
#include "../Utils/trie.h"

using std::string;

class OperatorsStateMachine: public FiniteStateMachine {
public:
    Token getToken() override;
    OperatorsStateMachine();
    State processString(std::string str, int &i, int row) override;

protected:
    State handleInput(char symbol) override;

private:
    Trie operatorsTrie_;
};


#endif //LEXER_OPERATORSFINITESTATEMACHINE_H
