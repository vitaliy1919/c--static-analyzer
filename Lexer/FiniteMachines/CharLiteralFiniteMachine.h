//
// Created by vitdmit on 2/27/19.
//

#ifndef LEXER_CHARLITERALFINITESTATE_H
#define LEXER_CHARLITERALFINITESTATE_H


#include "FiniteStateMachine.h"
#include "../Utils/LiteralStatesHandlers.h"


class CharLiteralFiniteMachine: public FiniteStateMachine {

private:
    LiteralStates current_state_ = LiteralStates::StartState;
    LiteralStatesHandlers handlers_;
protected:
    State handleInput(char symbol) override;

public:
    CharLiteralFiniteMachine(): handlers_('\'', public_state_, current_state_) {

    }

    State processString(const string &str, int &i, int row) override;
};


#endif //LEXER_CHARLITERALFINITESTATE_H
