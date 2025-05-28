#include "core/Token.h"
#include <sstream>
#include <iomanip>  // Added for std::setprecision

Token::Token(TokenType t) : type(t), value(std::monostate{}) {}

Token::Token(TokenType t, int val) : type(t), value(val) {}

Token::Token(TokenType t, double val) : type(t), value(val) {}

Token::Token(TokenType t, const std::string& val) : type(t), value(val) {}

std::string Token::toString() const {
    switch (type) {
        case TokenType::NUMBER: {
            if (std::holds_alternative<int>(value)) {
                return std::to_string(std::get<int>(value));
            } else if (std::holds_alternative<double>(value)) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(6) << std::get<double>(value);
                std::string s = oss.str();
                s.erase(s.find_last_not_of('0') + 1, std::string::npos);
                if (!s.empty() && s.back() == '.') s.pop_back();
                return s;
            }
            break;
        }
        case TokenType::IDENTIFIER:
            if (std::holds_alternative<std::string>(value)) {
                return std::get<std::string>(value);
            }
            break;

        case TokenType::PLUS:       return "+";
        case TokenType::MINUS:      return "-";
        case TokenType::MUL:        return "*";
        case TokenType::DIV:        return "/";
        case TokenType::POWER:      return "**";
        case TokenType::MOD:        return "%";
        case TokenType::LPAREN:     return "(";
        case TokenType::RPAREN:     return ")";
        case TokenType::COMMA:      return ",";
        case TokenType::ASSIGN:     return "=";

        // Bitwise operators and shifts
        case TokenType::BIT_AND:    return "&";
        case TokenType::BIT_OR:     return "|";
        case TokenType::BIT_XOR:    return "^";
        case TokenType::BIT_NOT:    return "~";
        case TokenType::LSHIFT:     return "<<";
        case TokenType::RSHIFT:     return ">>";

        case TokenType::END:        return "<END>";
    }
    return "<UNKNOWN>";
}
