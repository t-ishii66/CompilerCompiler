CompilerCompiler
================

Overview
--------

This project is a compact "compiler compiler" — a tool that reads a formal grammar definition and
produces a C parser/compiler for that grammar. It is self-referential: the grammar that defines the
compiler compiler is included in the repository, and the generated compiler can reproduce its own
source code from that grammar.

Key files
---------
- `comcom.h` — runtime library and helper code used by all generated parsers.
- `t0.def` — the grammar definition that *describes this compiler compiler*.
- `t3.out.c` — a pre-generated C implementation of the compiler compiler. When compiled, the
  resulting executable (`a.out`) can read `.def` files and emit C sources.

Quick reproduction
------------------
To reproduce the self-generation test:

```sh
$ gcc t3.out.c -Wno-pointer-sign -o a.out
$ ./a.out t0.def t4.out.c
$ diff t3.out.c t4.out.c
# (no differences)
```

This demonstrates thaThis demonstrates thaThis demonstrates thaThis demonstrates thaThi the
compiler produces the same `t3.oct.c` source again.compiler produces the same `t3.oct.c` source again.compiler produces the same `t3.oct.c` sourlled a parser generator) transforms a formal grammar into code that
recognizes that grammar. Instead of hanrecognizes that grammar. Instead of hanrecognizes that grammar. Instead of hanrecognizes that age in a higher-level notation and the tool generates the C
implementation for you.

Why this project is interesting
------------------------------
- Self-reference: the project contains a grammar that defines the tool that generates parsers.
- Simplicity: the generator uses a small runtime (`comcom.h`) and a compact output format.
- Educational: it is a good demonstration of metaprogramming and parser generation techniques.

Getting started — a practical example
-------------------------------------

Below is a practical sample showing how you can use the compiler compiler to generate a parser
for arithmetic expressions with correct operator precedence.

1) Write a grammar file `calc.def` (example below).
2) Generate a C parser:

```sh
$ ./a.out calc.def calc.c
$ gcc calc.c -Wno-pointer-sign -o calc
```

3) Use the generated parser on an input file:

```sh
$ printf "(10 + 5) $ printf "(10 + 5) $ printf "(10 + 5) $ printf "(10 + 5) $ printf "(10 + 5) $ printf "(10 + 5) $ printf "(10 + 5) $ printf "(10 + 5) $ printf "(10 + 5) $ printf "(10 + 5) $ example generates a parser that recognizes integer arithmetic with the usual $ printf "(10 + 5) $`/` higher $ printf "(10 + 5) $ printf "(ses.

```
START(CALC)
CALC    : EXPR { print("Result: "); call(1); print("\n"); }
;

EXPR    : TERM "+" EXPR     { call(1); print(" + "); call(3); }
        | TERM "-" EXPR     { call(1); print(" - "); call(3); }
        | TERM              { call(1); }
;

TERM    : FACTOR "*" TERM   { call(1); print(" * "); call(3); }
        | FACTOR "/" TERM   { call(1); print(" / "); call(3); }
        | FACTOR            { call(1); }
;

FACTOR  : "(" EXPR ")"      { print("("); call(2); print(")"); }
        | NUMBER            { call(1); }
;

NUMBER  : DIGIT+NUMBER     NU call(1); call(2); }
        | DIGIT             { call(1); }
;

DIGIT   : "0" { print("0"); }
        | "1" { print("1"); }
                                                                                                                                                                                                                                                                                                                              been updated to build cleanly with m                                                      no-pointe                                                        m passin                                                         ar*` (`byte*`) internally.

Development tips
----------------
- Edit or extend `t0.def` to change how the compiler generator emits C code.
- Use the `<!-- ... // -->` spool blocks- Use the `<!-- ... // -->` spool  code (like forward
  declarations or helper functions) to a separate spool  declarations or helper functions) to  If y  declarations or helper functions) to a sewarning-free under strict compilers, prefer
  adjusting `comcom.h` (the runtime) rather than repeatedly patching generated sources.

License / Attribution
---------------------
This project is derived from code originally published in Interface (1995). See repository files
for details.

Enjoy exploring parser generation!
