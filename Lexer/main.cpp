// C++ implementation of search and insert 
// operations on Trie 
#include <bits/stdc++.h>
#include "FiniteMachines/CommentsFiniteMachine.h"
#include "FiniteMachines/StringLiteralFiniteMachine.h"
#include "FiniteMachines/NumbersFiniteMachine.h"
#include "FiniteMachines/OperatorsStateMachine.h"
#include "FiniteMachines/ReservedWordsFiniteMachine.h"
#include "Utils/trie.h"
#include "Utils/TokenRecognizer.h"
#include "Tokens/PreprocessorToken.h"
#include "Tokens/CommentToken.h"

using namespace std;
  


// Driver 
int main() {
    ifstream file("int.txt");
    ofstream tokens_file("tokens.txt");
    string line;
    string cur_string;
    int row_number = 1;
    if (!file.is_open()) {
        std::cout << "Can't open file\n";
        return 1;
    }
    FiniteStateMachine *machine = new NumbersFiniteMachine();
    row_number = 1;
    State state;
    std::shared_ptr<Token> token = nullptr;
    TokenRecognizer tokenRecognizer;
    int last_output_row = 1;
    while (getline(file, line)) {
        int i = 0;
        if (tokenRecognizer.isTokenProcessed())
            cout << std::setprecision(6) << row_number << ": ";
        while (i < line.size()) {
            if (tokenRecognizer.isTokenProcessed() && line[i] == ' ') {
                cout << line[i];
                i++;
            } else {
                int start = i;

                token = tokenRecognizer.recognizeToken(line, i, row_number);
                if (tokenRecognizer.isTokenRecognized()) {
                    if (!tokenRecognizer.isTokenProcessed())
                        continue;

                    if (token->type == TokenTypes::Comment) {
                        std::shared_ptr<CommentToken> comment_token = std::dynamic_pointer_cast<CommentToken>(token);
                        for (int j = 0; j < comment_token->lines.size(); j++) {
                            string line = comment_token->lines[j];
                            if (j != 0)
                                cout << std::setprecision(6) << ++last_output_row << ": ";
                            comment_token->printColor();
                            cout << line;
                            comment_token->resetColor();
                            if (j != comment_token->lines.size() - 1)
                                cout << "\n";

                        }
                        last_output_row = row_number;
//                        if (last_output_row != row_number + 1)
//                            cout << "Something went wrong\n";
                        continue;
                    }
                    if (tokenRecognizer.isTokenProcessed()) {
//                        cout << std::setprecision(6) << row_number <<": ";
                        token->printColored();
                        tokens_file << *token << '\n';

                    } else
                        continue;
//                    if (token->type == TokenTypes::Preprocessor) {
//                        std::shared_ptr<PreprocessorToken> preToken = std::dynamic_pointer_cast<PreprocessorToken>(
//                                token);
//                        cout << ' ';
//                        for (auto &arg: preToken->args)
//                            cout << arg << ' ';
//                    }
                } else if (token) {
                    cout << token->value;
                }
                   // cout << e.what() << endl;
            }
        }
        //cout<<"row: " << row_number << endl;
        if (tokenRecognizer.isTokenProcessed())
            cout << '\n';
        row_number++;
        if (tokenRecognizer.isTokenProcessed())
            last_output_row = row_number;
    }
    token = tokenRecognizer.inputEOF();
    if (token != nullptr) {
        
    }
//    while (getline(file, line)) {
//        for (int i = 0; i < line.size(); i++) {
//            state = machine->onInput(line[i]);
//            if (state == State::Undefined)
//                cout << line[i];
//            else
//                cout << ANSI_GREEN << line[i] << ANSI_RESET;
//            if (state == State::Ended) {
//                tokens_file << "(" << row_number<<", "<<i - machine->getCurrentString().size() + 1 <<"): "<<machine->getCurrentString() << endl;
//
//            }
//        }
//        state = machine->onInput('\n');
//        if (state == State::Ended) {
//            tokens_file << "(" << row_number<<", "<<line.size() - machine->getCurrentString().size() + 1 <<"): "<<machine->getCurrentString() << endl;
//
//        }
//        row_number++;
//        cout<<'\n';
//    }
    delete machine;
    tokens_file.close();
    file.close();
}
