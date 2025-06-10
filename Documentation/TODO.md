# AlyCompiler TODO:

- [x] Lex source into tokens or something.

- [ ] Parse tokens or something into AST -- Just a tree containing data about the program.

- [ ] Compile AST into assembly, let's start with `x86_64?` We could also transpile into another language that then gets compiled, like C or something.

## Miscellaneous

1. Unnamed Variable:
    - It would be cool if an assignment and/or variable declaration could have no identifier, and work on a singular unnamed variable in environment.

# Have a type that represents all the other types - Not sure this makes a lot of sense
    - This would allow variables to be defined with a type of a different type, not sure why this would be useful other than `calloc` because it's generally only used for arrays so we could do it for something else?