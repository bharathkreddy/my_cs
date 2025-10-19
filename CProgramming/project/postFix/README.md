# Infix to Postfix Converter (Shunting Yard Algorithm in C)

This project implements an **infix to postfix expression converter** in C using 
Dijkstra's *Shunting Yard Algorithm*.  

It supports:
- Multi-digit numbers (`123`, `45.67`)
- Variables (`x`, `y`, `n`)
- Operators (`+ - * / ^`)
- Functions (`log`, `exp`, `sin`, `cos`)
- Parentheses for grouping

---

# 📚 Algorithm

1. This uses the Shunting Yard Algorithm:
2. Read tokens (numbers, variables, operators, functions, parentheses).
3. Operands are added directly to the output.
4. Operators are pushed onto a stack, with precedence and associativity rules applied.
5. Functions are pushed on the stack and moved after arguments close.
6. At the end, all remaining operators are popped into the output.

# 🔧 Future Work

1. Add support for more math functions (e.g., tan, sqrt).
2. Add postfix evaluation to compute results.
3. Improve error handling for invalid expressions.

