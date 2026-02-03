# CompilerCompiler

## Overview
This project is a tiny **compiler compiler**: a tool that reads a grammar definition and
produces a C parser/compiler for that grammar.

You can think of a compiler compiler as a "compiler generator." Instead of hand-writing a
parser in C, you describe the grammar in a compact notation, and the tool emits the C code
that recognizes and processes that grammar.

## The Self-Referential Story
This repository is special because it is **self-referential**.

1. The file `t0.def` defines the grammar of the compiler compiler itself.
2. From that definition, we can create (by hand) the corresponding generated C source,
   which is stored as `t3.out.c`.
3. When you compile `t3.out.c`, you get the executable `a.out`.
4. If you run `a.out` on `t0.def`, it generates a new file `t4.out.c`.
5. `t4.out.c` is **bit-for-bit identical** to `t3.out.c`.

That is the mind‑bending part: the grammar `t0.def` defines **the compiler compiler itself**,
and the generated compiler can reproduce its own source code.

## Key Files
- `t0.def` — grammar definition that *describes this compiler compiler*.
- `t3.out.c` — the hand‑crafted C implementation corresponding to `t0.def`.
- `comcom.h` — runtime library used by all generated parsers.


## Reproduce the Self-Generation
Run the following commands to see the self-generation in action:

```sh
gcc t3.out.c -Wno-pointer-sign -o a.out
./a.out t0.def t4.out.c
diff t3.out.c t4.out.c
# (no differences)
```

If `diff` shows no differences, the self-reproduction succeeded.

## Why This Is Interesting
- **Self-reference:** a system that defines itself is rare and fascinating.
- **Educational value:** it demonstrates how grammars become programs.
- **Compactness:** the runtime (`comcom.h`) is small and the output is simple C.

## Getting Started With Your Own Grammar
You can define a new grammar and generate a C parser from it. As an example:

1. Write a grammar file `calc.def`.
2. Generate a C parser:

```sh
./a.out calc.def calc.c
gcc calc.c -Wno-pointer-sign -o calc
```

3. Test it with some input:

```sh
printf "(10 + 5) * 3\n" | ./calc
```

## Example Grammar: `calc.def`
Below is a complete `calc.def` you can use as a starting point. It defines a tiny
arithmetic language with `+`, `-`, `*`, `/`, and parentheses, and it prints the
parsed expression back out in a structured way.

```def
START(CALC)
CALC    : EXPR { print("Result: "); call(1); print("\n"); }
;

EXPR    : TERM "+" EXPR     { call(1); print(" + "); call(2); }
        | TERM "-" EXPR     { call(1); print(" - "); call(2); }
        | TERM              { call(1); }
;

TERM    : FACTOR "*" TERM   { call(1); print(" * "); call(2); }
        | FACTOR "/" TERM   { call(1); print(" / "); call(2); }
        | FACTOR            { call(1); }
;

FACTOR  : "(" EXPR ")"      { print("("); call(1); print(")"); }
        | NUMBER            { call(1); }
;

NUMBER  : DIGIT+NUMBER      { call(1); call(2); }
        | DIGIT             { call(1); }
;

DIGIT   : "0" { print("0"); }
        | "1" { print("1"); }
        | "2" { print("2"); }
        | "3" { print("3"); }
        | "4" { print("4"); }
        | "5" { print("5"); }
        | "6" { print("6"); }
        | "7" { print("7"); }
        | "8" { print("8"); }
        | "9" { print("9"); }
;
END
```

## Notes
- Most changes to output behavior should be made in `t0.def`.
- Runtime mechanics (backtracking, parse trees, output plumbing) live in `comcom.h`.

---
Enjoy exploring how a compiler can define itself.
