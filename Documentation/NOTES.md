# AlyCompiler NOTES

1. We need some list of identifiers that are known, ideally with type information as well as the literal `value/memory` address or something. These need to be scoped (i.e. nested) to allow for shadowing of global identifiers within functions for example. This may even allow use to implement `let`, which would be cool.


## A simple linked-list representation of scoped identifiers

```plaintext
[  [  ID -> TYPE  ], [  "a" -> integer ]  ]
```
