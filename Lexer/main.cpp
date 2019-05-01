// C++ implementation of search and insert
// operations on Trie

#include <iomanip>
#include <locale>
#include <codecvt>
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

int a = 5&67;

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
//        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cvt;
//
//        // UTF-8 to UTF-32
//        std::u32string utf32 = cvt.from_bytes(line);
//        std::cout << "UTF-32 string size: " << utf32.size() << '\n';
//        std::cout << "converted() == " << cvt.converted() << '\n';
//        // UTF-32 to UTF-8
//        line = cvt.to_bytes(utf32);
//        std::cout << "new UTF-8 string size: " << line.size() << '\n';
//        std::cout << "converted() == " << cvt.converted() << '\n';
        //cout << utf32 <<endl;
        int i = 0;
        if (tokenRecognizer.isTokenProcessed())
            cout << std::setprecision(6) << row_number << ": ";
        while (i < line.size()) {
            if (tokenRecognizer.isTokenProcessed() && isWhiteSpace(line[i])) {
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
                    token->type = TokenTypes::Unrecognized;
                    cout << token->value;
                    if (i >= line.size())
                        token->value += '\n';
                    else
                        token->value += line[i];
                    tokens_file << *token << endl;
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
        std::shared_ptr<CommentToken> unrecognized_comment = std::dynamic_pointer_cast<CommentToken>(token);
        for (int i = 0; i < unrecognized_comment->lines.size(); i++) {
            string line = unrecognized_comment->lines[i];
            if (i != 0)
                cout << std::setprecision(6) << ++last_output_row << ": ";
//            unrecognized_comment->printColor();
            cout << line;
//            unrecognized_comment->resetColor();
                cout << "\n";
        }
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
