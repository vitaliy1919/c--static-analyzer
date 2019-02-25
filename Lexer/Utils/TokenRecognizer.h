//
// Created by vitdmit on 2/24/19.
//

#ifndef LEXER_TOKENRECOGNIZER_H
#define LEXER_TOKENRECOGNIZER_H

#include <utility>
#include "../Tokens/Token.h"
#include "../FiniteMachines/FiniteStateMachine.h"
#include "SingletonFiniteMachineFabric.h"
#include "string-utils.h"
#include <memory>
#include <stdexcept>
using std::pair;
using std::make_pair;
using std::shared_ptr;
class TokenRecognizer {
public:
    static std::shared_ptr<Token> recognizeToken(std::string str, int& i, int row) {
        shared_ptr<FiniteStateMachine> machine;
        if (isPunctuationMark(str[i])) {
            std::shared_ptr<Token> token = std::make_shared<Token>(row, i, i  + 1, string(1, str[i]));
            token->type = TokenTypes::PunctuationMark;
            i++;
            return token;
        } else if (str[i] == '/') {
            machine = SingletonFiniteMachineFabric::createOperatorsFiniteMachine();
        } else if (isdigit(str[i]))
            machine = SingletonFiniteMachineFabric::createNumbersFiniteMachine();
        else if (str[i] == '.') {
            if (isdigit(str[i+1]))
                machine = SingletonFiniteMachineFabric::createNumbersFiniteMachine();
            else
                machine = SingletonFiniteMachineFabric::createOperatorsFiniteMachine();
        } else if (str[i] == '\"') {
            machine = SingletonFiniteMachineFabric::createStringLiteralFiniteMachine();
        } else if (str[i] == '#') {
            machine = SingletonFiniteMachineFabric::createPreprocessorFiniteMachine();
        } else if (isalpha(str[i])) {
                machine = SingletonFiniteMachineFabric::createReservedWordsFiniteMachine();
                int start = i;
                State stateReserved = machine->processString(str, i, row);
                std::shared_ptr<Token> tokenReserved = nullptr;
                if (stateReserved == State::Ended) {
                    tokenReserved = machine->getToken();
                }
                int lengthIndetifier, lengthReserved;
                lengthReserved = i - start;
                i = start;
                machine = SingletonFiniteMachineFabric::createIndentifiersFiniteMachine();
                std::shared_ptr<Token> tokenIndentifier = nullptr;
                State stateIndentifier = machine->processString(str, i, row);
                lengthIndetifier = i - start;
                if (stateIndentifier == State::Ended) {
                    tokenIndentifier = machine->getToken();
                }

                if (tokenIndentifier == nullptr && tokenReserved == nullptr)
                    throw std::runtime_error("token not recognized: " + toString(*machine->getToken()));

                if (tokenReserved == nullptr) {
                    return tokenIndentifier;
                } else if (tokenIndentifier == nullptr) {
                    return tokenReserved;
                } else if (lengthIndetifier > lengthReserved) {
                    return tokenIndentifier;
                } else {
                    return tokenReserved;
                }
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
