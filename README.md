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
You can define a new grammar and generate a C parser from it. As an example,
let's create a **Reverse Polish Notation (RPN) converter** that transforms
infix expressions like `1+2*3` into postfix notation `1 2 3 * +`.

1. Write a grammar file `rpn.def`.
2. Generate a C parser:

```sh
./a.out rpn.def rpn.c
gcc rpn.c -Wno-pointer-sign -o rpn
```

3. Test it with some input:

```sh
echo "1+2*3" | ./rpn
# Output: 1 2 3 * +

echo "(1+2)*3" | ./rpn
# Output: 1 2 + 3 *
```

## Example Grammar: `rpn.def`
Below is a complete `rpn.def` that converts infix arithmetic expressions to
Reverse Polish Notation. The key insight is that by changing the order of
`print()` and `call()`, we can output operators *after* their operands.

```def
START(RPN)
RPN     : EXPR { call(1); print("\n"); }
;

EXPR    : TERM "+" EXPR     { call(1); print(" "); call(2); print(" +"); }
        | TERM "-" EXPR     { call(1); print(" "); call(2); print(" -"); }
        | TERM              { call(1); }
;

TERM    : FACTOR "*" TERM   { call(1); print(" "); call(2); print(" *"); }
        | FACTOR "/" TERM   { call(1); print(" "); call(2); print(" /"); }
        | FACTOR            { call(1); }
;

FACTOR  : "(" EXPR ")"      { call(1); }
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

The grammar handles operator precedence naturally: `*` and `/` bind tighter
than `+` and `-` because they are parsed at the `TERM` level, while `+` and `-`
are parsed at the `EXPR` level.

## Notes
- Most changes to output behavior should be made in the `.def` files.
- Runtime mechanics (backtracking, parse trees, output plumbing) live in `comcom.h`.

---

## The Mini Language

This project includes a complete example language called **mini**.
It demonstrates how the same grammar can have different backends:
one targeting C, another targeting x86-64 assembly.

### Grammar

```
PROGRAM   := STATEMENT*

STATEMENT := "var" NAME
           | "set" NAME EXPR
           | "input" NAME
           | "out" EXPR
           | "if" COND BLOCK
           | "while" COND BLOCK

BLOCK     := STATEMENT* "end"

COND      := EXPR ">" EXPR
           | EXPR "<" EXPR
           | EXPR "=" EXPR

EXPR      := TERM "+" TERM
           | TERM "-" TERM
           | TERM "*" TERM
           | TERM "/" TERM
           | TERM

TERM      := NAME | NUMBER

NAME      := [a-z]+
NUMBER    := [0-9]+
```

### Example Program: Fibonacci

```
var n
var i
var a
var b
var t

input n

set a 0
set b 1
set i 1

while i < n
set t a + b
set a b
set b t
set i i + 1
end

out b
```

### Two Backends

The same mini language has two backend implementations:

| Definition File | Target | Type |
|-----------------|--------|------|
| `mini.def` | C source code | Transpiler |
| `mini-asm.def` | x86-64 assembly | Compiler |

```
                        ┌─────────────┐
                        │  mini.def   │ → C Transpiler
                        └─────────────┘
                              ↑
┌──────────────┐        ┌───────────┐
│ program.mini │   →    │   a.out   │  (Compiler Compiler)
└──────────────┘        └───────────┘
                              ↓
                        ┌─────────────┐
                        │mini-asm.def │ → x86-64 Compiler
                        └─────────────┘
```

### Using mini.def (C Transpiler)

```sh
# Build the transpiler
./a.out mini.def mini.c
gcc mini.c -Wno-pointer-sign -o mini

# Transpile mini to C, then compile and run
./mini < program.mini > program.c
gcc program.c -o program
./program
```

### Using mini-asm.def (x86-64 Compiler)

```sh
# Build the compiler
./a.out mini-asm.def mini-asm.c
gcc mini-asm.c -Wno-pointer-sign -o mini-asm

# Compile to assembly, then assemble and run (Linux x86-64)
./mini-asm < program.mini > program.s
gcc program.s -o program -no-pie
./program
```

---

## Appendix: File Reference

### Core Files

| File | Description |
|------|-------------|
| `t0.def` | Grammar definition for the compiler compiler itself |
| `t3.out.c` | Generated C source of the compiler compiler |
| `comcom.h` | Runtime library (parsing, backtracking, tree construction) |

### Mini Language Files

| File | Description |
|------|-------------|
| `mini.def` | Mini language grammar → C transpiler |
| `mini.c` | Generated transpiler source (from mini.def) |
| `mini-asm.def` | Mini language grammar → x86-64 compiler |
| `mini-asm.c` | Generated compiler source (from mini-asm.def) |
| `program.mini` | Sample program (Fibonacci calculator) |

### Other Examples

| File | Description |
|------|-------------|
| `rpn.def` | Infix to Reverse Polish Notation converter (grammar) |
| `rpn.c` | Generated RPN converter source (from rpn.def) |

### Build Summary

```sh
# Build compiler compiler
gcc t3.out.c -Wno-pointer-sign -o a.out

# Verify self-reproduction
./a.out t0.def t4.out.c && diff t3.out.c t4.out.c

# Build mini transpiler
./a.out mini.def mini.c && gcc mini.c -Wno-pointer-sign -o mini

# Build mini-asm compiler
./a.out mini-asm.def mini-asm.c && gcc mini-asm.c -Wno-pointer-sign -o mini-asm
```

---

## Credits

Original source code from Interface Magazine 1995/12, CQ Publishing Company.

---
Enjoy exploring how a compiler can define itself.
