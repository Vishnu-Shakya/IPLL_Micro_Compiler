# IPLL_CompilerDesign

> Compiler Design project (Coursework) — lexer, parser, and further compiler phases implemented using Lex (Flex), Yacc (Bison) and C.
 
## Table of Contents

* [Project Overview](#project-overview)
* [Repository Structure](#repository-structure)
* [Features Implemented](#features-implemented)
* [Prerequisites](#prerequisites)
* [Build & Run Instructions](#build--run-instructions)
* [Examples](#examples)
* [Testing](#testing)
* [Design & Implementation Notes](#design--implementation-notes)
---

## Project Overview

This repository contains coursework for a Compiler Design lab (6th semester / university coursework). The goal is to implement the front-end phases of a compiler (lexical analysis and parsing) using **Lex (Flex)** and **Yacc (Bison)**, with additional components in **C** for semantic actions, symbol table management, intermediate representation (IR) and simple code generation or interpretation if present.

Typical responsibilities covered by the project:

* Tokenization (lexer) using Lex/Flex
* Parsing and grammar specification using Yacc/Bison (LR parsing)
* Construction of parse tree / abstract syntax tree (AST)
* Basic semantic analysis (type checking, symbol table)
* Intermediate code generation or direct translation to simple target (optional)
* Test cases and example programs

## Repository Structure 

```
IPLL_CompilerDesign/
├─ lexer.l                # Lex/Flex specification
├─ parser.y               # Yacc/Bison grammar and semantic actions
├─ ast.c, ast.h           # AST node definitions and helpers
├─ symbol_table.c/.h      # Symbol table implementation
├─ codegen.c              # (Optional) Code generation or IR emission
├─ main.c                 # Compiler driver: run lexer+parser and produce output
├─ Makefile               # Build rules for quick setup
├─ tests/                 # Sample input programs and expected outputs
│  ├─ sample1.c
│  └─ sample2.txt
├─ docs/                  # Any documentation, UML, or screenshots
└─ README.md              # (this file)
```

## Features Implemented

* Lexical analyzer recognizes identifiers, keywords, numeric literals (integers/floats), string literals, operators (`+ - * / = == != < > <= >=`), delimiters, and comments.
* Parser implements grammar for a small procedural language (declarations, assignments, expressions, conditionals `if/else`, loops `while/for`, function definitions and calls).
* AST construction: semantic actions in the parser build an AST for later passes.
* Symbol table management: supports scope, insertion/lookup, and simple type information.
* Semantic checks: undeclared identifier detection, duplicate declarations, basic type checking.
* Intermediate representation (three-address code) generator (optional).
* Simple code emitter or interpreter for generated IR (optional).

## Prerequisites

Install the following tools (examples for Ubuntu/Debian):

```bash
sudo apt update
sudo apt install -y build-essential flex bison gcc make
```

On macOS using Homebrew:

```bash
brew install flex bison gcc make
```

## Build & Run Instructions

A `Makefile` is strongly recommended. Example build steps (manual):

```bash
# 1) Generate lexer code
flex lexer.l            # produces lex.yy.c

# 2) Generate parser code
bison -d parser.y       # produces parser.tab.c and parser.tab.h (or parser.y output names)

# 3) Compile everything
gcc -std=c99 -g -o ipll_compiler lex.yy.c parser.tab.c ast.c symbol_table.c codegen.c main.c -lfl

# 4) Run
./ipll_compiler tests/sample1.txt
```

Or use the Makefile target:

```bash
make                # builds the compiler
make run ARGS=test/sample1.txt   # optional convenience target
make clean
```

## Examples

Add concrete example programs and the expected output. Example: `tests/sample1.txt`

**Input (sample1.txt)**

```
int a;
a = 5;
if (a > 3) a = a + 1;
```

**Run**

```bash
./ipll_compiler tests/sample1.txt
```

**Expected output**

```
Token stream: INT IDENTIFIER SEMICOLON IDENTIFIER ASSIGN NUMBER SEMICOLON IF LPAREN IDENTIFIER GT NUMBER RPAREN IDENTIFIER ASSIGN IDENTIFIER PLUS NUMBER SEMICOLON
Parse: Program -> DeclarationList -> ...
AST: (Program ...)
Symbol table:
 name    type    scope
 a       int     global

Semantic check: OK
Generated 3-address code:
 t1 = 5
 a = t1
 if a > 3 goto L1
 goto L2
L1:
 t2 = a + 1
 a = t2
L2:
```

## Testing

* Add test programs in `tests/` and expected output files `tests/expected/sample1.out`.
* A simple test runner script can compare expected vs actual output:

```bash
for f in tests/*.txt; do
  ./ipll_compiler "$f" > out.tmp
  diff -u "${f%.txt}.out" out.tmp || echo "Mismatch: $f"
done
```

## Design & Implementation Notes

* **Grammar style:** (e.g., LR(1), precedence rules used to disambiguate `if-else`, left-recursive rules converted where needed)
* **AST representation:** describe node structs, memory ownership, and traversal routines.
* **Symbol table:** hashing strategy, scope representation (stack of scopes), type info stored.
* **Semantic checks implemented:** list checks (undeclared variables, re-declaration, type mismatch in binary ops, return type checks in functions, arity checks for function calls).
* **Code generation / IR:** representation of temporaries, labels, and sample instruction format.
---

