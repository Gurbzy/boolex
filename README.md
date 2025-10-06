# boolex - generate truth tables

`boolex` is a simple command-line tool written in C++ that parses a boolean expression, converts it to postfix notation, and prints its full **truth table** along with all intermediate subexpressions.

---

- Parses infix boolean expressions with operators:
  - `!` (NOT)
  - `~` (NOT)
  - `&` (AND)
  - `|` (OR)
  - `=` (EQUIVALENCE)
  - `^` (XOR)
- Supports parentheses `()` for grouping.
- Automatically detects all unique boolean variables.
- Prints all subexpressions and their evaluated results.
- Clean, column-aligned truth table output.

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
