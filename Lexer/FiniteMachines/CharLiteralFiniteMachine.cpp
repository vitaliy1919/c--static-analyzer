//
// Created by vitdmit on 2/27/19.
//

#include "CharLiteralFiniteMachine.h"

State CharLiteralFiniteMachine::processString(const string &str, int &i, int row) {
    State state;
    token_ = std::make_shared<Token>();
    token_->row = row;
    token_->type = TokenTypes::CharLiteral;
    token_->t_start = i;
    do {
        if (i < str.length())
            state = handleInput(str[i]);
        else if (i == str.length())
            state = handleInput('\n');
        else
            public_state_ = State::Undefined;

        if (public_state_ != State::Undefined)
            token_->value += str[i];

        i++;
    } while (public_state_ != State::Undefined && public_state_ != State ::Ended);
//    if (public_state_ == State::Undefined)
//        i--;
    token_->t_end = i;
    return public_state_;
}

State CharLiteralFiniteMachine::handleInput(char symbol) {
    if (public_state_ != State::Running) {
        current_state_ = LiteralStates::StartState;
        public_state_ = State::Running;
    }

    switch (current_state_) {
        case LiteralStates::StartState:
            handlers_.startState(symbol);
            break;
        case LiteralStates::QuoteState:
            handlers_.quoteState(symbol);
            break;
        case LiteralStates::PrefixState:
            handlers_.prefixState(symbol);
            break;
        case LiteralStates::PrefixRemainderState:
            handlers_.prefixRemainderState(symbol);
            break;
        case LiteralStates::EscapeSymbolState:
            handlers_.escapeSymbolState(symbol);
            break;
    }
    return public_state_;
}

