#include "Lexer.h"
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

// New number() method that returns a Token with int or double
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
        // Parse as double
        double val = std::stod(numStr);
        return Token(TokenType::NUMBER, val);
    } else {
        // Parse as int
        int val = std::stoi(numStr);
        return Token(TokenType::NUMBER, val);
    }
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

        if (std::isdigit(ch)) {
            tokens.push_back(number());  // Use new number() method
        } else if (ch == '+') {
            tokens.emplace_back(TokenType::PLUS);
            advance();
        } else if (ch == '-') {
            tokens.emplace_back(TokenType::MINUS);
            advance();
        } else if (ch == '*') {
            tokens.emplace_back(TokenType::MUL);
            advance();
        } else if (ch == '/') {
            tokens.emplace_back(TokenType::DIV);
            advance();
        } else if (ch == '(') {
            tokens.emplace_back(TokenType::LPAREN);
            advance();
        } else if (ch == ')') {
            tokens.emplace_back(TokenType::RPAREN);
            advance();
        } else {
            throw std::runtime_error(std::string("Invalid character: ") + ch);
        }
    }

    return tokens;
}
