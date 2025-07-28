# AlyCompiler Development Roadmap

-----

## ✅ Completed

  * **Lexical Analysis:**
      * Lexed source into tokens.
      * Lexed past comments.
  * **AST Parsing:**
      * Parsed tokens into an Abstract Syntax Tree (AST).
      * Separated the **parsing stack** from the **parsing context**. The parsing context now manages scope hierarchies, while the stack handles internal parsing continuations. This separation prevents extraneous child contexts during function calls, which previously led to incorrect context management.
  * **Code Generation Fundamentals:**
      * Implemented **Address-of** (`&`) and **Dereference** (`*`) operators for pointers. This involved using the `lea` mnemonic for address-of and loading/dereferencing memory addresses for dereference.
      * Type-checked and validated variable accesses.
      * Fixed a bug where variable declarations with assignments were not code-generated properly.
      * Achieved initial compilation of the AST into **x86\_64 assembly**.
      * **Worked on parsing and code generation for `if` conditional statements.** (Updated)
  * **Compiler Infrastructure:**
      * Compiling with **`-Wall`** and **`-WExtra`** is enabled, and all associated warnings have been fixed, ensuring cleaner compilation.
  * **Examples:**
      * Implemented **Greatest Common Divisor (GCD)**, which required division codegen.
  * **Command Line Interface:**
      * Began handling command-line flags, including:
          * `--help, -h`: Prints usage and version information.
          * `--output, -o`: Sets the name of the output file.
          * `--format, -f`: Sets the target output format for generated code.
          * `--formats`: Lists all supported output formats.
          * `--notypecheck, -nt`: Skips type checking after parsing.
          * `--nocodegen, -nc`: Stops after type checking, without generating any code.

-----

## 🚧 Compiler Pipeline: Next Steps

-----

### External Function Support

We need to allow **external functions and symbols** to be defined. This will enable the use of standard library functions like `printf` or `fopen` for input/output operations.

  * **Declaration Syntax:** We'll define a clear syntax for declaring external functions, possibly `: ext <function_name> ([<parameter>]...)`. We also need to consider how to handle calling conventions (e.g., `: ext <function_name> ([<parameter>]....) : <mswin | linux>`), though this might add complexity for cross-compilation.
  * **String and Pointer Types:** Implementing **string types** and **pointers to them** is crucial for functions like `printf` that require format strings. Initially, we can consider a byte and byte pointer abstraction, eventually expanding to general pointers for any type.

### Expanded Examples

We'll develop additional examples to thoroughly test and demonstrate the compiler's capabilities.

  * **Least Common Multiple (LCM):** Implement the LCM function.
  * **Square Root (sqrt):** Implement a square root function.
  * **Perfect Square:** Implement a function to check for perfect squares, leveraging the integer square root implementation.

### Lexing / Parsing Enhancements

  - TODO: Compiler recognizes use of uninitialized variables
    - Could even not allow use of uninitialized pointers and also warn on other uninitialized uses.

  * **AST Node Token Information:** To significantly enhance error reporting, we'll add source **token information** to each AST node. This includes token span (start/end positions), file path, line number, and column number.

 - [x] DONE: Make parsing a type easier.
  - Currently we handle pointers in some places but not in others, and everything is kind of a mess. I think if we just parse variable declarations as an expression, we can then just parse that and in type-checking ensure that function parameters are all var. decl. The thing is we already do parse variable declarations as expressions, we just don't take advantage of the code because we don't use the parser stack continuation to do it, currently. The way to do it now is kind of code-duplicity, where we have the code to parse a type written separately everyway it's needed.

  My instinct is to just get a quick fix done in the form of duplicating the pointer type code everything it's needed, but I should probably just use parser stack continuation to handle function parameters and have that transform into function body stack handler. This way we will just parse any expression in a function parameter list and continue on doing so until we reach a closing parenthesis. Then, in type-checking, we can ensure all of the nodes in teh parameter list are var. decl. nodes, which means they all have valid type annotations.


-----

## ⚙️ Code Generation Improvements

-----

  * **Modular Code Generation:** We'll create a `CodeGen` structure that utilizes **function pointers** to modularize the code generation process. This will move away from large `switch` statements, allowing different backends to define their specific code generation behaviors consistently.
  * **Register Allocation and Stack Usage:** When scratch registers are exhausted during code generation, we'll implement mechanisms to utilize the **stack for temporary storage**. This will ensure the compiler can handle complex expressions without running out of registers.
  * **Block Return Types:** We'll convert expression lists (`{}`) into a standalone **expression type** (`NODE_TYPE_BLOCK`). This will enable blocks to have return values, specifically the return value of the last expression within the block, or a default value if no expressions are present.
  * **`if` Conditional Statement Context Handling:** The basic parsing of `if` statements is in place, but proper **context handling** for these statements still needs to be fully implemented. This should be a straightforward task. (Added)

-----

## 🔥 High Priority Features

-----

  - [ ] Within the typechecker handle function calls better.
    - We somehow need to access the type of each parameter as we iterate them, but we recently changed how functions parameters are parsed, and because of this we no longer store type symbols / information in the function AST itself. This means, while typechecking a function call, we would have to somehow know which context it pertain to. We could just store an extra node that points to the function environment node somehow, but I don't think that's the best solution.

  * **LISP Runtime in Aly:** We'll implement a **LISP runtime** written in the compiled language itself. This will serve as a significant dogfooding exercise and demonstrate the language's capabilities.
  * **Line/Column Tracking in AST:** We'll fully integrate **line and column tracking** into the AST to significantly improve the precision and helpfulness of error reporting and debugging.
  * **`environment_free` Method:** We'll create a method named **`environment_free`** for proper memory management and cleanup of environment-related data structures.

-----

## 🧠 Language Features

-----

### Type System & Variables

  * **`=Any=` Type Support:** Introduce a special **`=Any=` type** capable of accepting any other type as its value. This may necessitate runtime type querying.
  * **Automatic Type Deduction:** Enable the compiler to automatically **deduce variable types** where inference is possible, reducing the need for explicit type annotations.
  * **Uninitialized Variables Syntax:** Decide on a clear and consistent syntax for **uninitialized variables**, for example, `a : integer !` or `a : integer = None`.
  * **Universal Type Representation:** Explore a type that could represent ***any*** type. This could be useful for dynamic handling of types in advanced scenarios.
  * **Unnamed Variable Declarations:** Support declaring variables without an explicit identifier, referring to a singular unnamed variable in the environment (e.g., `some_value = 10` could be treated as an unnamed variable).

### Function Calls

  * **Named Arguments in Any Order:** Allow the ability to pass arguments in any order if they are named (e.g., `diff(y: 9, 6)` could be re-ordered during parsing to `diff(9, 6)`).

-----

## 🤯 Crazy / Fun Ideas

-----

  * **Compile to Brainfuck:** Just for fun, explore compiling Aly code into Brainfuck. This would be an interesting, albeit potentially impractical, challenge.
  * **Compile to CHIP-8 Assembly:** Collaborate with someone working on a CHIP-8 virtual machine to target CHIP-8 assembly.
  * **End-to-End Tests in Algol:** Write end-to-end tests in Algol. This could be a fun learning experience, exploring a classic language while testing the compiler.

-----

## 🛠️ Structural Changes & Refactors

-----

  * **Convert `Environment` Type to AST Node:** This change would make the environment more flexible, allowing it to be managed similarly to other AST nodes (e.g., for garbage collection or memory management). It would also make the code more LISP-like, improving consistency.
  * **State Machine for Parser:** As the parser grows more complex, consider using a **state machine** to handle edge cases and improve maintainability. Currently, special cases are handled directly in the parser, but a state machine could help separate concerns and improve scalability.

-----

## 📌 Miscellaneous

-----
  - [ ] Fix lambda parsing!
    - How do lambdas fit into a statically typed language? How can we accept a function as an argument? We will need some syntax to define a function signature like a type, that way a function parameters may have it's type be a function with a specific signature. We aren't able to just accept a `function` type because that is not able to be called. Rather, a call to a function defined in this way would not be able to be properly type-checked. I don't want to include a lambda runtime or whatever that does runtime typechecking, either.

    So I think the solution is some way to define a variable as a function with a specific type signature (parameters and return type). Basically, what you find in the headers of C and C++ programs. Let's think about how we could represent a type like this with out type system.

    WHEN TYPECHECKING A FUNCTION BODY:
    We need to know which function signature we are defining for. With our current syntax and how everything works, this is easy to do. Every time a function is defined, we have the parameter and return type data. We create a new context for functions, so it increments the scope we have when iterating as well (just like `if` expressions bodies).

    WHEN TYPECHECKING A FUNCTION CALL:
    We need to know which function signature we are defined for, both to set the return type as well as typecheck the given arguments against the expected parameters. If the return type was defined in a context that the function is not being called from: we shouldn't care about this! So maybe we don't need to keep track of the context the function was defined in. The comments mentioning this change in the typechecker are wrong, I'm pretty sure.

    So all of this makes me realize that a function signature needs to be a type, I guess. That would allow a function to be defined just like a variable. It just means that our typechecking would need to include function types, or we need to handle functions adn function signatures entirely on their own, like we currently do... I don't know!!!

    ```
    defun foo (function_parameter : (n : integer) : integer) : integer {
        function_parameter(25)
    }
    ```

    So the above shows how we may define a function parameter. Maybe we should extend this syntax to functions themselves?

    ```
    foo : integer (function_parameter : integer (n : integer), argument : integer) {
        function_parameter(argument)
    }

    double_the_int : integer (a : integer) {
        a * 2
    }

    foo(double_the_int, 25)
    ```

    As you can see I also changed the syntax to contain the return value first, then the parameter list.

    So I guess we need functions to be variables, since they sometimes need to be used like a variable access... (as seen in the `foo` function call above).

    So a function will be defined in variable environment like so:
    ```
    SYM:<function_variable_name> <-> FUNCTION
                                    `-- <return type symbol> [-> <parameter>]...
    ```

    Then, we just need to somehow get the body of the function by the function variable name during code generation. This is necessary so that we can actually implement the function at an address that corresponds to the function variable name in some way (like using it directly for the assembly address label we `jmp` to, for example).

    I presume this is what the functions environment should be for? Or, I just guess the body of the function could be stored in the AST like it is now.

    Final thoughts: Functions need to be defined as type in the type system, and not this foreign thing. This will allow functions to be passed as parameters and such, while still being completely type checked. I think we need to store a flat list of all function body definitions and ensure that no duplicates are allowed, even in the case of different scopes. This allows direct use of the function symbol as an assembly address and prevents having to mangle.

- [x] Remove global FUNCTION optimization in codegen
  - Whilst it does make the program an unnoticeable amount faster, it also breaks if any `if` expression lies between global function definitions...

  - [x] Fix messy git work tree
      - We already have a gitignore to ignore all build type files / folders and we have moved all examples to `examples` folder anyway so its just `src/`
    
    - [x] Have better build instructions for other toolchains
      - First of all, instead of using GNU Binutils (`as` and `ld`), most people probably don't care about that and just want to run `gcc`. Luckily with GCC, it's really, really easy.

      I had luck getting clang to produce working executables in a very straightforward manner as well, so if we can reproduce that today then let's definitely add that in there aas well.

   - [x] Change the type system surrounding pointers entirely
    - Switch from pointer nodes with children to nodes having a pointer flag and pointer count (or pointer flag is the pointer count non-zero). This will *greatly* simplify our typechecking, codegen, allocation, etc.

    This will most definitely break everything.

    Our current pointer types look like this: `@@integer`
    This gets converted into a `Node` that looks like this:
    ```
    POINTER
    `-- POINTER
        `-- SYM: "INTEGER"
    ```

    This is inefficient memory-wise and over-complicates the issue. There is literally no need to have the pointer type be a separate node type, or even a separate node.

    What we should have instead is a pointer indirection counter. This could be a part of every node, and, when non-zero, indicates the amount of pointers to the type of the node itself.

    ```
    SYM: "INTEGER" (indirection level = 2)
    ```
  
  - [ ] TODO / FIX: Fix `if` context handling during codegen
    - One thing that we are definitely not handling properly is contexts of `if` expressions during codegen.

  * **Division and Bit-Shifting Operators:** Implement division and bit-shifting binary operators to enable more powerful examples like `sqrt` and `perfect_square`.
  * **`+= / -=` with Reassignment `:=`:** Conceptualize how to handle the interaction between compound assignment operators (`+=`, `-=`) and the reassignment symbol (`:=`).
  * **Refactor Type Inference:** Continue to improve the type inference system, particularly in cases where types can be automatically deduced.
  * **Finalize Type Referencing Approach:** Define how types should reference other types. This could help with creating meta-types or dealing with more complex type systems.
  * **Compiler-Aided TODO Collection:** Have the compiler collect TODO comments and other directives from the source code, allowing for compiler-aided software design.

-----

## Syntax

-----

We need to support a **quick function declaration syntax**, which could look something like this:

```
integer_identity : integer (x : integer) { x }

void foo () {}

foo : None () {}

foo :[None() {}]
foo :None() {}
```

### Current Basic Syntax:

  * `...` means any amount repeated.
  * Surrounded by `[]` means it is optional.
  * Inside `""` means the string is compared literally.

**Helpers:**

  * **Parameter List:** `( <variable declaration> ["," <variable declaration>]... )`
  * **Expression List:** `{ <expression> [<expression>]... }`

**Syntaxes that make AST Nodes:**

  * **Integer:** `<positive-or-negative-integer>`
  * **Variable Declaration:** `<symbol> ":" <type>`
  * **Named Function:** `<variable declaration> <parameter list> <expression list>`
  * **Function:** `[ <type> <parameter list> <expression list> ]`
  * **Variable Access:** `<symbol>`
  * **Binary Operator:** `<expression> <operator> <expression>`
  * **Function Call:** `<symbol> <parameter list>`