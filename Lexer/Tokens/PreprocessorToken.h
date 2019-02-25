//
// Created by vitdmit on 2/25/19.
//

#ifndef LEXER_PREPROCESSORTOKEN_H
#define LEXER_PREPROCESSORTOKEN_H


#include <vector>
#include "Token.h"

class PreprocessorToken: public Token {
public:
    std::vector<std::string> args;
};


#endif //LEXER_PREPROCESSORTOKEN_H
