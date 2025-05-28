#ifndef AST_H
#define AST_H

#include "core/Token.h"
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>

// Forward declaration for variable context
using VarContext = std::unordered_map<std::string, double>;

// Base class for all expression nodes
class Expr {
public:
    virtual ~Expr() = default;
    virtual double evaluate(VarContext& context) const = 0;
    virtual std::string toString() const = 0;
};

// Node for numeric literals
class NumberNode : public Expr {
public:
    explicit NumberNode(double value);
    double evaluate(VarContext& context) const override;
    std::string toString() const override;

private:
    double value;
};

// Node for binary operations (+, -, *, /)
class BinaryOpNode : public Expr {
public:
    BinaryOpNode(TokenType op, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right);

    double evaluate(VarContext& context) const override;
    std::string toString() const override;

private:
    TokenType op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
};

// Node for unary operations (+, -)
class UnaryOpNode : public Expr {
public:
    UnaryOpNode(TokenType op, std::unique_ptr<Expr> operand);
    double evaluate(VarContext& context) const override;
    std::string toString() const override;

private:
    TokenType op;
    std::unique_ptr<Expr> operand;
};

// Node for variables (e.g., a, x, total)
class VariableNode : public Expr {
public:
    explicit VariableNode(const std::string& name);
    double evaluate(VarContext& context) const override;
    std::string toString() const override;

private:
    std::string name;
};

// ** New: Node for assignments (e.g., x = 5 + 2) **
class AssignmentNode : public Expr {
public:
    AssignmentNode(std::string varName, std::unique_ptr<Expr> expr);
    double evaluate(VarContext& context) const override;
    std::string toString() const override;

private:
    std::string varName;
    std::unique_ptr<Expr> expr;
};

#endif // AST_H
