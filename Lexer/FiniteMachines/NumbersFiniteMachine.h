//
// Created by vitdmit on 2/23/19.
//

#ifndef LEXER_NUMBERSFINITEMACHINE_H
#define LEXER_NUMBERSFINITEMACHINE_H


#include "FiniteStateMachine.h"

enum class NumberStates {
    StartState,
    ZeroSymbolState,
    FirstDigitState,
    DigitSequenceState,
    BinDigitSequenceState,
    OctDigitSequenceState,
    HexDigitSequenceState,
    LongRemainderState,
    DotState,
    ExponentState,
    HexDotState,
    ExponentDigitSequenceState,
    HexRemainderSequenceState,
    RemainderSequenceState,
};

class NumbersFiniteMachine: public FiniteStateMachine {

public:
    const std::string &getCurrentString() const override;

    State processString(const string &str, int &i, int row) override;

protected:
    bool token_omit_symbol_;
    State handleInput(char symbol) override;
    NumberStates current_state_ = NumberStates::StartState;
private:
    void startState(char symbol);
    void digitSequenceState(char symbol);
    void dotState(char symbol);
    void longRemainderState(char symbol);
    void exponentState(char symbol);
    void exponentDigitsState(char symbol);
    void remainderSequenceState(char symbol);
    void zeroSymbolState(char symbol);
    void binDigitSequenceState(char symbol);
    void octDigitSequenceState(char symbol);
    void hexDigitSequenceState(char symbol);
    void hexDotState(char symbol);
};


#endif //LEXER_NUMBERSFINITEMACHINE_H
