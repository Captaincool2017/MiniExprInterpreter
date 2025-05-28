#include "core/Lexer.h"
#include "core/Parser.h"
#include "core/AST.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <limits>

// Helper to run one expression and check result (approximate for floating point)
void testExpression(const std::string& input, double expected, VarContext& context) {
    try {
        Lexer lexer(input);
        auto tokens = lexer.tokenize();

        Parser parser(tokens);
        std::unique_ptr<Expr> expr = parser.parse();

        double result = expr->evaluate(context);

        constexpr double EPS = 1e-9;
        if (std::abs(result - expected) > EPS) {
            std::cerr << "Test FAILED for input: \"" << input << "\". Expected: " << expected << ", got: " << result << "\n";
            assert(false);
        } else {
            std::cout << "Test PASSED: \"" << input << "\" = " << result << "\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "Test FAILED with exception for input: \"" << input << "\". Exception: " << ex.what() << "\n";
        assert(false);
    }
}

// Test error handling (should throw)
void testError(const std::string& input) {
    try {
        VarContext context;
        Lexer lexer(input);
        auto tokens = lexer.tokenize();

        Parser parser(tokens);
        std::unique_ptr<Expr> expr = parser.parse();

        expr->evaluate(context);

        std::cerr << "Test FAILED (no exception) for input: \"" << input << "\"\n";
        assert(false);
    } catch (...) {
        std::cout << "Test PASSED (exception thrown) for input: \"" << input << "\"\n";
    }
}

// Test variable assignment and reuse
void testAssignment() {
    VarContext context;
    std::string assign1 = "x = 5";
    std::string assign2 = "y = x + 3";

    // Evaluate assignment 1
    {
        Lexer lexer(assign1);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto expr = parser.parse();
        double val = expr->evaluate(context);
        assert(val == 5);
        assert(context["x"] == 5);
        std::cout << "Assignment test PASSED: " << assign1 << " = " << val << "\n";
    }

    // Evaluate assignment 2
    {
        Lexer lexer(assign2);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto expr = parser.parse();
        double val = expr->evaluate(context);
        assert(val == 8);
        assert(context["y"] == 8);
        std::cout << "Assignment test PASSED: " << assign2 << " = " << val << "\n";
    }
}

// Bitwise operation tests
void testBitwiseOperations() {
    VarContext context;

    // Use static_cast<int64_t> to avoid floating point surprises in expected values
    testExpression("5 & 3", static_cast<double>(5 & 3), context);        // 1
    testExpression("5 | 2", static_cast<double>(5 | 2), context);        // 7
    testExpression("5 ^ 1", static_cast<double>(5 ^ 1), context);        // 4
    testExpression("1 << 3", static_cast<double>(1 << 3), context);      // 8
    testExpression("16 >> 2", static_cast<double>(16 >> 2), context);    // 4

    // Unary bitwise NOT (~)
    testExpression("~5", static_cast<double>(~5), context);

    // Assignment with bitwise NOT and subsequent usage
    testExpression("x = ~5", static_cast<double>(~5), context);
    testExpression("x & 3", static_cast<double>((~5) & 3), context);

    std::cout << "Bitwise operation tests PASSED.\n";
}

int main() {
    VarContext context;

    // Basic arithmetic tests
    testExpression("1 + 2", 3, context);
    testExpression("10 - 3", 7, context);
    testExpression("4 * 2.5", 10, context);
    testExpression("10 / 4", 2.5, context);
    testExpression("2 ** 3", 8, context);        // power operator test
    testExpression("10 % 3", 1, context);        // modulus operator test
    testExpression("-5 + 10", 5, context);       // unary minus test
    testExpression("-(2 + 3) * 4", -20, context);

    // Parentheses and precedence
    testExpression("2 + 3 * 4", 14, context);
    testExpression("(2 + 3) * 4", 20, context);

    // Variable assignment and reuse
    testAssignment();

    // Bitwise operations
    testBitwiseOperations();

    // Error handling tests
    testError("10 / 0");          // Division by zero
    testError("10 % 0");          // Modulo by zero
    testError("unknownVar + 5");  // Undefined variable

    std::cout << "All tests completed successfully.\n";
    return 0;
}
