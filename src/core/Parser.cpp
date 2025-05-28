#include "core/Parser.h"
#include <stdexcept>
#include <variant>
#include <string>

// Constructor unchanged
Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

const Token& Parser::currentToken() const {
    if (pos >= tokens.size()) throw std::runtime_error("Unexpected end of input");
    return tokens[pos];
}

void Parser::advance() {
    if (pos < tokens.size()) ++pos;
}

// Entry point: parse assignment or expression, expect end of input
std::unique_ptr<Expr> Parser::parse() {
    auto result = assignment();  // Parse assignment first
    if (currentToken().type != TokenType::END)
        throw std::runtime_error("Unexpected token after expression");
    return result;
}

// assignment → IDENTIFIER '=' assignment | expr
std::unique_ptr<Expr> Parser::assignment() {
    if (currentToken().type == TokenType::IDENTIFIER) {
        // Lookahead for '=' token
        if ((pos + 1) < tokens.size() && tokens[pos + 1].type == TokenType::ASSIGN) {
            std::string varName = std::get<std::string>(currentToken().value);
            advance();  // consume identifier
            advance();  // consume '='
            auto right = assignment();  // right recursive for chained assignments
            return std::make_unique<AssignmentNode>(varName, std::move(right));
        }
    }
    // No assignment detected, parse normal expression
    return expr();
}

// expr → term ((+|-) term)*
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

// term → bitwise_or ((*|/|%) bitwise_or)*
std::unique_ptr<Expr> Parser::term() {
    auto left = bitwise_or();
    while (currentToken().type == TokenType::MUL || currentToken().type == TokenType::DIV || currentToken().type == TokenType::MOD) {
        TokenType op = currentToken().type;
        advance();
        auto right = bitwise_or();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

// bitwise_or → bitwise_xor (| bitwise_xor)*
std::unique_ptr<Expr> Parser::bitwise_or() {
    auto left = bitwise_xor();
    while (currentToken().type == TokenType::BIT_OR) {
        TokenType op = currentToken().type;
        advance();
        auto right = bitwise_xor();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

// bitwise_xor → bitwise_and (^ bitwise_and)*
std::unique_ptr<Expr> Parser::bitwise_xor() {
    auto left = bitwise_and();
    while (currentToken().type == TokenType::BIT_XOR) {
        TokenType op = currentToken().type;
        advance();
        auto right = bitwise_and();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

// bitwise_and → shift (& shift)*
std::unique_ptr<Expr> Parser::bitwise_and() {
    auto left = shift();
    while (currentToken().type == TokenType::BIT_AND) {
        TokenType op = currentToken().type;
        advance();
        auto right = shift();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

// shift → power ((<<|>>) power)*
std::unique_ptr<Expr> Parser::shift() {
    auto left = power();   // <-- FIX: previously was factor(), now power()
    while (currentToken().type == TokenType::LSHIFT || currentToken().type == TokenType::RSHIFT) {
        TokenType op = currentToken().type;
        advance();
        auto right = power();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

// power → factor (** power)?
std::unique_ptr<Expr> Parser::power() {
    auto left = factor();
    if (currentToken().type == TokenType::POWER) {
        TokenType op = currentToken().type;
        advance();
        auto right = power();  // right recursion for right-associativity
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

// factor → NUMBER | IDENTIFIER | (expr) | unary_op factor
// unary_op → + | - | ~
std::unique_ptr<Expr> Parser::factor() {
    if (currentToken().type == TokenType::PLUS ||
        currentToken().type == TokenType::MINUS ||
        currentToken().type == TokenType::BIT_NOT) {  // ~ operator

        TokenType op = currentToken().type;
        advance();
        auto operand = factor();
        return std::make_unique<UnaryOpNode>(op, std::move(operand));
    }

    if (currentToken().type == TokenType::NUMBER) {
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
    }

    if (currentToken().type == TokenType::IDENTIFIER) {
        if (!std::holds_alternative<std::string>(currentToken().value)) {
            throw std::runtime_error("Invalid identifier token value");
        }
        std::string name = std::get<std::string>(currentToken().value);
        advance();
        return std::make_unique<VariableNode>(name);
    }

    if (currentToken().type == TokenType::LPAREN) {
        advance();
        auto node = expr();
        if (currentToken().type != TokenType::RPAREN)
            throw std::runtime_error("Expected ')'");
        advance();
        return node;
    }

    throw std::runtime_error("Unexpected token: " + currentToken().toString());
}
