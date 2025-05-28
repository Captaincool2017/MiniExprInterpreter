#include "core/Lexer.h"
#include <cctype>
#include <stdexcept>
#include <string>

Lexer::Lexer(const std::string& input) : input(input), pos(0) {}

char Lexer::currentChar() {
    if (pos >= input.length()) return '\0';
    return input[pos];
}

void Lexer::advance() {
    pos++;
}

void Lexer::skipWhitespace() {
    while (std::isspace(currentChar())) advance();
}

Token Lexer::number() {
    size_t startPos = pos;
    bool hasDecimalPoint = false;

    while (true) {
        char ch = currentChar();
        if (std::isdigit(ch)) {
            advance();
        } else if (ch == '.') {
            if (hasDecimalPoint) break;  // second decimal point - stop number
            hasDecimalPoint = true;
            advance();
        } else {
            break;
        }
    }

    std::string numStr = input.substr(startPos, pos - startPos);

    if (hasDecimalPoint) {
        double val = std::stod(numStr);
        return Token(TokenType::NUMBER, val);
    } else {
        int val = std::stoi(numStr);
        return Token(TokenType::NUMBER, val);
    }
}

Token Lexer::identifier() {
    size_t startPos = pos;
    while (std::isalnum(currentChar()) || currentChar() == '_') {
        advance();
    }
    std::string idStr = input.substr(startPos, pos - startPos);
    return Token(TokenType::IDENTIFIER, idStr);
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (true) {
        skipWhitespace();
        char ch = currentChar();

        if (ch == '\0') {
            tokens.emplace_back(TokenType::END);
            break;
        }
        if (std::isalpha(ch) || ch == '_') {
            tokens.push_back(identifier());
        } else if (std::isdigit(ch)) {
            tokens.push_back(number());
        } else if (ch == '+') {
            tokens.emplace_back(TokenType::PLUS);
            advance();
        } else if (ch == '-') {
            tokens.emplace_back(TokenType::MINUS);
            advance();
        } else if (ch == '*') {
            advance(); // consume first '*'
            if (currentChar() == '*') {
                advance(); // consume second '*'
                tokens.emplace_back(TokenType::POWER);
            } else {
                tokens.emplace_back(TokenType::MUL);
            }
        } else if (ch == '/') {
            tokens.emplace_back(TokenType::DIV);
            advance();
        } else if (ch == '%') {
            tokens.emplace_back(TokenType::MOD);
            advance();
        } else if (ch == '(') {
            tokens.emplace_back(TokenType::LPAREN);
            advance();
        } else if (ch == ')') {
            tokens.emplace_back(TokenType::RPAREN);
            advance();
        } else if (ch == ',') {
            tokens.emplace_back(TokenType::COMMA);
            advance();
        } else if (ch == '=') {
            tokens.emplace_back(TokenType::ASSIGN);
            advance();
        }
        // Bitwise operators and shifts
        else if (ch == '&') {
            tokens.emplace_back(TokenType::BIT_AND);
            advance();
        } else if (ch == '|') {
            tokens.emplace_back(TokenType::BIT_OR);
            advance();
        } else if (ch == '^') {
            tokens.emplace_back(TokenType::BIT_XOR);
            advance();
        } else if (ch == '~') {
            tokens.emplace_back(TokenType::BIT_NOT);
            advance();
        } else if (ch == '<') {
            advance();
            if (currentChar() == '<') {
                advance();
                tokens.emplace_back(TokenType::LSHIFT);
            } else {
                throw std::runtime_error("Invalid token: expected '<' after '<'");
            }
        } else if (ch == '>') {
            advance();
            if (currentChar() == '>') {
                advance();
                tokens.emplace_back(TokenType::RSHIFT);
            } else {
                throw std::runtime_error("Invalid token: expected '>' after '>'");
            }
        } else {
            throw std::runtime_error(std::string("Invalid character: ") + ch);
        }
    }

    return tokens;
}
