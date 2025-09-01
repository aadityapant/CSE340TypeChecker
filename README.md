CSE340 Project 3 — Hindley–Milner-style Type Checker (C++)

A recursive-descent lexer + parser + type checker for a small language.
The checker enforces constraints C1–C5, infers types for implicit variables, and prints either a type-mismatch line or the final type of each variable as specified in the assignment.

🚀 What this does

Lexes & parses the project language (tokens, grammar provided in spec).

Tracks expressions appearing in assignments, if/while conditions, and switch discriminants.

Infers types for variables declared implicitly (first appearance in body) using a simplified Hindley–Milner unification across all occurrences.

Enforces constraints (C1–C5):

C1: LHS type must equal RHS type (assignments)

C2: Binary operands must have the same type

C3: Operand of ! must be bool

C4: if/while conditions must be bool

C5: switch expression must be int

Outputs either:

TYPE MISMATCH <line> <C1|C2|C3|C4|C5> on first violation, or

One line per variable (or equivalence class) like x: int # or a, b: ? #, in program order.

🧩 Language at a glance (per spec)

Built-in types: int, real, bool

Literals: NUM (int), REALNUM (real), true, false

Prefix expressions:

expression → primary | unary_operator expression | binary_operator expression expression

unary_operator → !

binary_operator → + - * / > < >= <= = <>

Statements: assignment, if (...) { ... }, while (...) { ... }, switch (...) { case NUM: { ... } ... }

Variables: declared explicitly via var_list : type; or implicitly when first used in body.

See CSE340 – Project 3: Type Checking for the full token list, grammar, and output rules.

🛠️ Build & Run

The assignment targets Ubuntu 19.04+ with g++ 7.5+.

# if sources are split
g++ -std=gnu++17 -O2 -Wall -Wextra \
  inputbuf.cc lexer.cc main.cc \
  -o typecheck

# if everything is in one file (e.g., main.cc)
g++ -std=gnu++17 -O2 -Wall -Wextra main.cc -o typecheck


Run by piping a program on stdin:

./typecheck < program.txt

📦 Project structure (yours)
.
├─ inputbuf.h / inputbuf.cc   # buffered char I/O (pushback, unget string)
├─ lexer.h / lexer.cc         # tokens, reserved words, number/id scanners, comments
├─ main.cc (parser + checker) # recursive-descent parser & type inference/constraints
└─ (optionally) tests/

🔍 How the implementation works (high-level)

Lexical analysis (LexicalAnalyzer)

Skips whitespace and // comments, recognizes numbers (with REALNUM), identifiers/keywords, and all operators/punctuators from the spec.

Parsing (recursive-descent)

Implements the grammar from the spec, including prefix forms for unary/binary expressions and the three statement kinds.

Type inference & checking

While parsing, collects variable occurrences into per-expression lists (allExpress) for assignments, comparisons, if/while, and switch.

After parsing, iteratively propagates discovered types through these sets until fixed-point:

If all operands agree on a concrete built-in type, assign it to unknowns.

If a constraint is violated, immediately print TYPE MISMATCH <line> <Cx> and exit.

Final printing

For each variable in program order, print name: type # if resolved, or print whole equivalence class a, b, c: ? # once if unresolved and share the same (unknown) type name, matching the spec’s output format.

✅ Examples

Type error (C1):

a, b: int;
{
  a = < b 2;
}


Output:

TYPE MISMATCH 3 C1


(assignment LHS int vs RHS bool from comparison)

No error, inferred types & groups:

{
  x = + a * b c;
  y = ! < a x;
  z = w;
}


Possible output (per spec’s grouping rules):

x, a, b, c: ? #
y: bool #
z, w: ? #


Tip: Create additional edge-case tests (mixed numeric/boolean chains, nested prefix ops, implicit variables only in conditions, etc.), as Gradescope uses hidden tests.

🧪 Developer notes

InputBuffer supports GetChar, UngetChar, and UngetString for robust tokenization.

The lexer’s number scanner detects REALNUM when fractional digits follow a dot; otherwise NUM.

Expressions use prefix form exactly as in the grammar; ensure your test inputs follow that form.

The checker treats + - * / as producing the operand type and relational operators as producing bool, as required.

⚠️ Academic integrity

If this repo is public, ensure you follow your course’s sharing policy for starter files and solutions.

📄 License

Coursework code copyright and usage policies may apply (see your course).
You may license your own additions as desired.

References

CSE340 – Project 3: Type Checking (PDF) — tokens, grammar, constraints, outputs.
