#include "Token.h"
#include <sstream>

Token::Token(TokenType t) : type(t), value(std::monostate{}) {}

Token::Token(TokenType t, int val) : type(t), value(val) {}

Token::Token(TokenType t, double val) : type(t), value(val) {}

std::string Token::toString() const {
    std::ostringstream oss;
    switch (type) {
        case TokenType::NUMBER:
            if (std::holds_alternative<int>(value))
                oss << "NUMBER(" << std::get<int>(value) << ")";
            else if (std::holds_alternative<double>(value))
                oss << "NUMBER(" << std::get<double>(value) << ")";
            else
                oss << "NUMBER(?)";
            break;
        case TokenType::PLUS:  oss << "PLUS"; break;
        case TokenType::MINUS: oss << "MINUS"; break;
        case TokenType::MUL:   oss << "MUL"; break;
        case TokenType::DIV:   oss << "DIV"; break;
        case TokenType::LPAREN: oss << "LPAREN"; break;
        case TokenType::RPAREN: oss << "RPAREN"; break;
        case TokenType::END:    oss << "END"; break;
    }
    return oss.str();
}
