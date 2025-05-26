#ifndef AST_H
#define AST_H

#include "Token.h"
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>

// Base class for all expression nodes
class Expr {
public:
    virtual ~Expr() = default;
    virtual double evaluate() const = 0;      // Return double instead of int
    virtual std::string toString() const = 0;
};

// Node for numeric literals
class NumberNode : public Expr {
public:
    explicit NumberNode(double value);        // Store double value
    double evaluate() const override;
    std::string toString() const override;

private:
    double value;
};

// Node for binary operations (+, -, *, /)
class BinaryOpNode : public Expr {
public:
    BinaryOpNode(TokenType op, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right);

    double evaluate() const override;
    std::string toString() const override;

private:
    TokenType op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
};

#endif // AST_H
