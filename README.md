# CSE340 Project 3 — Hindley–Milner-style Type Checker (C++)

A recursive-descent **lexer + parser + type checker** for a small language.  
The checker enforces constraints **C1–C5**, infers types for **implicit variables**, and prints either a type-mismatch line or the final type of each variable as specified in the assignment.

---

## 🚀 What this does

- **Lexes & parses** the project language (tokens, grammar provided in spec).
- **Tracks expressions** appearing in assignments, `if`/`while` conditions, and `switch` discriminants.
- **Infers types** for variables declared implicitly (first appearance in body) using a simplified Hindley–Milner unification across all occurrences.
- **Enforces constraints (C1–C5):**
  - **C1**: LHS type must equal RHS type (assignments)
  - **C2**: Binary operands must have the same type
  - **C3**: Operand of `!` must be `bool`
  - **C4**: `if`/`while` conditions must be `bool`
  - **C5**: `switch` expression must be `int`
- **Outputs** either:
  - `TYPE MISMATCH <line> <C1|C2|C3|C4|C5>` on first violation, **or**
  - One line per variable (or equivalence class) like `x: int #` or `a, b: ? #`, in program order.

---

## 🧩 Language at a glance (per spec)

- **Built-in types**: `int`, `real`, `bool`
- **Literals**: `NUM` (int), `REALNUM` (real), `true`, `false`
- **Prefix expressions**:

## 🔍 How the implementation works (high-level)
Lexical analysis (LexicalAnalyzer)

Skips whitespace and // comments.

Recognizes numbers (including REALNUM), identifiers/keywords, and all operators/punctuators from the spec.

Parsing (recursive-descent)

Implements the grammar (prefix form for unary/binary expressions) and the three statement kinds.

Type inference & checking

While parsing, collects variable occurrences into per-expression lists (allExpress) for assignments, comparisons, if/while, and switch.

After parsing, iteratively propagates discovered types until fixed-point:

If all operands agree on a concrete type, assign it to unknowns.

If a constraint is violated, immediately print TYPE MISMATCH <line> <Cx> and exit.

Final printing

For each variable in program order, print name: type # if resolved.

If unresolved but linked through usage, print the equivalence class once as a, b, c: ? # (shared unknown type).

## ✅ Examples
Type error (C1)

Input

a, b: int;
{
  a = < b 2;
}


Output

TYPE MISMATCH 3 C1


(Assignment LHS int vs RHS bool from comparison.)

No error — inferred types & groups

Input

{
  x = + a * b c;
  y = ! < a x;
  z = w;
}


Possible output (per grouping rules)

x, a, b, c: ? #
y: bool #
z, w: ? #


Tip: Create additional edge-case tests (mixed numeric/boolean chains, nested prefix ops, implicit variables only in conditions, etc.).
---

## 🧪 Developer notes

InputBuffer supports GetChar, UngetChar, and UngetString for robust tokenization.

Number scanning marks REALNUM when fractional digits follow a dot; otherwise NUM.

Expressions are prefix exactly as in the grammar; ensure test inputs follow that form.

The checker treats + - * / as producing the operand type and relational operators as producing bool.

## ⚠️ Academic integrity

If this repo is public, ensure you follow your course’s sharing policy for starter files and solutions.
