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
private:
    bool tokenProcessed = true;
    bool lastLine = false;
    bool token_recognized = false;
public:
    bool isTokenProcessed() const {
        return tokenProcessed;
    }

    bool isLastLine() const {
        return lastLine;
    }

    void setLastLine(bool lastLine) {
        TokenRecognizer::lastLine = lastLine;
    }
    std::shared_ptr<Token> inputEOF() {
        if (!tokenProcessed) {
            return SingletonFiniteMachineFabric::createCommentsFiniteMachine()->getToken();
        } else return nullptr;
    }
    std::shared_ptr<Token> recognizeToken(std::string str, int& i, int row) {
        shared_ptr<FiniteStateMachine> machine;
        size_t len = str.size();
        bool is_comment = false;
        if (!tokenProcessed) {
            machine = SingletonFiniteMachineFabric::createCommentsFiniteMachine();
            is_comment = true;
        } else if (isPunctuationMark(str[i])) {
            token_recognized = true;
            std::shared_ptr<Token> token = std::make_shared<Token>(row, i, i + 1, string(1, str[i]));
            token->type = TokenTypes::PunctuationMark;
            i++;
            return token;
        } else if (str[i] == '/') {
            if (i < len - 1 && (str[i + 1] == '/' || str[i + 1] == '*')) {
                machine = SingletonFiniteMachineFabric::createCommentsFiniteMachine();
                is_comment = true;
            } else {
                machine = SingletonFiniteMachineFabric::createOperatorsFiniteMachine();
            }
        } else if (isdigit(str[i]))
            machine = SingletonFiniteMachineFabric::createNumbersFiniteMachine();
        else if (str[i] == '.') {
            if (i > 0 && (isalpha(str[i - 1]) || str[i - 1] == '_' || isDecDigit(str[i - 1])))
                machine = SingletonFiniteMachineFabric::createOperatorsFiniteMachine();
            else if (i < len - 1 && isdigit(str[i + 1]))
                machine = SingletonFiniteMachineFabric::createNumbersFiniteMachine();
            else
                machine = SingletonFiniteMachineFabric::createOperatorsFiniteMachine();
        } else if (str[i] == '\"' ||
                (i + 1 < len && isalpha(str[i]) && str[i + 1] == '\"') ||
                (i + 2 < len && isalpha(str[i]) && str[i+1] == '8' && str[i + 2] == '\"')) {
            machine = SingletonFiniteMachineFabric::createStringLiteralFiniteMachine();
        } else if (str[i] == '\'' ||
                   (i + 1 < len && isalpha(str[i]) && str[i + 1] == '\'') ||
                   (i + 2 < len && isalpha(str[i]) && str[i+1] == '8' && str[i + 2] == '\'')) {
            machine = SingletonFiniteMachineFabric::createCharLiteralFiniteMachine();
        } else if (str[i] == '#') {
            machine = SingletonFiniteMachineFabric::createPreprocessorFiniteMachine();
        } else if (isalpha(str[i]) || str[i] == '_') {
            machine = SingletonFiniteMachineFabric::createReservedWordsFiniteMachine();
            int start = i;
            State stateReserved = machine->processString(str, i, row);
            std::shared_ptr<Token> tokenReserved = nullptr;
            if (stateReserved == State::Ended) {
                tokenReserved = machine->getToken();
            }
            std::string string1 = R"(dudu)";
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

            if (tokenIndentifier == nullptr && tokenReserved == nullptr) {
                token_recognized = false;
                do {
                    machine->getToken()->value += str[i];
                    i++;
                } while (i < str.length() && !isNumberTerminateSymbol(str[i]));
//                if (i < str.length())
                return machine->getToken();
            }
            token_recognized = true;
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
        if (state == State::Ended) {
            tokenProcessed = true;
            token_recognized = true;
            return machine->getToken();
        } else if (state == State::Running) {
            tokenProcessed = false;
            token_recognized = false;
            return nullptr;
        } else {
            token_recognized = false;
            while (i < str.length() && !isNumberTerminateSymbol(str[i])) {
                machine->getToken()->value += str[i];
                i++;
            }
            return machine->getToken();
        }
    }

    bool isTokenRecognized() const {
        return token_recognized;
    }
};


#endif //LEXER_TOKENRECOGNIZER_H
