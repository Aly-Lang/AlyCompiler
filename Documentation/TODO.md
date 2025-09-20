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
      * Implemented **Greatest Common Divisor (GCD)**, which required division code-gen.
  * **Command Line Interface:**
      * Began handling command-line flags, including:
          * `--help, -h`: Prints usage and version information.
          * `--output, -o`: Sets the name of the output file.
          * `--format, -f`: Sets the target output format for generated code.
          * `--formats`: Lists all supported output formats.
          * `--notypecheck, -nt`: Skips type checking after parsing.
          * `--nocode-gen, -nc`: Stops after type checking, without generating any code.

-----

- [x] TODO: Update the lexer:
    - The lexer needs to have some way to let the caller know that the token lexed was a delimiter itself, as multiple of these may want to be lexed in a row (for example, during operator parsing, we want to parse `<` but also `<<`, so we must lex until we get a non-delimiter token).

- [ ] TODO: Add debug information using CFI directives
  - ![GNU Binutils documentation](https://sourceware.org/binutils/docs/as/)

- [x] TODO: Emacs Major Mode indenting and simplify syntax table entries.
  - This is a great example from SerenityOS :: https://github.com/SerenityOS/jakt/blob/main/editors/emacs/jakt-mode.el

- [x] TODO: Refactor Emacs Major Mode to be like it is but better
  - This is a great example from SerenityOS :: https://github.com/SerenityOS/jakt/blob/main/editors/emacs/jakt-mode.el

- [ ] TODO: Add token member to AST node structures.
  - This would allow for much better error messages that point to the source code that the error originates from.

  - We should also think about line count or something like that; maybe node ast holds custom structure containing token span, as well as file path (if applicable), line number, column number, etc.

## 🚧 Compiler Pipeline: Next Steps

-----

[x] ### External Function Support

  - I believe that we need a way to differentiate them as an external function from any other function. It's basically going to be a function variable that is callable, even though it hasn't been assigned a function/lambda. Currently, this is any function variable, because we don't do that extensive of type checking on functions / function calls.

  With this in mind, it may be smart to work on disallowing unassigned function calls before attempting to add to the feature that doesn't exist yet?

  So, function calls are currently typed checked in that the variable access is a function, and given arguments match parameter type, and that's it. We need to ensile that the function we are calling has been assigned to, I think? Otherwise, the variable may be uninitialized, and the call to contents of the variable will definitely break at RT.

  During type-checking, we iterate over the AST in a very specific way: in order!
  Because Aly works like C and requires variable and such to be defined before they are used, we are able to detect when a variable has not yet been assigned to. So all we have to do is add some sort of flag or something in the variable binding when a reassignment is type-checked. Then, when a function call happens, we already check the variable binding to ensure `function` type, so checking if it's uninitialized should be easier.

  After thinking about the syntax, we also need to keep in mind that `external` functions do not need this sort of special type-checking, and should only apply to functions that are't external... Also, external function calls should probably be code-genned differently, at least currently, as the language passes all arguments on the stack, and that's not the proper calling convention for every single platform.

  So, with all that in mind: maybe external functions are a different type than functions? For an example, let's say we had an "external function" type, as well as the "function" type we have now. I guess we would just skip the "callable" type checking that we just describe above adding when the type was "external function". I think this could be the way to go about this problem.

  Although, you can see in `external_function.aly` that this should not be allowed but for reference:
  ```
  putc : ext integer(c : integer)

  another_putc : integer(n : integer)
  another_putc := putc
  ```

  Is this okay? I think this should be fine. I never really want a function variable that isn't explicitly external to be used to reference a function that very much so external. So I think external functions just being a separate type is totally okay, at least for now.

  In Conclusion:
    - Parsing:: Syntax + Highlighting
      - Expand `parse_type` to parse `ext` keyword before doing what it already does.

      - FOR NOW -- Error when `ext` is used on non-function types, but maybe eventually open this up to allow for linked symbols to be used...

   - Type Checking :: Callable
    - Currently, the typechecker handles function calls without ever ensuring teh function has been assigned to., This is the feature of the language we don't do for external function calls, so basically just ensure that we have a control flow during type checking between eternal and non-external function calls. But for now do nothing more than what we've been doing with function type assurance and argument/parameter type matching. 


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

  * **Modular Code Generation:** We'll create a `code-gen` structure that utilizes **function pointers** to modularize the code generation process. This will move away from large `switch` statements, allowing different backends to define their specific code generation behaviors consistently.
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

- TODO: [OPTIMIZATION] Substract local stack allocation at beginning of function

- TODO: Write TextMate grammar for VS integration
  - Resources:
    - MSDN :: https://learn.microsoft.com/en-us/visualstudio/ide/adding-visual-studio-editor-support-for-other-languages?view=vs-2022
    - Article :: https://www.apeth.com/nonblog/stories/textmatebundle.html
    - Example Grammar :: https:://macromates.com/manual/en/language_grammars

  - TODO: This example should work, but it does not!!!
    - The following program returns 5 (access denied on Windows), instead of the correct answer (which is 8).
```
defun gcd_euclid (a : integer, b : integer) : integer {
    if a = b {
        a
    } else {
        debug_testing : integer = 
        if a < b {
          gcd_euclid(a, b - a)
        } else {
           gcd_euclid(a - b, b)
        }
      debug_testing
    }
}

gcd_euclid(88, 32)
```

  - [x] Fix lambda parsing!
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

    Final thoughts: Functions need to be defined as type in the type system, and not this foreign thing. This will allow functions to be passed as parameters and such, while still being completely type checked. I think we need to store a flat list of all function body definitions and ensure that no duplicates are allowed, even in the case of different scopes. This allows direct use of the function symbol as an assembly address and prevents having to mangle. Wait I don't think this is needed, and as long as type signature matches then we can ensure that even though we did separate type checking we can still generate code exactly the same (I think... Oh Lord).

    So basically, when creating a function, create a context and everything. We need to allow a function with no body to be defined, in the hopes that it will be assigned some value before it is ever called. We should eventually ensure this.

    When type-checking a function body, all we need is to enter the proper context. The context should contain all variables, types, etc in local scope, including parameters.

    When type-checking a function call, all we need is to lookup the function name as a variable and get it's type.

- [x] Remove global FUNCTION optimization in code-gen
  - Whilst it does make the program an unnoticeable amount faster, it also breaks if any `if` expression lies between global function definitions...

  - [x] Fix messy git work tree
      - We already have a gitignore to ignore all build type files / folders and we have moved all examples to `examples` folder anyway so its just `src/`
    
    - [x] Have better build instructions for other toolchains
      - First of all, instead of using GNU Binutils (`as` and `ld`), most people probably don't care about that and just want to run `gcc`. Luckily with GCC, it's really, really easy.

      I had luck getting clang to produce working executables in a very straightforward manner as well, so if we can reproduce that today then let's definitely add that in there aas well.

   - [x] Change the type system surrounding pointers entirely
    - Switch from pointer nodes with children to nodes having a pointer flag and pointer count (or pointer flag is the pointer count non-zero). This will *greatly* simplify our typechecking, code-gen, allocation, etc.

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
  
  - [x] TODO / FIX: Fix `if` context handling during code-gen
    - One thing that we are definitely not handling properly is contexts of `if` expressions during code-gen.

  * [ ] **Division and Bit-Shifting Operators:** Implement division and bit-shifting binary operators to enable more powerful examples like `sqrt` and `perfect_square`.
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


- [ ] TODO: Implement repetitive control flow...

- [x] TODO: Consolidate `current_token`, `token_length`, and `end` into `ParsingState`
  - These current are passed all around the parser as arguments to all sorts of functions, and I think it could be simplified by bundling these arguments together into the one thing they represent.

- [ ] TODO: Separate contexts from scopes (or fix this problem in some other way)...

- [ ] TODO: Create new binary operator node value that is easier in code-gen...

- [x] TODO: Implement division and bit shifting binary operators...

- [ ] TODO: Support quick function declarations syntax...

- [ ] TODO: AST optimization, code-gen optimization, etc. etc...
    - At a glance, it seems that we could do much better at daisy-chaining result registers of expressions. As a prime example, we could use an integer literal directly in the instruction, rather than loading it into a register before using that register wherever the integer is needed. This would be obvious in function call parameter pushing.
```
  ;;#; Function Call: "foo"
  pushq %rax
  ;;#; Variable Access: "sixty_nine"
  mov sixty_nine(%rip), %rax
  pushq %rax
  ;;#; Variable Access: "foo"
  mov foo(%rip), %rax
  call *%rax
  add $8, %rsp
  add $8, %rsp
```

Another thing we could fix up is pushing/popping all callee-saved registers, even when they aren't used. It makes simple functions, ones that just return a single integer, for example, a bit silly in how complex the code generated is.

```
  ;;#; Function
  jmp after.L0
.L0:
  push %rbp
  mov $rsp, %rbp
  sub $32, %rsp
  push %rbx
  push %rsi
  push %rdi
  ;;#; INTEGER: 69
  mov $69, %rax
  pop %rbx
  pop %rsi
  pop %rdi
  add $32, %rsp
  pop %rbp
  ret
after.L0:
  lea .L0(%rip), %rax
```

 One thing I'm wondering is how to figure out when an expression may be used as an operand, and when it must be code-genned into a result register... After some thought, it seems that this must be done during code-gen, with specific checks in certain expression types to attempt to create the most efficient program possible. All of these checks must also ensure they respect the user's specific optimization level.

- [ ] TODO: Esolang exactly like C but only with a single type: `bit`
  - This would allow use to do something like:
    - `bit[32] main(bit[32] argc, bit[64] argv)`
```c
bit* a = malloc(8);
bit++
```

- [ ] TODO: Add debug information using CFI directives...

- [ ] TODO: Compiler that enforces certain code style...

- [ ] TODO: Vimscript Syntax plugin
  - [VIM Syntax Plugins Support](https://thoughtbot.com/blog/writing-vim-syntax-plugins)

- [ ] FIXME: When out of scratch registers in code-gen, use stack or something...

- [ ] FIXME: How do we deal with syntax of `*=` and `-=`. etc??? 
  - We could either have different AST nodes that are code-genned differently or we could have them construct and composite existing AST nodes (BINARY OPERATOR AND REASSIGN). 

  - Coming back to this, I really like just constructing two nodes for these specific binary operator cases. I wonder if we could even generalize, and have any binary operator before an `=` do a reassignment thing. Doesn't really work with `<=` or `>=`though...

- [ ] TODO: Convert `{}` expression lists into an expression itself.

- [ ] TODO: Have the compiler able to collect TODO comments and things from source...

- [ ] FIXME: Errors that don't suck:
  - This means errors that can have references to the original source code. Also errors that can have filepaths, line/column numbers for relevant source code file positions.
  
  So with these two things, we should be good to go on our errors, or at least have a good start: 
    - Print relevant source code span
      - To do this, we are going to have to keep track of a AST node's token span, which will require quiet some work in the parser. Without this, there wouldn't really be a way to know where the AST node came from. I guess we are just going to have to add a new member to the Node structure that contains source code span information; we could quiet literally store a `Token`, as just a string span.

  - File, Line, and Column reference

- [x] TODO: Use `sete` in `x86_64` backend for comparisons
  - This would be much more efficient than our 4-scratch-registers-hogging current situation.

- [x] TODO: Pointers example is very, very borked ~:/~
  - I don't know what happened, but it breaks VERY badly. This was fixed by updating the compiler.

- [ ] TODO: Separate codegen into multiple files by platform

