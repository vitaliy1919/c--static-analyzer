//
// Created by vitdmit on 2/24/19.
//

#ifndef LEXER_RESERVEDWORDSFINITEMACHINE_H
#define LEXER_RESERVEDWORDSFINITEMACHINE_H


#include "FiniteStateMachine.h"

class ReservedWordsFiniteMachine: public FiniteStateMachine {

public:
    Token * getToken() override;

    State processString(std::string str, int &i, int row) override;

protected:
    State handleInput(char symbol) override;
};


#endif //LEXER_RESERVEDWORDSFINITEMACHINE_H
