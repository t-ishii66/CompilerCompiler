CompilerCompiler
================

Self Extendable Compiler Compiler


comcom.h is header file , and it contains main func.
t0.def is the definition of *THIS* Compiler Compiler.
t3.out.c is the C code image of *THIS* Compiler Compiler.

-----------------------------------------------
How to use this software.

$ gcc t3.out.c
$ ./a.out t0.def t4.out.c

then, t4.out.c is generated.
t4.out.c is exactly same as t3.out.c .

-----------------------------------------------
What is t3.out.c

a.out of t3.out.c is a Compiler Compier.
So, you can use this a.out like yacc/bison.
You can also make a new Compiler by a.out.
One of the souce code for a.out is t0.def.
t0.def is the definition of a.out.  a.out is defined by t0.def.
So, a.out and t0.def can generate source code of a.out.
This is t3.out.c.

-----------------------------------------------
Example  "THIS IS A PEN Analyzer"

"THIS IS A PEN Analyzer" can analyze a text file contains
"THIS IS A PEN" text string or not.

The definition of this analyzer is sample.def.


$ ./a.out sample.def sample.c
$ gcc -o sample sample.c

Now, you should make a definition file .

$ cat user.txt
THIS IS A PENCIL

$ ./sample user.txt user.out
$ cat user.out
-this--is--pen-finish!




Enjoy.

