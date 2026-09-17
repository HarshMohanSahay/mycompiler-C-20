# MyCompiler

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.10+-blue.svg)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen.svg)

A **complete compiler toolchain** for a Mini-like imperative language, implemented from scratch in **C++17**. This project implements a full compilation pipeline: lexical analysis → parsing → AST construction → bytecode generation → stack-based VM execution.

---

## 🚀 Features

| Component | Description |
|-----------|-------------|
| **Lexer** | Hand-written scanner with token recognition for keywords, identifiers, numbers, operators, and punctuation |
| **Parser** | Recursive-descent parser with precedence climbing for expressions (supports `+ - * /` with correct precedence) |
| **AST** | Type-safe AST using `std::unique_ptr` for memory-safe tree ownership (Expr/Stmt hierarchy) |
| **Compiler** | Single-pass AST visitor generating stack-machine bytecode |
| **Bytecode** | Compact instruction set: `PUSH_CONST`, `LOAD_VAR`, `STORE_VAR`, `ADD`, `SUB`, `MUL`, `DIV`, `PRINT`, `HALT` |
| **VM** | Stack-based interpreter with variable store (`std::unordered_map`), runtime error handling |
| **Debug Mode** | Built-in disassembler + token dump (`--debug` flag) |

---

## 🎯 Language Features

| Feature | Syntax Example |
|---------|---------------|
| Variable assignment | `x = 42;` |
| Arithmetic (`+ - * /`) | `z = x + y * 2;` |
| Operator precedence | `*`/`/` bind tighter than `+`/`-` |
| Parenthesized expressions | `result = (a + b) * 2;` |
| Numeric literals (int/float) | `x = 3.14;` |
| Print statement | `print x + y;` |
| Statement termination | `;` required |
| Single-line comments | `// this is ignored` |
| Whitespace insensitive | Yes |

---

## 🏗 Architecture

```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│  Source     │────▶│   Lexer     │────▶│   Parser    │────▶│  Compiler   │────▶│    VM       │
│  (.mini)    │     │  (Tokens)   │     │    (AST)    │     │ (Bytecode)  │     │  (Output)   │
└─────────────┘     └─────────────┘     └─────────────┘     └─────────────┘     └─────────────┘
        │                                                                │
        │                       ┌─────────────────┐                     │
        └──────────────────────▶│   Debug Mode    │─────────────────────┘
                                │ (--debug flag)  │
                                └─────────────────┘
```

**Pipeline Stages:**
1. **Lexical Analysis** → Token stream (keywords, identifiers, literals, operators)
2. **Syntax Analysis** → Abstract Syntax Tree via recursive descent
3. **Code Generation** → Stack-machine bytecode via AST visitor pattern
4. **Execution** → Stack-based VM with variable map

---

## 🏗 Project Structure

```
MyCompiler/
├── include/              # Header files
│   ├── AST.h            # AST node definitions (Expr/Stmt hierarchies)
│   ├── Bytecode.h       # Bytecode instruction set & Chunk
│   ├── Compiler.h       # AST → Bytecode compiler
│   ├── Lexer.h          # Lexical analyzer
│   ├── Parser.h         # Recursive-descent parser
│   ├── Token.h          # Token definitions
│   └── VM.h             # Virtual Machine
├── src/                  # Implementation
│   ├── Bytecode.cpp     # Disassembler & instruction helpers
│   ├── Compiler.cpp     # AST visitor → bytecode
│   ├── Lexer.cpp        // Tokenizer implementation
│   ├── Parser.cpp       // Recursive-descent parser
│   ├── VM.cpp           // Stack VM interpreter
│   └── main.cpp         // Pipeline orchestration + CLI
├── test.mini             # Example: x = 42; print x;
├── test2.mini            # Example: arithmetic with precedence
├── CMakeLists.txt        # CMake 3.10+, C++17
└── README.md
```

---

## 🛠 Building

**Requirements:** C++17 compiler (GCC 7+, Clang 5+, MSVC 19.1+), CMake 3.10+

```bash
# Configure & build
cmake -B build -S .
cmake --build build

# Or classic
# mkdir build && cd build && cmake .. && make

# Run
./build/MyCompiler test.mini
./build/MyCompiler test2.mini --debug
```

---

## 💡 Usage

```bash
# Basic execution
./MyCompiler <source_file.mini>

# Debug mode: tokens + bytecode disassembly + output
./MyCompiler <source_file.mini> --debug
```

### Example

**Input** (`test2.mini`):
```mini
x = 10;
y = 20;
z = x + y * 2;
print z;
```

**Output:**
```
50
```

**Debug Output** (`--debug`):
```
-----TOKENS-----
1: IDENTIFIER 'x'
1: EQUAL '='
1: NUMBER '10'
1: SEMICOLON ';'
2: IDENTIFIER 'y'
2: EQUAL '='
2: NUMBER '20'
2: SEMICOLON ';'
3: IDENTIFIER 'z'
3: EQUAL '='
3: IDENTIFIER 'x'
3: PLUS '+'
3: IDENTIFIER 'y'
3: STAR '*'
3: NUMBER '2'
3: SEMICOLON ';'
4: PRINT 'print'
4: IDENTIFIER 'z'
4: SEMICOLON ';'
4: EOF ''

-----BYTECODE----
0: PUSH_CONST 10
1: STORE_VAR x
2: PUSH_CONST 20
3: STORE_VAR y
4: LOAD_VAR x
5: LOAD_VAR y
6: PUSH_CONST 2
7: MUL
8: ADD
9: STORE_VAR z
10: LOAD_VAR z
11: PRINT
12: HALT

-----OUTPUT----
50
```

---

## 🧠 Implementation Highlights

| Area | Implementation Detail |
|------|----------------------|
| **Memory Safety** | AST uses `std::unique_ptr` for automatic ownership; no manual `delete` |
| **Parser** | Recursive descent with precedence climbing (`expression → term → factor`) |
| **Compiler** | Visitor pattern over AST; single-pass bytecode emission |
| **VM** | Stack machine with `std::vector<double>` operand stack + `unordered_map<string,double>` variables |
| **Error Handling** | Exceptions (`std::runtime_error`) caught at top level with line-number reporting |
| **Build** | Modern CMake with `target_include_directories`, warning flags per-compiler |

### Grammar (EBNF-style)
```
program     → statement* EOF
statement   → assignStmt | printStmt
assignStmt  → IDENTIFIER "=" expression ";"
printStmt   → "print" expression ";"
expression  → term (("+" | "-") term)*
term        → factor (("*" | "/") factor)*
factor      → NUMBER | IDENTIFIER | "(" expression ")"
```

---

## 🔧 Extending the Language

| Feature | Files to Modify |
|---------|-----------------|
| New operator (e.g., `%`) | `Token.h`, `Lexer.cpp`, `Parser.cpp`, `Bytecode.h`, `Compiler.cpp`, `VM.cpp`, `Bytecode.cpp` |
| New statement (`if`, `while`) | `AST.h` (Stmt hierarchy), `Parser.h/.cpp`, `Compiler.cpp`, `Bytecode.h`, `VM.cpp` |
| New type (strings, bools) | `Token.h`, `AST.h` (Expr variants), `Bytecode.h` (operand types), `VM.cpp` |
| Functions/calls | `AST.h`, `Parser`, `Compiler`, `VM` (call stack/frame) |

---

## 📚 Learning Outcomes

This project demonstrates:
- **Compiler theory in practice**: Lexing, parsing, AST, codegen, VM
- **Modern C++**: RAII, smart pointers, STL containers, exceptions
- **Design patterns**: Visitor (compiler), Recursive Descent (parser), Interpreter (VM)
- **Build systems**: Modern CMake with target-based includes
- **Debugging tooling**: Built-in disassembler & token inspector

---

## 🙋‍♂️ Author

Built as a learning project to understand compiler internals from front to back.  
Feel free to fork, extend, or use as a reference for your own compiler journey!