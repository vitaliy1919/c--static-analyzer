//
// Created by vitdmit on 2/24/19.
//

#ifndef LEXER_RESERVEDWORDSFINITEMACHINE_H
#define LEXER_RESERVEDWORDSFINITEMACHINE_H


#include "TrieBasedFiniteMachine.h"

class ReservedWordsFiniteMachine: public TrieBasedFiniteMachine {

protected:
    void init() override {
        std::string reserved_words[] = {

                "alignas",
                "alignof",
                "and",
                "and_eq",
                "asm",
                "atomic_cancel",
                "atomic_commit",
                "atomic_noexcept",
                "auto",
                "bitand",
                "bitor",
                "bool",
                "break",
                "case",
                "catch",
                "char",
                "char8_t",
                "char16_t",
                "char32_t",
                "class",
                "compl",
                "concept",
                "const",
                "consteval",
                "constexpr",
                "const_cast",
                "continue",
                "co_await",
                "co_return",
                "co_yield",
                "decltype",
                "default",
                "delete",
                "do",
                "double",
                "dynamic_cast",
                "else",
                "enum",
                "explicit",
                "export",
                "extern",
                "false",
                "float",
                "for",
                "friend",
                "goto",
                "if",
                "import",
                "inline",
                "int",
                "long",
                "module",
                "mutable",
                "namespace",
                "new",
                "noexcept",
                "not",
                "not_eq",
                "nullptr",
                "operator",
                "or",
                "or_eq",
                "private",
                "protected",
                "public",
                "reflexpr",
                "register",
                "reinterpret_cast",
                "requires",
                "return",
                "short",
                "signed",
                "sizeof",
                "static",
                "static_assert",
                "static_cast",
                "struct",
                "switch",
                "synchronized",
                "template",
                "this",
                "thread_local",
                "throw",
                "true",
                "try",
                "typedef",
                "typeid",
                "typename",
                "union",
                "unsigned",
                "using",
                "virtual",
                "void",
                "volatile",
                "wchar_t",
                "while",
                "xor",
                "xor_eq"
        };

        uint len = sizeof(reserved_words) / sizeof(std::string);
        for (int i = 0; i < len; i++) {
            trie_.insert(reserved_words[i]);
        }
    }

    bool advance(char symbol) override {
        return isalnum(symbol) || symbol == '_';
    }

    void preProcess() override {
        token_->type = TokenTypes::ReservedWord;
    }

public:
    ReservedWordsFiniteMachine() {
        init();
    }
};


#endif //LEXER_RESERVEDWORDSFINITEMACHINE_H
