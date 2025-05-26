# AlyCompiler NOTES

1. We need some list of identifiers that are known, ideally with type information as well as the literal `value/memory` address or something. These need to be scoped (i.e. nested) to allow for shadowing of global identifiers within functions for example. This may even allow use to implement `let`, which would be cool.


## A simple linked-list representation of scoped identifiers

```plaintext
[  [  ID -> TYPE  ], [  "a" -> integer ]  ]
```

## Example AST Tree Representation

This tree below shows how Aly will the AST with variable definitions, reassignments, type definitions, unary, and ternary operators.

```plaintext
================================
        ROOT
         │
         ├── /
         │    ├── integer
         │    │     └── 34
         │    │
         │    ├── +
         │    │
         │    └── integer
         │          └── 35

        ROOT-x
         │
         ├── /
         │    └── +
         │         ├── integer
         │         │     └── 34
         │         │
         │         └── integer
         │               └── 35

        ROOT-x
         │
         ├── ?
         │    ├── condition
         │    │
         │    ├── integer
         │    │     └── 69
         │    │
         │    └── integer
         │          └── 420
================================
```