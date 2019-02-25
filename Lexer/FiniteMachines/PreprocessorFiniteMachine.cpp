//
// Created by vitdmit on 2/25/19.
//

#include "PreprocessorFiniteMachine.h"
#include "../Tokens/PreprocessorToken.h"
#include "../Utils/string-utils.h"
State PreprocessorFiniteMachine::processString(const string &str, int &i, int row) {
    if (str[i] != '#')
        return State::Undefined;
    i++;
    auto preprocessorToken = std::make_shared<PreprocessorToken>();
    token_ = preprocessorToken;
    preprocessorToken->type = TokenTypes::Preprocessor;
    preprocessorToken->row = row;
    preprocessorToken->t_start = i;
    size_t len = str.size();
    std::string directive = parseTokenBySpace(str, i);
    preprocessorToken->value = '#' + directive;
    if (preprocessorDirectives_.find(directive)) {
        while (i < len) {
            directive = parseTokenBySpace(str, i);
        }
        preprocessorToken->args.push_back(directive);
        preprocessorToken->t_end = i;
        token_ = preprocessorToken;
    } else {
        return State::Undefined;
    }
    return State::Ended;
}

void PreprocessorFiniteMachine::trieInit() {
    std::string directives[] = {
            "define", "undef", "include", "if", "ifdef", "ifndef", "else", "elif", "endif", "line", "error", "pragma"
    };
    for (auto directive: directives)
        preprocessorDirectives_.insert(directive);
}

PreprocessorFiniteMachine::PreprocessorFiniteMachine() {
    trieInit();
}
