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
    POWER,      // add power operator '**'
    MOD,        // add modulus operator '%'
    LPAREN,
    RPAREN,
    COMMA,      // optional, for separating function args
    IDENTIFIER,
    ASSIGN,
    BIT_AND,    // &
    BIT_OR,     // |
    BIT_XOR,    // ^
    BIT_NOT,    // ~
    LSHIFT,     // <<
    RSHIFT,      // >>
    END
};

struct Token {
    TokenType type;
    std::variant<int, double, std::string, std::monostate> value;

    Token(TokenType t);
    Token(TokenType t, int val);
    Token(TokenType t, double val);
    Token(TokenType t, const std::string& val); 
    std::string toString() const;
};

#endif // TOKEN_H
