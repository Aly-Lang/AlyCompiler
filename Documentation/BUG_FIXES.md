# AlyCompiler BUG FIXES

- [x] `file_contents()` does not check for NULL malloc return values.

- [x] Tokens do not need to be linked lists, or have `create/free` functions.

  - [x] We can also get rid of `print_tokens()`, while we are at it.

- [ ] When lexing, zero out given token pointer using memset().

- [ ] Get rid of `integer_t`, just use long long and get on with it.

- [ ] Completely change `parse_expr(...)`. Accept `char* source, char** end, Node* result`. Get rid of working_node completely, use result. Get rid of root node allocation, that will be handled at a handled at a higher level, just use result.

- [ ] Parse in a while loop, instead of just parsing a single expression.

- Think about how parser could parse within and into a given parsing context.

  - Maybe a parsing context contains multiple environments for types, defined variables, etc. This would allow the parser to look up variable access symbols to ensure that they are defined and of the proper type.

  - This is also where the operator environment could live, with mappings of operators to functions that apply them somehow, right?

  - They would also need to contain what type of operator they are, right?

  - So, for example, there are prefix unary operators, postfix unary operators, prefix binary operators, infix binary operators, postfix binary operators, and more... How do we programmatically define a new operator in a way that doesn't suck?