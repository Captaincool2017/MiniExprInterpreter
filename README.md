# 🧮 Mini Expression Interpreter

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![C++](https://img.shields.io/badge/language-C++17-blue.svg)
![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)

A lightweight, high-performance C++ interpreter that brings mathematical and bitwise expressions to life through an interactive REPL experience. Built with a clean, modular architecture featuring lexical analysis, recursive descent parsing, AST construction, and expression evaluation with proper operator precedence.

## 🎯 What This Project Offers

This interpreter demonstrates core compiler construction concepts while providing a practical tool for:

- **Interactive Computing** - REPL environment for instant expression evaluation
- **Educational Tool** - Learn compiler design through clean, well-documented code
- **Mathematical Calculator** - Support for complex arithmetic and bitwise operations
- **Variable Management** - Persistent memory across REPL sessions
- **Error Recovery** - Graceful handling with informative diagnostic messages

Perfect for students learning compiler theory, developers exploring language implementation, or anyone needing a programmable calculator with variable support.

## ✨ Core Features

### 🔢 Mathematical Operations
Complete arithmetic support with proper precedence:
- **Basic Operations**: `+`, `-`, `*`, `/`, `%` (modulo)
- **Exponentiation**: `**` (power operator)
- **Unary Operations**: `-5`, `+3`, `~bits`
- **Parentheses**: `(2 + 3) * 4` for grouping

### 🧠 Bitwise Operations
Full bitwise manipulation capabilities:
- **Logic Operations**: `&` (AND), `|` (OR), `^` (XOR)
- **Bit Shifting**: `<<` (left shift), `>>` (right shift)  
- **Complement**: `~` (bitwise NOT)
- **Mixed Expressions**: `(x << 2) | (y & 255)`

### 🗃️ Variable System
Persistent variable storage with assignment chaining:
- **Simple Assignment**: `x = 42`
- **Expression Assignment**: `result = (a + b) * c`
- **Chained Assignment**: `x = y = z = 10`
- **Variable References**: Use variables in any expression

### 🖥️ Interactive REPL
Professional command-line interface:
- **Instant Evaluation** - See results immediately
- **Session Persistence** - Variables survive across expressions
- **Error Recovery** - Continue after syntax/runtime errors
- **Clean Exit** - `Ctrl+D` or empty line to quit

### 🧱 Clean Architecture
Modular design following compiler construction best practices:
- **Lexer** - Tokenizes input with proper error reporting
- **Parser** - Recursive descent with precedence climbing
- **AST** - Clean abstract syntax tree representation
- **Evaluator** - Tree-walking interpreter with variable context
- **REPL** - Interactive shell with error handling

## 🗂️ Project Architecture

```
MiniExprInterpreter/
├── 📄 Makefile              # Build automation and testing
├── 📄 LICENSE               # MIT License
├── 📁 include/              # Header files
│   └── 📁 core/            
│       ├── lexer.h         #   Tokenization and lexical analysis
│       ├── parser.h        #   Recursive descent parser
│       ├── ast.h           #   Abstract syntax tree nodes
│       ├── evaluator.h     #   Expression evaluation engine
│       └── interpreter.h   #   REPL and error handling
├── 📁 src/                  # Implementation
│   └── 📁 core/
│       ├── lexer.cpp       #   Token recognition and scanning
│       ├── parser.cpp      #   Syntax analysis and AST building
│       ├── ast.cpp         #   AST node implementations
│       ├── evaluator.cpp   #   Tree-walking evaluation
│       ├── interpreter.cpp #   REPL loop and error recovery
│       └── main.cpp        #   Entry point
├── 📁 tests/                # Comprehensive test suite
│   ├── test_lexer.cpp      #   Tokenization tests
│   ├── test_parser.cpp     #   Parsing and AST tests
│   ├── test_evaluator.cpp  #   Evaluation logic tests
│   └── test_main.cpp       #   Integration tests
├── 📁 build/                # Compiled output
└── 📄 README.md            # This documentation
```

## 🚀 Quick Start

### Prerequisites
- **C++17** compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- **Make** build system
- Terminal/Command Prompt

### Installation & Usage
```bash
# Clone the repository
git clone https://github.com/Captaincool2017/MiniExprInterpreter.git
cd MiniExprInterpreter

# Build the project
make

# Run the interactive interpreter
./build/interpreter
```

### 🧪 Running Tests
Comprehensive test suite covering all components:
```bash
# Run all unit tests
make test

# Expected output
Running tests...
./build/test_evaluator
Test PASSED: "1 + 2" = 3
Test PASSED: "10 - 3" = 7
Test PASSED: "4 * 2.5" = 10
Test PASSED: "10 / 4" = 2.5
Test PASSED: "2 ** 3" = 8
Test PASSED: "10 % 3" = 1
Test PASSED: "-5 + 10" = 5
Test PASSED: "-(2 + 3) * 4" = -20
Test PASSED: "2 + 3 * 4" = 14
Test PASSED: "(2 + 3) * 4" = 20
Assignment test PASSED: x = 5 = 5
Assignment test PASSED: y = x + 3 = 8
Test PASSED: "5 & 3" = 1
Test PASSED: "5 | 2" = 7
Test PASSED: "5 ^ 1" = 4
Test PASSED: "1 << 3" = 8
Test PASSED: "16 >> 2" = 4
Test PASSED: "~5" = -6
Test PASSED: "x = ~5" = -6
Test PASSED: "x & 3" = 2
Bitwise operation tests PASSED.
Test PASSED (exception thrown) for input: "10 / 0"
Test PASSED (exception thrown) for input: "10 % 0"
Test PASSED (exception thrown) for input: "unknownVar + 5"
All tests completed successfully.
```

## 💡 Interactive Examples

### Basic Arithmetic
```plaintext
> 2 + 3 *4
AST: (2 + (3 * 4))
Result: 14
> (10 -2) / 4
AST: ((10 - 2) / 4)
Result: 2
> 2 ** 3
AST: (2 ** 3)
Result: 8
```

### Variable Operations
```plaintext
> x = 42
AST: (x = 42)
Result: 42
> y = x / 6
AST: (y = (x / 6))
Result: 7
> result = x + y * 2
AST: (result = (x + (y * 2)))
Result: 56
```

### Bitwise Manipulation
```plaintext
> flags = 10
AST: (flags = 10)
Result: 10
> mask = 255                    
AST: (mask = 255)
Result: 255
> result = flags & mask
AST: (result = (flags & mask))
Result: 10
> shifted = result << 2
AST: (shifted = (result << 2))
Result: 40
> ~shifted
AST: (~shifted)
Result: -41
```

### Complex Expressions
```plaintext
> x = y = 5
AST: (x = (y = 5))
Result: 5
> complex = (x + y) * 2 ** 3 - (x & y)
AST: (complex = (((x + y) * (2 ** 3)) - (x & y)))
Result: 75
> final = complex >> 2
AST: (final = (complex >> 2))
Result: 18
```

## 📊 Sample REPL Session

```plaintext
Enter arithmetic expressions including +, -, *, /, %, **, &, |, ^, ~, <<, >>
Supports variables and assignments (e.g., x = 5 * 3).
Press Enter on empty line to quit.
> radius = 5
AST: (radius = 5)
Result: 5
> area = 3.14159 * radius ** 2
AST: (area = (3.14159 * (radius ** 2)))
Result: 78.539750
> circumference = 2 * 3.14159 * radius
AST: (circumference = ((2 * 3.14159) * radius))
Result: 31.415900
> bits = 240
AST: (bits = 240)
Result: 240
> low_nibble = bits & 15
AST: (low_nibble = (bits & 15))
Result: 0
> high_nibble = (bits & (15 << 4)) >> 4
AST: (high_nibble = ((bits & (15 << 4)) >> 4))
Result: 15
```

## 🧠 Technical Implementation

### Lexical Analysis
- **Token Types**: Numbers, operators, identifiers, parentheses
- **Number Formats**: Decimal
- **Error Recovery**: Reports position and context for invalid tokens

### Parsing Strategy
- **Recursive Descent** with operator precedence climbing
- **Left Associativity** for most operators (`+`, `-`, `*`, `/`)
- **Right Associativity** for exponentiation (`**`)
- **Precedence Levels**: Parentheses → Unary → Power → Multiply/Divide → Add/Subtract → Bitwise

## 🎓 Educational Value

This project demonstrates:

- **Compiler Construction** - Complete pipeline from source to execution
- **Language Design** - Operator precedence, associativity, and syntax rules
- **Data Structures** - AST representation and tree traversal
- **Error Handling** - Graceful recovery and user-friendly messages
- **Software Architecture** - Clean separation of concerns and modularity

Perfect for:
- **CS Students** learning compiler theory and implementation
- **Interview Preparation** for systems programming roles
- **Portfolio Projects** showcasing language implementation skills

## 🌟 Resume-Ready Description

> *"Built a complete expression interpreter in C++ featuring lexical analysis, recursive descent parsing, AST construction, and tree-walking evaluation. Implements proper operator precedence, variable management, and interactive REPL with comprehensive error handling. Demonstrates compiler construction principles with clean, modular architecture and extensive unit testing."*

## 🚧 Future Enhancements

**Planned Features:**
- 🔢 **Floating-Point Support** - Double precision bitwise support
- 📊 **Mathematical Functions** - `sin()`, `cos()`, `sqrt()`, `log()`
- 📁 **File Execution Mode** - `./interpreter script.expr`
- 🕰️ **REPL History** - Arrow key navigation and command recall
- 🎨 **Syntax Highlighting** - Colorized input and output
- 🔧 **Advanced Features** - Conditional expressions, loops

**Enhancement Ideas:**
- Add string literal support and manipulation
- Implement user-defined functions
- Create expression compilation to bytecode
- Add debugging and step-through capabilities

## 🐞 Known Limitations

- **Floating-Point Bitwise**: Bitwise operations only work with integers
- **Error Context**: Parser errors could provide more detailed token context  
- **Number Overflow**: Large integers may overflow without warning
- **Unary Plus**: Parsed correctly but has no computational effect

## 🤝 Contributing

Contributions are highly encouraged! This project is perfect for:

**Beginner Contributions:**
- Add more test cases
- Improve error messages
- Enhance documentation

**Intermediate Contributions:**
- Add new operators or functions
- Implement REPL history
- Create additional number formats

**Advanced Contributions:**
- Add floating-point support
- Implement function definitions
- Create bytecode compilation

### How to Contribute:
1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. **Write tests** for your changes
4. **Commit** with clear messages (`git commit -m 'Add amazing feature'`)
5. **Push** and create a Pull Request

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**Nishchay Pallav (Mike)**  
B.Tech ECE @ NITK | Computer Science, Embedded Systems & Robotics Enthusiast  
🔗 [GitHub](https://github.com/Captaincool2017) | 📧 [Email](mailto:nishchaypallav2002@gmail.com) | 💼 [LinkedIn](https://www.linkedin.com/in/nishchaypallav/)

---

*Built with ❤️ for the Computer Science and Programming community*