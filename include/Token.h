#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <variant>

enum class TokenType {
    NUMBER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    END
};

struct Token {
    TokenType type;
    std::variant<int, double, std::monostate> value;

    Token(TokenType t);
    Token(TokenType t, int val);
    Token(TokenType t, double val);

    std::string toString() const;
};

#endif // TOKEN_H
