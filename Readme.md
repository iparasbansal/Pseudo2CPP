# Pseudo2CPP: Intent-Driven CP Boilerplate & Compiler Transpiler

Pseudo2CPP is an offline C++17 command-line developer tool that acts as both an **Intent-Driven Algorithm Selector** and a **Structured Pseudocode Transpiler**. 

It maps natural-language competitive programming (CP) prompts to standard DSA algorithms and compiles custom pseudocode logic blocks into syntactically valid C++ templates.

---

## Features

- **Mathematical Intent Classifier**: Uses a Vector Space Model with **TF-IDF & Cosine Similarity** to match natural language problem descriptions to candidate algorithms.
- **Fuzzy Token Matching**: Employs Levenshtein edit distance word-by-word against the vocabulary.
- **Domain Context Multipliers**: Adjusts scoring weights dynamically based on domain context clues (Trees, Graphs, Strings, Lists).
- **Softmax Confidence Scaling**: Evaluates top classification candidates using a Softmax probability distribution.
- **Compiler Transpiler Frontend**: Includes a built-in Lexical Analyzer and Recursive Descent Parser that translates structured pseudocode statements into clean, template-safe C++17.
- **Modern C++ Generation**: Resolves dynamic parameters using C++ templates and automatic type inference (`auto`), eliminating the need for explicit type annotations in the pseudocode.

---

## Quick Start

1. **Build the Engine & Run Tests**:
   ```bash
   make clean && make && make test
   ```

2. **Select an Algorithm from Natural Language Query**:
   ```bash
   ./transpiler --query "cheapest route between cities with negative tolls" --explain
   ```

3. **Transpile Custom Pseudocode Block**:
   ```bash
   ./transpiler --input examples/custom_logic.txt --output solution.cpp
   ```

---

## Supported Pseudocode Grammar

The transpiler parses and compiles structured pseudocode matching the following syntax:

* **Functions**: `function solve(arr, n) { ... }` $\rightarrow$ transpiles to standard C++ templates (`template<typename T_arr, typename T_n> auto solve(T_arr arr, T_n n)`).
* **Variable Declarations**: `let sum = 0` $\rightarrow$ `auto sum = 0;`.
* **Loops**:
  * `for i from 0 to n - 1 { ... }` $\rightarrow$ `for (int i = 0; i <= (n - 1); i++) { ... }`.
  * `while x < 100 { ... }` $\rightarrow$ `while (x < 100) { ... }`.
* **Conditionals**: `if (x % 2 == 0) { ... } else { ... }` $\rightarrow$ `if ((x % 2 == 0)) { ... } else { ... }`.
* **Functions & Returns**: `return x` $\rightarrow$ `return x;`.

---

## Architecture

```text
LogicAnalyzer.hpp      TF-IDF and Cosine Similarity intent engine
TranspilerCore.hpp     Compiler frontend (Lexer, Parser, AST, C++ Code Gen)
AlgorithmRegistry.hpp  DSA algorithm metadata registry
Generator.hpp          Algorithm-to-template generator routing
Templates.hpp          C++ algorithm boilerplate template database
main.cpp               CLI parser and generated code integration pipeline
tests/                 Intent classification and compiler translation unit tests
examples/              Sample CP prompts and custom pseudocode scripts
```

---

## Build Commands

```bash
make          # build transpiler CLI
make test     # run both intent matching and compiler test suites
make list     # print supported algorithms and complexities
make clean    # remove build objects and executables
```

---

## Author

Developed by Paras Bansal.
