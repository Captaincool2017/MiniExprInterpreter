#ifndef PARSER_H
#define PARSER_H

#include "core/Token.h"
#include "core/AST.h"
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

    std::unique_ptr<Expr> assignment();   // parse assignment expressions
    std::unique_ptr<Expr> expr();         // expr → term ((+|-) term)*
    std::unique_ptr<Expr> term();         // term → factor ((*|/) factor)*
    std::unique_ptr<Expr> power();        // new
    std::unique_ptr<Expr> factor();       // factor → NUMBER | IDENTIFIER | (expr) | unary_op factor
    std::unique_ptr<Expr> bitwise_or();
    std::unique_ptr<Expr> bitwise_xor();
    std::unique_ptr<Expr> bitwise_and();
    std::unique_ptr<Expr> shift();

};

#endif // PARSER_H
