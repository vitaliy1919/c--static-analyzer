//
// Created by vitdmit on 2/27/19.
//

#ifndef LEXER_LITERALSTATES_H
#define LEXER_LITERALSTATES_H

#include "../FiniteMachines/FiniteStateMachine.h"

enum class LiteralStates {
    StartState,
    QuoteState,
    EscapeSymbolState,
    PrefixRemainderState,
    PrefixState
};
class LiteralStatesHandlers {
private:
    char symbol_;
    State &public_state_;
    LiteralStates &current_state_;
public:
    void startState(char symbol);

    void quoteState(char symbol);

    void prefixState(char symbol);

    void prefixRemainderState(char symbol);

    void escapeSymbolState(char symbol);

    LiteralStatesHandlers(char symbol_, State& public_state_, LiteralStates& current_state_);
};


#endif //LEXER_LITERALSTATES_H
