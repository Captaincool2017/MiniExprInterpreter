# Mini Expression Interpreter

A simple arithmetic expression interpreter written in modern C++ (C++17).  
It supports:

- **Integer and floating-point (double) numbers**
- **Basic arithmetic operations**: `+`, `-`, `*`, `/`
- **Proper expression parsing** with precedence
- **Parentheses** for grouping
- **Human-readable Abstract Syntax Tree (AST)** representation

---

## 🛠️ Project Structure

```
.
├── include/        # Header files (Token.h, Lexer.h, Parser.h, AST.h)
├── src/            # Source files (Token.cpp, Lexer.cpp, Parser.cpp, AST.cpp)
├── main.cpp        # Entry point
├── Makefile        # Build automation
└── README.md       # You are here
```

---

## 🚀 Getting Started

### ✅ Prerequisites

- C++17-compatible compiler (`g++`, `clang++`, etc.)
- `make` utility (optional, for using the Makefile)

### 🧱 Build

```bash
make
```

Binary will be placed in `build/interpreter`.

### ▶️ Run

```bash
./build/interpreter
```

Example REPL interaction:

```
Enter an arithmetic expression (or blank to quit):
> 3 + 4 * 2
AST: (3 + (4 * 2))
Result: 11

> (1.5 + 2.5) * 2
AST: ((1.5 + 2.5) * 2)
Result: 8
```

---

## 🧪 Example Test Cases

| Expression         | AST Output                     | Result |
|--------------------|--------------------------------|--------|
| `1 + 2`            | `(1 + 2)`                      | `3`    |
| `4 * (3 - 1)`      | `(4 * (3 - 1))`                | `8`    |
| `3.5 + 1.5`        | `(3.5 + 1.5)`                  | `5`    |
| `10 / 4`           | `(10 / 4)`                     | `2.5`  |
| `5 + 2 * 3`        | `(5 + (2 * 3))`                | `11`   |
| `(5 + 2) * 3`      | `((5 + 2) * 3)`                | `21`   |

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
