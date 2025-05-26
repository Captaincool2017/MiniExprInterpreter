#include "main.h"

int main() {
    std::string input;

    std::cout << "Enter an arithmetic expression (or blank to quit):\n";
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input.empty()) break;

        try {
            Lexer lexer(input);
            std::vector<Token> tokens = lexer.tokenize();

            Parser parser(tokens);
            std::unique_ptr<Expr> ast = parser.parse();

            std::cout << "AST: " << ast->toString() << "\n";
            double result = ast->evaluate();
            std::cout << "Result: ";
            if (result == static_cast<int>(result)) {
                std::cout << static_cast<int>(result) << "\n";
            } else {
                std::cout << result << "\n";
            }
        } catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << "\n";
        }
    }

    return 0;
}
