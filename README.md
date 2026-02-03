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
- Most changes to output behavior should be made in `t0.def`.
- Runtime mechanics (backtracking, parse trees, output plumbing) live in `comcom.h`.

---

## Advanced Topic: Building Your Own Language

For those who want to go further, you can use this compiler compiler to create
your own small programming language that compiles to C.

### Challenge: Create a "mini" Language

Try creating a simple language with the following syntax:

```
set x 5
set y 10
out x + y
```

This should compile to C code like:

```c
#include <stdio.h>
int main(){
int x=5;
int y=10;
printf("%d\n",x+y);
return 0;
}
```

### How It Works

Just like `rpn.def` defines an RPN converter, you will create `mini.def` that
defines a **translator from mini language to C**. The compiler compiler reads
`mini.def` and generates `mini.c` — a C program that can parse the mini language
and output C code.

The workflow is:
```
mini.def  --[a.out]-->  mini.c  --[gcc]-->  mini  (the mini compiler)
program.mini  --[mini]-->  program.c  --[gcc]-->  program  (executable)
```

### Hints

1. **Structure your grammar** with these rules:
   - `MINI` — the top-level rule that wraps everything in `main()`
   - `STMTS` — a sequence of statements
   - `STMT` — either a `set` statement or an `out` statement
   - `EXPR` — an expression (variable, number, or binary operation)

2. **Use `print()` to emit C code**:
   - For `set x 5`, emit `int x=5;`
   - For `out <expr>`, emit `printf("%d\n", <expr>);`

3. **The key insight**: Your `.def` file defines a *translator* from your
   language to C. Each grammar rule's action should `print()` the corresponding
   C code.

### Testing Your Compiler

```sh
# 1. Generate the compiler
./a.out mini.def mini.c
gcc mini.c -Wno-pointer-sign -o mini

# 2. Write a program in your language
echo 'set x 5
set y 10
out x + y' > program.mini

# 3. Compile to C, then compile and run
./mini < program.mini > program.c
gcc program.c -o program
./program
# Output: 15
```

A working `mini.def` is included in this repository as a reference solution.

---
Enjoy exploring how a compiler can define itself.
