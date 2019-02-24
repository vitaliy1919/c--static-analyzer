//
// Created by vitdmit on 2/24/19.
//

#ifndef LEXER_SINGLETEONFINITEMACHINEFABRIC_H
#define LEXER_SINGLETEONFINITEMACHINEFABRIC_H


#include "../FiniteMachines/FiniteStateMachine.h"
#include "../FiniteMachines/NumbersFiniteMachine.h"
#include "../FiniteMachines/StringLiteralFiniteMachine.h"
#include "../FiniteMachines/OperatorsStateMachine.h"
#include "../FiniteMachines/CommentsFiniteMachine.h"
#include "../FiniteMachines/ReservedWordsFiniteMachine.h"
#include <memory>

using std::shared_ptr;
using std::make_shared;
class SingletonFiniteMachineFabric {
private:
    static shared_ptr<StringLiteralFiniteMachine> string_literal_finite_machine_;
    static shared_ptr<NumbersFiniteMachine> numbers_finite_machine_;
    static shared_ptr<OperatorsStateMachine> operators_state_machine_;
    static shared_ptr<CommentsFiniteMachine> comments_finite_machine_;
    static shared_ptr<ReservedWordsFiniteMachine> reserved_words_finite_machine_;

public:
    static shared_ptr<FiniteStateMachine> createStringLiteralFiniteMachine() {
        if (string_literal_finite_machine_ == nullptr)
            string_literal_finite_machine_ = make_shared<StringLiteralFiniteMachine>();
        return string_literal_finite_machine_;
    }
    static shared_ptr<FiniteStateMachine> createReservedWordsFiniteMachine() {
        if (reserved_words_finite_machine_ == nullptr)
            reserved_words_finite_machine_ = make_shared<ReservedWordsFiniteMachine>();
        return reserved_words_finite_machine_;
    }

    static shared_ptr<FiniteStateMachine> createOperatorsFiniteMachine() {
        if (operators_state_machine_ == nullptr)
            operators_state_machine_ = make_shared<OperatorsStateMachine>();
        return operators_state_machine_;
    }

    static shared_ptr<FiniteStateMachine> createNumbersFiniteMachine() {
        if (numbers_finite_machine_ == nullptr)
            numbers_finite_machine_ = make_shared<NumbersFiniteMachine>();
        return numbers_finite_machine_;
    }

    static shared_ptr<FiniteStateMachine> createCommentsFiniteMachine() {
        if (comments_finite_machine_ == nullptr)
            comments_finite_machine_ = make_shared<CommentsFiniteMachine>();
        return comments_finite_machine_;
    }
};
shared_ptr<StringLiteralFiniteMachine> SingletonFiniteMachineFabric::string_literal_finite_machine_;
shared_ptr<NumbersFiniteMachine> SingletonFiniteMachineFabric::numbers_finite_machine_;
shared_ptr<OperatorsStateMachine> SingletonFiniteMachineFabric::operators_state_machine_;
shared_ptr<CommentsFiniteMachine> SingletonFiniteMachineFabric::comments_finite_machine_;
shared_ptr<ReservedWordsFiniteMachine> SingletonFiniteMachineFabric::reserved_words_finite_machine_;


#endif //LEXER_SINGLETEONFINITEMACHINEFABRIC_H