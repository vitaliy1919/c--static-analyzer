//
// Created by vitdmit on 2/23/19.
//

#include "StringLiteralFiniteMachine.h"

State StringLiteralFiniteMachine::handleInput(char symbol) {
    if (public_state_ != State::Running) {
        is_raw_string_ = false;
        delimiter.clear();
        current_state_ = LiteralStates::StartState;
        public_state_ = State::Running;
    }
    if (!is_raw_string_) {
        switch (current_state_) {
            case LiteralStates::StartState:
                if (tolower(symbol) != 'r')
                    handlers_.startState(symbol);
                else {
                    is_raw_string_ = true;
                    cur_pos_++;
                    if (cur_pos_ >= line_.size())
                        public_state_ = State::Undefined;
                    else {
                        token_->value += symbol;
                        rState(line_[cur_pos_]);
                    }
                }
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
    } else {
        switch (raw_string_state_) {
            case RawStringState::DelimiterConsumeState:
                delimiterConsumeState(symbol);
                break;
            case RawStringState::LiteralConsumingState:
                literalConsumingState(symbol);
                break;
            case RawStringState::ClosingDelimiterState:
                closingDelimiterState(symbol);
                break;
            case RawStringState::CloseQuoteState:
                closeQuoteState(symbol);
                break;
        }
    }
    return public_state_;
}

State StringLiteralFiniteMachine::processString(const string &str, int &i, int row) {
    State state;
    line_ = str;
    token_ = std::make_shared<Token>();
    token_->row = row;
    token_->type = TokenTypes::StringLiteral;
    token_->t_start = i;
    cur_pos_ = i;
    do {
        if (cur_pos_ < str.length())
            state = handleInput(str[cur_pos_]);
        else if (cur_pos_ == str.length())
            state = handleInput('\n');
        else
            public_state_ = State::Undefined;
        if (state != State::Undefined && !is_raw_string_)
            token_->value += str[cur_pos_];
        cur_pos_++;
    } while (public_state_ != State::Undefined && public_state_ != State ::Ended);
//    if (public_state_ == State::Undefined)
//        i--;
    if (cur_pos_ >= str.length())
        token_->t_end = cur_pos_ - 1;
    else
        token_->t_end = cur_pos_;

    i = cur_pos_;
    if (state == State::Undefined)
        i--;
    return public_state_;
}

void StringLiteralFiniteMachine::rState(char symbol) {
    if (symbol == '\"') {
        token_->value += symbol;
        raw_string_state_ = RawStringState::DelimiterConsumeState;
    } else
        public_state_ = State::Undefined;
}

void StringLiteralFiniteMachine::delimiterConsumeState(char symbol) {
    token_->value += symbol;
    if (symbol == '(') {
        raw_string_state_ = RawStringState::LiteralConsumingState;
    } else {
        delimiter += symbol;
    }

}

void StringLiteralFiniteMachine::literalConsumingState(char symbol) {
    token_->value += symbol;
    if (symbol == ')') {
        raw_string_state_ = RawStringState::ClosingDelimiterState;
    }
}

void StringLiteralFiniteMachine::closingDelimiterState(char symbol) {
    bool isDelimiter = true;
    for (int i = 0; i < delimiter.size(); i++) {
        if (line_[cur_pos_ + i] != delimiter[i]) {
            isDelimiter = false;
            break;
        }
    }

    if (isDelimiter) {
        raw_string_state_ = RawStringState::CloseQuoteState;
        token_->value += delimiter;
        cur_pos_+=delimiter.size() - 1;
    } else
        raw_string_state_ = RawStringState::LiteralConsumingState;
}

void StringLiteralFiniteMachine::closeQuoteState(char symbol) {
    token_->value += symbol;
    if (symbol == '\"')
        public_state_ = State::Ended;
    else
        public_state_ = State::Undefined;
}


