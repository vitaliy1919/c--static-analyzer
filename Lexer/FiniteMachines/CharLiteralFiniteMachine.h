//
// Created by vitdmit on 2/27/19.
//

#ifndef LEXER_CHARLITERALFINITESTATE_H
#define LEXER_CHARLITERALFINITESTATE_H


#include "FiniteStateMachine.h"

enum class CharLiteralStates {
    StartState,
    QuoteState,
    EscapeSymbolState,
    PrefixRemainderState,
    PrefixState
};

class CharLiteralFiniteMachine: public FiniteStateMachine {

private:
    CharLiteralStates current_state_;
protected:
    State handleInput(char symbol) override;

public:
    
    
    State processString(const string &str, int &i, int row) override;

    void startState(char symbol);

    void quoteState(char symbol);

    void prefixState(char symbol);

    void prefixRemainderState(char symbol);

    void escapeSymbolState(char symbol);
};


#endif //LEXER_CHARLITERALFINITESTATE_H
