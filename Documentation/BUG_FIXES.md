# BUG FIXES

## Assertions & Debugging

- **[ ]  Investigated and resolved assertion failure for `NODE_TYPE_MAX`:**
  - The issue stemmed from `NODE_TYPE_MAX` being moved within the `enum`, causing unexpected behavior in `cassert`.
  - Identified and accounted for the differences between C and C++ assertion behavior.

## Memory Management

- **[ ]  Fixed `file_contents()` to check for `NULL` return value from `malloc()`.**

## Token Handling

- **[ ]  Refactored token handling:**
  - Removed unnecessary linked lists and `create/free` functions.
  - Removed `print_tokens()` as it was no longer needed.

## Lexing

- **_TODO:_** Add lexing-specific bug fixes here.

## Data Types

- **[ ]  Removed `integer_t` in favor of `long long`.**

## Parsing

- **[ ]  Refactored `parse_expr()` to:**
  - Accept `char* source`, `char** end`, and `Node* result`.
  - Eliminate `working_node` and use `result` directly.
  - Remove root node allocation (handled at a higher level).
  - **Implemented parsing using a `while` loop** instead of handling a single expression.

---

# Other Considerations

## Parsing Context

- Explored how the parser could parse **within and into a given parsing context**.
- Implemented a **parsing context** to manage multiple environments:
  - **Type & Variable Definitions** → Ensures symbols are properly defined and typed.
  - **Operator Environment** → Maps operators to their respective functions.

## Operator Handling

- Operators were classified into categories such as:
  - Prefix unary, postfix unary
  - Prefix binary, infix binary, postfix binary
  - Additional classifications where necessary
- **Implemented a clean and maintainable way to define new operators programmatically.**
