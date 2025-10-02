# Balanced Parentheses Checker (C)

This project implements a simple **stack-based parentheses matcher** in C.  
It checks whether an expression has properly balanced parentheses, brackets, and braces:
- `()`
- `[]`
- `{}`

---

## 🔹 Features

- Stack implemented using a linked list (`struct Node`).
- Supports push, pop, display, and cleanup functions.
- Checks for:
  - Correct matching pairs (`(` with `)`, `[` with `]`, `{` with `}`).
  - Proper nesting order.
  - No leftover unclosed brackets.
- Detects unbalanced cases like:
  - Extra closing bracket.
  - Wrongly ordered brackets.
  - Missing closing bracket.

---

## 🔹 Example

### Input
(a + b) * (c + d)
### Output
Indeed balanced

### Input
((a + b]
### Output
Not balanced


---

## 🔹 File Structure

- `main.c` – CLI entry point (takes user input).
- `bm.h` – Header file (stack structures and function declarations).
- `bm.c` – Implementation (stack functions + `isBalanced`).
- `test.c` – Unit tests for multiple expressions.

---

## 🔹 Build & Run

### Compile the interactive version
```bash
gcc main.c bm.c -o balance
./balance
gcc test.c bm.c -o test_balance
./test_balance

## MAKEFILE
make        # builds ./main
make test   # builds ./tests
make asan   # builds ./main with AddressSanitizer
make clean  # cleans up
