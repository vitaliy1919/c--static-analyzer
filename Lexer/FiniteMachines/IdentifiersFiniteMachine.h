//
// Created by i503709 on 2/25/19.
//

#ifndef LEXER_IDENTIFIERSFINITEMACHINE_H
#define LEXER_IDENTIFIERSFINITEMACHINE_H


#include "FiniteStateMachine.h"

enum class IndentifierState {
    StartState,
    ConstumingState
};


class IdentifiersFiniteMachine: public FiniteStateMachine {
public:
    State processString(const string &str, int &i, int row) override;
protected:
    State handleInput(char symbol) override;

private:
    IndentifierState current_state_;

    void startState(char symbol);

    void consumingState(char symbol);
};


#endif //LEXER_IDENTIFIERSFINITEMACHINE_H
