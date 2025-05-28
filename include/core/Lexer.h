#ifndef LEXER_H
#define LEXER_H

#include "core/Token.h"
#include <string>
#include <vector>

class Lexer {
public:
    explicit Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t pos;

    char currentChar();
    void advance();
    void skipWhitespace();

    Token number();
    Token identifier();
};

#endif // LEXER_H
