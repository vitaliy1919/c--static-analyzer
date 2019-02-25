//
// Created by vitdmit on 2/24/19.
//

#ifndef LEXER_OPERATORSFINITESTATEMACHINE_H
#define LEXER_OPERATORSFINITESTATEMACHINE_H


#include "TrieBasedFiniteMachine.h"

using std::string;

class OperatorsStateMachine: public TrieBasedFiniteMachine {
protected:
    void init() override {
        string binary_operators[] = {"+", "-", "*", "/", "%", "=", "&", "|", ">", "<", "&", "!", "^", ">>", "<<"};
        string double_operators[] = {"++", "--", "&&", "||", "::"};
        string unary_operators[] = {"(", ")", "~", "->", ".", "?", ":"};
        for (int i = 0; i < sizeof(binary_operators) / sizeof(string);i++) {
            trie_.insert(binary_operators[i]);
            trie_.insert(binary_operators[i] + "=");
        }
        for (int i = 0; i < sizeof(double_operators) / sizeof(string);i++) {
            trie_.insert(double_operators[i]);
        }
        for (int i = 0; i < sizeof(unary_operators) / sizeof(string);i++) {
            trie_.insert(unary_operators[i]);
        }
    }

    bool advance(char symbol) override {
        return true;
    }

    void preProcess() override {
        token_->type = TokenTypes::Operator;
    }

public:
    OperatorsStateMachine() {init();}
};


#endif //LEXER_OPERATORSFINITESTATEMACHINE_H
