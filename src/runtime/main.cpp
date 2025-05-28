#include "core/main.h"  

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

int main() {
    std::cout << "Enter arithmetic expressions including +, -, *, /, %, **, &, |, ^, ~, <<, >>\n";
    std::cout << "Supports variables and assignments (e.g., x = 5 * 3).\n";
    std::cout << "Press Enter on empty line to quit.\n";

    std::string input;
    VarContext context;  // variable context persists across lines

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        input = trim(input);

        if (input.empty()) break;

        try {
            Lexer lexer(input);
            std::vector<Token> tokens = lexer.tokenize();

            Parser parser(tokens);
            std::unique_ptr<Expr> ast = parser.parse();

            std::cout << "AST: " << ast->toString() << "\n";

            double result = ast->evaluate(context);

            std::cout << "Result: ";
            constexpr double EPS = 1e-9;
            if (std::abs(result - static_cast<int>(result)) < EPS) {
                std::cout << static_cast<int>(result) << "\n";
            } else {
                std::cout << std::fixed << std::setprecision(6) << result << "\n";
            }
        } catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << "\n";
        }
    }

    return 0;
}
