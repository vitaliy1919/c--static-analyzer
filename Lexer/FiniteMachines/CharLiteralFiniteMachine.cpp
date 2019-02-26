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
        current_state_ = CharLiteralStates::StartState;
        public_state_ = State::Running;
    }

    switch (current_state_) {
        case CharLiteralStates::StartState:
            startState(symbol);
            break;
        case CharLiteralStates::QuoteState:
            quoteState(symbol);
            break;
        case CharLiteralStates::PrefixState:
            prefixState(symbol);
            break;
        case CharLiteralStates::PrefixRemainderState:
            prefixRemainderState(symbol);
            break;
        case CharLiteralStates::EscapeSymbolState:
            escapeSymbolState(symbol);
            break;
    }
    return public_state_;
}

void CharLiteralFiniteMachine::startState(char symbol) {
    if (tolower(symbol) == 'l' || symbol == 'U') {
        current_state_ = CharLiteralStates::PrefixState;
    } else if (symbol == 'u') {
        current_state_ = CharLiteralStates::PrefixRemainderState;
    } else if (symbol == '\'') {
        current_state_ = CharLiteralStates::QuoteState;
    } else
        public_state_ = State::Undefined;

}

void CharLiteralFiniteMachine::quoteState(char symbol) {
    if (symbol == '\\') {
        current_state_ = CharLiteralStates::EscapeSymbolState;
    } else if (symbol == '\'') {
        public_state_ = State::Ended;
    }
}

void CharLiteralFiniteMachine::prefixState(char symbol) {
    if (symbol == '\'')
        current_state_ = CharLiteralStates::QuoteState;
    else
        public_state_ = State::Undefined;
}

void CharLiteralFiniteMachine::prefixRemainderState(char symbol) {
    if (symbol == '8') {
        current_state_ = CharLiteralStates::PrefixState;
    } else if (symbol == '\'') {
        current_state_ = CharLiteralStates::QuoteState;
    } else
        public_state_ = State::Undefined;
}

void CharLiteralFiniteMachine::escapeSymbolState(char symbol) {
    current_state_ = CharLiteralStates::QuoteState;
}
