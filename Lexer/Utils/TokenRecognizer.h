//
// Created by vitdmit on 2/24/19.
//

#ifndef LEXER_TOKENRECOGNIZER_H
#define LEXER_TOKENRECOGNIZER_H

#include <utility>
#include "../Tokens/Token.h"
#include "../FiniteMachines/FiniteStateMachine.h"
#include "SingletonFiniteMachineFabric.h"
#include <memory>
#include <stdexcept>
using std::pair;
using std::make_pair;
using std::shared_ptr;
class TokenRecognizer {
public:
    static Token* recognizeToken(std::string str, int& i, int row) {
        shared_ptr<FiniteStateMachine> machine;

        if (str[i] == '/') {
            if (str[i + 1] == '/' || str[i + 1] == '*') {
                i++;
                return new Token();
            }
            else {
                machine = SingletonFiniteMachineFabric::createOperatorsFiniteMachine();
            }
        } else if (isdigit(str[i]))
            machine = SingletonFiniteMachineFabric::createNumbersFiniteMachine();
        else if (str[i] == '.') {
            if (isdigit(str[i+1]))
                machine = SingletonFiniteMachineFabric::createNumbersFiniteMachine();
            else
                machine = SingletonFiniteMachineFabric::createOperatorsFiniteMachine();
        } else if (isalpha(str[i])) {
            machine = SingletonFiniteMachineFabric::createReservedWordsFiniteMachine();
//            State state = machine->processString(str, i, row);
//            Token * tokenReserved = nullptr;
//            if (state == State::Ended) {
//                tokenReserved = machine.getToken();
//            }
//            Token *token
        } else {
            machine = SingletonFiniteMachineFabric::createOperatorsFiniteMachine();
//            i++;
//            std::string err = "Token not recognized: ";
//            throw std::runtime_error(err + str[i]);
        }

        State state = machine->processString(str, i, row);
        if (state == State::Ended)
            return machine->getToken();
        throw std::runtime_error("token not recognized: "+toString(*machine->getToken()));
    }
};


#endif //LEXER_TOKENRECOGNIZER_H
