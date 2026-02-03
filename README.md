CompilerCompiler
================

<h2>Self Extendable Compiler Compiler</h2>


comcom.h is header file , and it contains main() func.
t0.def is the definition of <b>THIS Compiler Compiler</b>.
t3.out.c is the C source code of <b>THIS Compiler Compiler</b>.

-----------------------------------------------
<h2>How to use this software.</h2>
<pre>
$ gcc t3.out.c
$ ./a.out t0.def t4.out.c
</pre>
then, t4.out.c is generated.
t4.out.c is exactly same as t3.out.c .

-----------------------------------------------
<h2>What is t3.out.c</h2>

a.out generated from t3.out.c is a <b>Compiler Compier</b>.
So, you can use this a.out as a <b>yacc/bison</b>.
<h3>You can also generate a new Compiler by this a.out.</h3>
One of the souce code of the a.out is t0.def.
t0.def is the definition of the self extendable compiler compiler. 
So, the a.out can generate the same source code of a.out by using t0.def .

<pre>
1. t0.def is the definition of the self extendable compiler compiler.
2. The executable code from the t0.def is a.out.
3. a.out is a compiler compiler like a yacc/bison.
4. a.out can generate a C source code by using t0.def.
5. And that C code is the source code of a.out !!
6. You can design a new Compiler by using a.out.
</pre>

-----------------------------------------------
<h2>Example  "THIS IS A PEN Analyzer"</h2>

"THIS IS A PEN Analyzer" can analyze a text file contains
"THIS IS A PEN" text string or not.

The definition of this analyzer is sample.def.

<pre>
START(SAMPLE)
SAMPLE : THIS IS "A" PEN {
		call(1);
		call(2);
		call(3);
		print("finish!"); 
	}
;
THIS	: "THIS" 	{ print("-this-"); }
	| "THAT"	{ print("-that-"); }
;

IS	: "IS" 		{ print("-is-");}
	| "ARE"		{ print("-are-");}
;
PEN	: "PEN" 	{ print("-pen-");}
	| "PENCIL"	{ print("-pencil-");}
;

END
</pre>

<pre>
$ ./a.out sample.def sample.c
$ gcc -o sample sample.c
</pre>

Now, you should make a definition file .

<pre>
$ cat user.txt
THIS IS A PENCIL

$ ./sample user.txt user.out
$ cat user.out
-this--is--pen-finish!
</pre>


Enjoy.

