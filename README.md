# boolex - generate truth tables

`boolex` is a simple command-line tool written in C++ that parses a boolean expression, converts it to postfix notation, and prints its full **truth table** along with all intermediate subexpressions.

---

- Parses infix boolean expressions with operators:
  - `!` (NOT)
  - `@` (IFF)
  - `>` (IMPLICATION FORWARD)
  - `<` (IMPLICATION BACKWARD)
  - `&` (AND)
  - `|` (OR)
  - `=` (EQUIVALENCE)
  - `^` (XOR)
- Supports parentheses `()` for grouping.
- Automatically detects all unique boolean variables.
- Prints all subexpressions and their evaluated results.
- Clean, column-aligned truth table output.

- Sensitive input
- It has simple expression validity checking, but its not perfect, I'm sure its capable of being broken
---


### Prerequisites
You’ll need:
- A C++17 (or newer) compiler
- `make` (optional)

### Using `make`
```bash
make 

manual compilation
g++ -std=c++17 -Wall -Werror -I include src/*.cpp -o boolex

# Examples 
./boolex '(!p | q) = (p & q)'
./boolex '(a & b) | (!a & !b)'

cs peoples favorite
./boolex '(a ^ b) ^ b = a'

# output example for '(a ^ b) ^ b = a'
a                   b                   a ^ b               a ^ b ^ b           a ^ b ^ b = a
0                   0                   0                   0                   1
1                   0                   1                   1                   1
0                   1                   1                   0                   1
1                   1                   0                   1                   1
