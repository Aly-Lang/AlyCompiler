# AlyCompiler's TODO

- [x] Lex source into tokens or something

- [ ] Parse tokens or something into AST -- Just a tree containing data about the program

- [ ] Compile AST into assembly, let's start with x86_64? We could also transpile into another language that then gets compiled, like C or something.

# Kind of Urgent

- [x] Lex past comments or something.

- [ ] Write a LISP runtime in the compiled language.

- [ ] Add token member to AST node structure. This would allow for much better error messages that point to the source code that the error originates from.  
  - We should also think about line count or something like that; maybe node AST holds custom structure containing token span, as well as file path (if applicable), line number, column number, etc.

# Dumb ideas that we could implement

- `=Any=` type that can accept any type -- This would be cool to be able to accept any type as a parameter. We may need a way to query what type something is, bu t that is also totally doable. This may be too complicated, but would be cool.

- Compile to brain-fuck XD? - This is just a perfect idea. I am not know if it's possible.

- Write end-to-end tests in Algol? This gives me something new to learn?

# -- Miscellaneous

- Allow automatic type deduction, as we already have the ability (or should have the ability) to deduce return type of an expression, why require type annotation explicitly in variable declarations? Maybe have custom `deduce` type or something.

- Decide what the syntax is for uninitialized variables -- Maybe we can do something like the example below.Perhaps we could do so something like `a : integer !`

We could could also have a specific value the parser recognizes as uninitialized, like `a : integer = None` or something.

- Unnamed variable declarations
  - It would be cool if an assignment and/or variable declaration could have no identifier, and work on a singular unnamed variable in the environment.

- State Machine Parser:
  - Just a thought but when we lex right now we need to go deeper and as the compiler and parser get more advanced maybe we could use a state machine or something to handle the special cases rather than how we are currently doing it. Right now, I think we'll handle all the special cases in the same way we are because it's going to become so much more complicated and that will waste time.

- Have a type that represents all the other types:
  - This would allow variables to be defined with a type of another type.

- Compile to CHIP 8 ASM:
 - Someone is working on a CHIP-8 virtual machine, assembler and disassembler, etc. in PHP, and it would be cool to collaborate on that with them. 

 - No reason why Aly can't target CHIP-8.