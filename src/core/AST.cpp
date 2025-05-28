#include "core/AST.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cmath>  // For std::pow and std::fmod

// ---------------- NumberNode ----------------

NumberNode::NumberNode(double value) : value(value) {}

double NumberNode::evaluate(VarContext& /*context*/) const {
    return value;
}

std::string NumberNode::toString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << value;
    std::string s = oss.str();
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    if (!s.empty() && s.back() == '.') s.pop_back();
    return s;
}

// ---------------- BinaryOpNode ----------------

BinaryOpNode::BinaryOpNode(TokenType op, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right)
    : op(op), left(std::move(left)), right(std::move(right)) {}

double BinaryOpNode::evaluate(VarContext& context) const {
    double lval = left->evaluate(context);
    double rval = right->evaluate(context);

    // Helper to convert double to int for bitwise operations
    auto toInt = [](double v) -> int { return static_cast<int>(v); };

    switch (op) {
        case TokenType::PLUS:  return lval + rval;
        case TokenType::MINUS: return lval - rval;
        case TokenType::MUL:   return lval * rval;
        case TokenType::DIV:
            if (rval == 0) throw std::runtime_error("Division by zero");
            return lval / rval;
        case TokenType::MOD:
            if (rval == 0) throw std::runtime_error("Modulo by zero");
            return std::fmod(lval, rval);
        case TokenType::POWER:
            return std::pow(lval, rval);

        // Bitwise operators (operands treated as ints)
        case TokenType::BIT_AND:
            return toInt(lval) & toInt(rval);
        case TokenType::BIT_OR:
            return toInt(lval) | toInt(rval);
        case TokenType::BIT_XOR:
            return toInt(lval) ^ toInt(rval);
        case TokenType::LSHIFT:
            return toInt(lval) << toInt(rval);
        case TokenType::RSHIFT:
            return toInt(lval) >> toInt(rval);

        default:
            throw std::runtime_error("Unknown binary operator");
    }
}

std::string BinaryOpNode::toString() const {
    std::ostringstream oss;
    oss << "(" << left->toString() << " "
        << (op == TokenType::PLUS ? "+" :
            op == TokenType::MINUS ? "-" :
            op == TokenType::MUL ? "*" :
            op == TokenType::DIV ? "/" :
            op == TokenType::MOD ? "%" :
            op == TokenType::POWER ? "**" :
            op == TokenType::BIT_AND ? "&" :
            op == TokenType::BIT_OR ? "|" :
            op == TokenType::BIT_XOR ? "^" :
            op == TokenType::LSHIFT ? "<<" :
            op == TokenType::RSHIFT ? ">>" : "?")
        << " " << right->toString() << ")";
    return oss.str();
}

// ---------------- UnaryOpNode ----------------

UnaryOpNode::UnaryOpNode(TokenType op, std::unique_ptr<Expr> operand)
    : op(op), operand(std::move(operand)) {}

double UnaryOpNode::evaluate(VarContext& context) const {
    double val = operand->evaluate(context);

    switch (op) {
        case TokenType::PLUS:
            return val;
        case TokenType::MINUS:
            return -val;
        case TokenType::BIT_NOT:
            return ~static_cast<int>(val);
        default:
            throw std::runtime_error("Unknown unary operator");
    }
}

std::string UnaryOpNode::toString() const {
    std::string opStr;
    switch (op) {
        case TokenType::PLUS: opStr = "+"; break;
        case TokenType::MINUS: opStr = "-"; break;
        case TokenType::BIT_NOT: opStr = "~"; break;
        default: opStr = "?"; break;
    }
    return "(" + opStr + operand->toString() + ")";
}

// ---------------- VariableNode ----------------

VariableNode::VariableNode(const std::string& name) : name(name) {}

double VariableNode::evaluate(VarContext& context) const {
    auto it = context.find(name);
    if (it == context.end()) {
        throw std::runtime_error("Undefined variable: " + name);
    }
    return it->second;
}

std::string VariableNode::toString() const {
    return name;
}

// ---------------- AssignmentNode ----------------

AssignmentNode::AssignmentNode(std::string varName, std::unique_ptr<Expr> expr)
    : varName(std::move(varName)), expr(std::move(expr)) {}

double AssignmentNode::evaluate(VarContext& context) const {
    double val = expr->evaluate(context);
    context[varName] = val;
    return val;
}

std::string AssignmentNode::toString() const {
    return "(" + varName + " = " + expr->toString() + ")";
}
