# AlyCompiler TODO

---

## ✅ Completed

- [x] Lex source into tokens  
- [x] Lex past comments

---

## 🚧 Compiler Pipeline

### 🔁 Lexing / Parsing
- [ ] **Parse tokens into AST**  
  The AST should represent the structure of the program, containing relevant data.

- [ ] **Add token member to AST nodes**  
  To improve error reporting, each AST node should store information about its source token:  
  - Token span (start and end positions)  
  - File path (if applicable)  
  - Line number and column number

---

### ⚙️ Code Generation
- [ ] **Compile AST into assembly** (Start with x86_64?)  
  Initially, we could compile directly to assembly or consider an intermediate step like transpiling to C, which can then be compiled.  

- [ ] **Create a `CodeGen` structure with function pointers**  
  - This would allow the code generation process to be modular and consistent, with different backends having their own semantic adjustments.  
  - Move away from switch cases in functions by defining code generation behaviors using a structure.

---

## 🔥 High Priority

- [ ] **Write a LISP runtime** in the compiled language  
  - A runtime for executing LISP-style code in the generated language would be essential.

- [ ] **Add support for line/column tracking in the AST**  
  - Having this information would greatly enhance error reporting and debugging.

- [ ] **Compile with `-Wall` and `-WExtra`**, fix warnings  
  - Ensure clean compilation and fix any existing warnings.

---

## 🧠 Language Features

### 🔧 Type System & Variables
- [ ] **Support `=Any=` type**  
  - A special type that can accept any other type as its value.  
  - We may need a way to query the type of a value at runtime, but it's doable.

- [ ] **Automatic type deduction**  
  - Allow the compiler to automatically deduce types for variables.  
  - If the return type of an expression can be inferred, do not require explicit type annotations for variables.

- [ ] **Uninitialized variables**  
  - Decide on syntax for uninitialized variables:  
    - Example: `a : integer !`  
    - Alternatively: `a : integer = None` (or any other sentinel value).

- [ ] **A type that represents all other types**  
  - Allow a type that could represent *any* type. This could be useful for dynamic handling of types in advanced cases.

- [ ] **Unnamed variable declarations**  
  - Support for declaring variables without an explicit identifier, which could refer to a singular unnamed variable in the environment.  
    - Example: `some_value = 10` could be treated as an unnamed variable.

---

### 📞 Function Calls
- [ ] **Allow named arguments in any order**  
  - The ability to pass arguments in any order if they are named.  
  - Example: `diff(y: 9, 6)` could be re-ordered during parsing to `diff(9, 6)`.

---

## 🤯 Crazy / Fun Ideas

- [ ] **Compile to Brainfuck**  
  - Just for fun—compile Aly code into Brainfuck. Not sure if it’s practical, but it’d be an interesting challenge.

- [ ] **Compile to CHIP-8 assembly**  
  - Someone is working on a CHIP-8 virtual machine, assembler, and disassembler in PHP. It could be cool to collaborate with them and get Aly to target CHIP-8.

- [ ] **Write end-to-end tests in Algol**  
  - This could be a fun learning experience, exploring a classic language while testing the compiler.

---

## 🛠️ Structural Changes & Refactors

- [ ] **Convert `Environment` type into an AST node**  
  - This change would make the environment more flexible and allow it to be managed similarly to other AST nodes (e.g., for garbage collection or memory management).  
  - It would also make the code more LISP-like, improving consistency with the rest of the system.

- [ ] **Consider using a state machine for the parser**  
  - As the parser grows more complex, a state machine could help handle edge cases and improve maintainability.  
  - Currently, we are handling special cases directly in the parser, but a state machine could help separate concerns and improve scalability.

---

## 📌 Miscellaneous

- [ ] **Finalize syntax for uninitialized variables**  
  - Deciding on a clean and consistent syntax for uninitialized variables will be important for clarity and user experience.

- [ ] **Refactor type inference**  
  - Continue to improve the type inference system, particularly in cases where types can be automatically deduced.

- [ ] **Finalize approach for referencing types**  
  - Define how types should reference other types. This could help with creating meta-types or dealing with more complex type systems.

- [x] **Fix warnings during compilation**  
  - Enable `-Wall` and `-WExtra` in the compiler, and fix any warnings that are outputted to ensure clean, production-quality code.
