# AlyCompiler's TODO

- [x] Lex source into tokens or something

- [ ] Parse tokens or something into AST -- Just a tree containing data about the program

- [ ] Compile AST into assembly, let's start with x86_64? We could also transpile into another language that then gets compiled, like C or something.

# Dumb ideas that we could implement

- Compile to brain-fuck XD? - This is just a perfect idea. I am not know if it's possible.

- Write end-to-end tests in Agol? This gives me something new to learn?

# -- Miscellaneous

- Unnamed variable declarations
  - It would be cool if an assignment and/or variable declaration could have no identifier, and work on a singular unnamed variable in the environment.

- State Machine Parser:
  - Just a thought but when we lex right now we need to go deeper and as the compiler and parser get more advanced maybe we could use a state machine or something to handle the special cases rather than how we are currently doing it. Right now, I think we'll handle all the special cases in the same way we are because it's going to become so much more complicated and that will waste time.

- Have a type that represents all the other types:
  - This would allow variables to be defined with a type of another type.