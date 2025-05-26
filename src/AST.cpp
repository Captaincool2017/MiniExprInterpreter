#include "AST.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

NumberNode::NumberNode(double value) : value(value) {}

double NumberNode::evaluate() const {
    return value;
}

std::string NumberNode::toString() const {
    // Format with fixed precision to avoid too long decimals
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << value;
    std::string s = oss.str();

    // Remove trailing zeros and possibly the dot if integer
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    if (!s.empty() && s.back() == '.') {
        s.pop_back();
    }

    return s;
}

BinaryOpNode::BinaryOpNode(TokenType op, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right)
    : op(op), left(std::move(left)), right(std::move(right)) {}

double BinaryOpNode::evaluate() const {
    double lval = left->evaluate();
    double rval = right->evaluate();

    switch (op) {
        case TokenType::PLUS:  
            return lval + rval;
        case TokenType::MINUS: 
            return lval - rval;
        case TokenType::MUL:   
            return lval * rval;
        case TokenType::DIV:
            if (rval == 0) throw std::runtime_error("Division by zero");
            return lval / rval;
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
            op == TokenType::DIV ? "/" : "?")
        << " " << right->toString() << ")";
    return oss.str();
}
