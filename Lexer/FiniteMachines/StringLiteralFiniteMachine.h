//
// Created by vitdmit on 2/23/19.
//

#ifndef LEXER_STRINGLITERALFINITEMACHINE_H
#define LEXER_STRINGLITERALFINITEMACHINE_H


#include "FiniteStateMachine.h"
#include "../Utils/LiteralStatesHandlers.h"
#include "../Utils/trie.h"

enum class RawStringState {
    RState,
    DelimiterConsumeState,
    LiteralConsumingState,
    ClosingDelimiterState,
    CloseQuoteState
};


class StringLiteralFiniteMachine: public FiniteStateMachine {
private:
    LiteralStatesHandlers handlers_;
    LiteralStates current_state_ = LiteralStates::StartState;
    RawStringState raw_string_state_;
    bool is_raw_string_ = false;
    Trie delimiter_trie_;
    std::string delimiter, line_;
    int cur_pos_;
protected:
    virtual State handleInput(char symbol) override;
public:
    StringLiteralFiniteMachine():handlers_('\"', public_state_, current_state_) {

    }

    State processString(const string &str, int &i, int row) override;

    void rState(char symbol);

    void delimiterConsumeState(char symbol);

    void literalConsumingState(char symbol);

    void closingDelimiterState(char symbol);

    void closeQuoteState(char symbol);
};


#endif //LEXER_STRINGLITERALFINITEMACHINE_H
