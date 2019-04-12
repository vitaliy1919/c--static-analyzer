//
// Created by vitdmit on 2/27/19.
//

#include "LiteralStatesHandlers.h"
#include "string-utils.h"

void LiteralStatesHandlers::startState(char symbol) {
    if (tolower(symbol) == 'l' || symbol == 'U') {
        current_state_ = LiteralStates::PrefixState;
    } else if (symbol == 'u') {
        current_state_ = LiteralStates::PrefixRemainderState;
    } else if (symbol == symbol_) {
        current_state_ = LiteralStates::QuoteState;
    } else
        public_state_ = State::Undefined;

}

void LiteralStatesHandlers::quoteState(char symbol) {
    if (symbol == '\\') {
        current_state_ = LiteralStates::EscapeSymbolState;
    } else if (symbol == symbol_) {
        public_state_ = State::Ended;
    } else if (isCharLiteralTerminateSymbol(symbol)) {
        public_state_ = State ::Undefined;
    }
}

void LiteralStatesHandlers::prefixState(char symbol) {
    if (symbol == symbol_)
        current_state_ = LiteralStates::QuoteState;
    else
        public_state_ = State::Undefined;
}

void LiteralStatesHandlers::prefixRemainderState(char symbol) {
    if (symbol == '8') {
        current_state_ = LiteralStates::PrefixState;
    } else if (symbol == symbol_) {
        current_state_ = LiteralStates::QuoteState;
    } else
        public_state_ = State::Undefined;
}

void LiteralStatesHandlers::escapeSymbolState(char symbol) {
    if (isCharLiteralTerminateSymbol(symbol))
        public_state_ = State::Undefined;
    else
        current_state_ = LiteralStates::QuoteState;
}



LiteralStatesHandlers::LiteralStatesHandlers(char symbol_, State& public_state_, LiteralStates& current_state_) : symbol_(symbol_),
                                                                                                    public_state_(
                                                                                                            public_state_),
                                                                                                    current_state_(
                                                                                                            current_state_) {}
