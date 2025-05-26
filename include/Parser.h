#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "AST.h"
#include <vector>
#include <memory>

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    std::unique_ptr<Expr> parse();

private:
    std::vector<Token> tokens;
    size_t pos;

    const Token& currentToken() const;
    void advance();

    std::unique_ptr<Expr> expr();    // expr → term ((+|-) term)*
    std::unique_ptr<Expr> term();    // term → factor ((*|/) factor)*
    std::unique_ptr<Expr> factor();  // factor → NUMBER | (expr)
};

#endif // PARSER_H
