//
// Created by vitdmit on 2/24/19.
//

#include "TrieBasedFiniteMachine.h"

State TrieBasedFiniteMachine::processString(const string &str, int &i, int row) {
    token_ = std::make_shared<Token>();
    preProcess();
    token_->row = row;
    token_->t_start = i;
    bool state = findMaxSubstring(str, i);
    if (state) {
        token_->t_end = i;
        token_->value = str.substr(token_->t_start, token_->t_end - token_->t_start);
        return State::Ended;
    } else
        return State::Undefined;
}
