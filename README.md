# 🧮 Mini Expression Interpreter

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![C++](https://img.shields.io/badge/language-C++17-blue.svg)
![Build Status](https://img.shields.io/badge/build-passing-brightgreen)

A lightweight C++ interpreter for evaluating mathematical and bitwise expressions with variable support. It parses, builds an abstract syntax tree (AST), and evaluates expressions with proper precedence and associativity rules.

## ✨ Features

- Basic arithmetic: `+`, `-`, `*`, `/`, `%`, `**` (power)
- Bitwise operations: `&`, `|`, `^`, `~`, `<<`, `>>`
- Parentheses for grouping: `(2 + 3) * 4`
- Unary operators: `-`, `+`, `~`
- Variable assignments and chained expressions: `x = y = 5`
- Graceful error handling with informative messages
- Modular architecture (Lexer, Parser, AST, Evaluator)
- Unit tested using custom test suite

## 📁 Directory Structure

```
MiniExprInterpreter/
├── include/          # Header files
│   └── core/
├── src/              # Implementation
│   └── core/
├── tests/            # Unit tests
├── build/            # Compiled output
├── Makefile          # Build and test automation
├── LICENSE           # MIT License
└── README.md         # Project documentation
```

## 🧪 Running Tests

To compile and run all unit tests:

```bash
make test
```

If successful, output will show:

```plaintext
Test PASSED: "2 + 3 * 4" = 14
Assignment test PASSED: x = 5 = 5
...
All tests completed successfully.
```

## 🛠️ Build Instructions

1. Clone the repository

```bash
git clone https://github.com/yourusername/MiniExprInterpreter.git
cd MiniExprInterpreter
```

2. Build the project

```bash
make
```

3. Run (if interactive mode/main is added)

```bash
./build/interpreter
```

## 🧠 Example Expressions

```plaintext
1 + 2
(3 + 4) * 2
x = 5
y = x + 3
2 ** 3
16 >> 2
~5
```

## 🚧 Roadmap

- [x] Arithmetic and bitwise parsing
- [x] Variable assignment and memory
- [x] Operator precedence and associativity
- [x] REPL (Interactive Interpreter)
- [ ] Function support (e.g., `sin(x)`, `sqrt(x)`)
- [ ] Command-line file execution support

## 🐞 Known Issues

- No support for floating-point bitwise operations
- Unary plus has no effect but is parsed
- Parser errors may not report full token context

## 🤝 Contributing

Pull requests are welcome. Please open an issue for any bug report, feature request, or major change proposal. Let's build it together!

## 📜 License

This project is licensed under the MIT License.

## 👨‍💻 Author

Developed by Nishchay Pallav (Mike)  
B.Tech ECE @ NITK, Embedded Systems, Electronics and Robotics Enthusiast

## 💬 Feedback

Feel free to open issues or discussions. You can also drop suggestions or queries at your convenience. Let's make it better—together!
