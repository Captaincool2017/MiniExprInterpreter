#include "Parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

const Token& Parser::currentToken() const {
    if (pos >= tokens.size()) throw std::runtime_error("Unexpected end of input");
    return tokens[pos];
}

void Parser::advance() {
    if (pos < tokens.size()) ++pos;
}

std::unique_ptr<Expr> Parser::parse() {
    auto result = expr();
    if (currentToken().type != TokenType::END)
        throw std::runtime_error("Unexpected token after expression");
    return result;
}

std::unique_ptr<Expr> Parser::expr() {
    auto left = term();
    while (currentToken().type == TokenType::PLUS || currentToken().type == TokenType::MINUS) {
        TokenType op = currentToken().type;
        advance();
        auto right = term();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<Expr> Parser::term() {
    auto left = factor();
    while (currentToken().type == TokenType::MUL || currentToken().type == TokenType::DIV) {
        TokenType op = currentToken().type;
        advance();
        auto right = factor();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<Expr> Parser::factor() {
    if (currentToken().type == TokenType::NUMBER) {
        // Check if value holds int or double
        double value = 0.0;

        if (std::holds_alternative<int>(currentToken().value)) {
            value = static_cast<double>(std::get<int>(currentToken().value));
        } else if (std::holds_alternative<double>(currentToken().value)) {
            value = std::get<double>(currentToken().value);
        } else {
            throw std::runtime_error("Invalid number token value");
        }

        advance();
        return std::make_unique<NumberNode>(value);
    } else if (currentToken().type == TokenType::LPAREN) {
        advance();
        auto node = expr();
        if (currentToken().type != TokenType::RPAREN)
            throw std::runtime_error("Expected ')'");
        advance();
        return node;
    } else {
        throw std::runtime_error("Expected number or '('");
    }
}
