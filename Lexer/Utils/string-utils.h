//
// Created by vitdmit on 2/23/19.
//

#ifndef LEXER_STRING_UTILS_H
#define LEXER_STRING_UTILS_H


#include <cctype>

bool isDecDigit(char symb) {
    return symb >= '0' && symb <= '9';
}
bool isBinDigit(char symb) {
    return symb == '0' || symb == '1';
}
bool isHexDigit(char symb) {
    symb = tolower(symb);
    return (symb >= '0' && symb <= '9') || (symb >= 'a' && symb <= 'f');
}
bool isOctDigit(char symb) {
    return symb >= '0' && symb <='7';
}
bool isWhiteSpace(char symb) {
    return symb == ' ' || symb == '\n' || symb == '\t';
}

bool isTerminateSymbol(char symb) {
    return isWhiteSpace(symb) || symb == ';' || symb == ':' || symb == ',' || symb == '?' || symb == '[' || symb == ']'
        || (!isdigit(symb) && !isalpha(symb) && symb != '+' && symb != '-' && symb != '.');
}
#endif //LEXER_STRING_UTILS_H
