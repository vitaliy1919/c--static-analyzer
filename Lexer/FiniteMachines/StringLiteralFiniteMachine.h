//
// Created by vitdmit on 2/23/19.
//

#ifndef LEXER_STRINGLITERALFINITEMACHINE_H
#define LEXER_STRINGLITERALFINITEMACHINE_H


#include "FiniteStateMachine.h"

class StringLiteralFiniteMachine: public FiniteStateMachine {
private:
    static const int START = 0;
    static const int CONSUMING_STRING = 1;
    static const int SPECIAL_SYMBOL = 2;
protected:
    virtual State handleInput(char symb) override;

    void startState(char symb);

    void consumingStringState(char symb);
    State processString(std::string str, int &i, int row) override;

    void consumingSpecialSymbolState(char symb);
};


#endif //LEXER_STRINGLITERALFINITEMACHINE_H
