//
// Created by vitdmit on 2/23/19.
//

#ifndef LEXER_STRING_UTILS_H
#define LEXER_STRING_UTILS_H


#include <cctype>
#include <string>

inline bool isDecDigit(char symb) {
    return symb >= '0' && symb <= '9';
}
inline bool isBinDigit(char symb) {
    return symb == '0' || symb == '1';
}
inline bool isHexDigit(char symb) {
    symb = tolower(symb);
    return (symb >= '0' && symb <= '9') || (symb >= 'a' && symb <= 'f');
}
inline bool isOctDigit(char symb) {
    return symb >= '0' && symb <='7';
}
inline bool isWhiteSpace(char symb) {
    return symb == ' ' || symb == '\n' || symb == '\t';
}
inline bool isPunctuationMark(char symb) {
    static char punctuation_marks[] = {',', ';', '{', '}', '\\'};
    for (char mark: punctuation_marks)
        if (symb == mark)
            return true;
    return false;
}
inline bool isTerminateSymbol(char symb) {
    return isWhiteSpace(symb) || symb == ';' || symb == ':' || symb == ',' || symb == '?' || symb == '[' || symb == ']'
        || (!isdigit(symb) && !isalpha(symb) && symb != '+' && symb != '-' && symb != '.');
}
inline bool isOperatorFirstSymbol(char symb) {
    static char operators[] = {'+', '-', '*', '/', '%', '=', '&', '|', '>', '<', '&', '!', '^', '(', ')', '[', ']', '~', '.', '?', ':'};
    for (char mark: operators)
        if (symb == mark)
            return true;
    return false;
}

inline bool isNumberTerminateSymbol(char symb) {
    return symb != '.' && (isWhiteSpace(symb) || isPunctuationMark(symb) || isOperatorFirstSymbol(symb));
}

inline bool isIdentifierTerminateSymbol(char symb) {
    return symb == '.' || isNumberTerminateSymbol(symb);
}
inline bool isCharLiteralTerminateSymbol(char symb) {
    return symb != ' ' && isWhiteSpace(symb);
}

inline bool isStringLiteralTerminateSymbol(char symb) {
    return isCharLiteralTerminateSymbol(symb);
}

inline std::string parseTokenBySpace(const std::string& str, int& i) {
    size_t len = str.size();
    while (i < len && str[i] == ' ') {
        i++;
    }
    std::string result;
    while (i < len && str[i] != ' ') {
        result += str[i];
        i++;
    }
    return result;
}

#endif