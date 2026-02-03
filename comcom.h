/*
	Original Source code is written in Interface 1995/12 CQ-publishing 
	company. www.cqpub.co.jp

	This sorce code is drived version.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>

typedef unsigned char	byte;
typedef unsigned int	uint;

#define TRUE	1
#define FALSE	0

/* Forward declarations */
void back(void);
void spoolOutput(void);
void firstcall(int e);

/* Forward declarations for all parsing functions */
void _COMCOM(int e);
void _STMTS(int e);
void _STMT(int e);
void _RULES(int e);
void _RULE(int e);
void _TERMS(int e);
void _TERM(int e);
void _OUTS(int e);
void _OUT(int e);
void _NAME(int e);
void _QSTR(int e);
void _QSTR1(int e);
void _CHR(int e);
void _MCHR(int e);
void _NUMS(int e);
void _ALPH(int e);
void _SALPH(int e);
void _NUM(int e);
void _MARK(int e);

static FILE* FI = 0;		/* input file */
static FILE* FO = 0;		/* output file */
static FILE* FS = 0;		/* output file(additional) */

static int K = TRUE;		/* K=FALSE:skip space */
static int F = 0;		/* F=1: output to spool */
static int D = 0;		/* D: auto generation number */

/* input file contents */
#define IB_SIZE	5000
static byte IB[IB_SIZE];
static int I = 0;

/* back tarck stack */
#define BS_SIZE	10000
struct {			/* try()-ok() stack */
	jmp_buf	j;		/* jump buffer used by try() */
	int	e;		/* */
	int	t;		/* */
	int	i;		/* */
	int	k;		/* */
} BS[BS_SIZE];
static int B = 0;

/* parse tree stack */
#define ES_SIZE	10000
static int ES[ES_SIZE];
static int E = 0;

/* n-tree stack */
#define TS_SIZE	20000
union {
	int	(*f)();
	int	n;
} TS[TS_SIZE];
static int T = 0;

static long maxI = 0;
static long maxO = 0;
static long maxS = 0;
static long cntB = 0;
static long cntI = 0;
static int maxB = 0;
static int maxE = 0;
static int maxT = 0;

void report()
{
	printf("source size %8ld\n", maxI);
	printf("object size %8ld\n", maxO);
	printf("spool  size %8ld\n", maxS);
	printf("back  track %8ld\n", cntB);
	printf("source read %8ld\n", cntI);
	printf("BS max size %8d\n", maxB);
	printf("ES max size %8d\n", maxE);
	printf("TS max size %8d\n", maxT);
}

void stop(char* s)
{
	spoolOutput();
	fclose(FS);
	fclose(FO);
	fclose(FI);
	unlink("SPOOL.$$$");
	report();
	printf("\n%s\n", s);
	exit(0);
}
void abend(char* s)
{
	printf("\n### %s error ###\n", s);
	stop("** abnormal end **");
}

void init(int argc, char* argv[])
{
	uint	c;
	printf("source file = %s\n", argv[1]);
	printf("object file = %s\n", argv[2]);

	FI = fopen(argv[1], "r");
	if (!FI) abend("input file open");

	FO = fopen(argv[2], "w");
	if (!FO) abend("output file open");

	FS = fopen("SPOOL.$$$", "w");
	if (!FS) abend("spool file open");

	printf("\n--- source list ---\n");
	while (!feof(FI)) {
		c = fgetc(FI);
		if (maxI >= IB_SIZE)
			abend("IB over");
		IB[maxI ++] = c;
	}
}

uint fileInput()
{
	static int i = 0;
	cntI ++;
	if (i == I && i < maxI) 
		putchar(IB[i ++]);
	return (uint)((I < maxI) ? IB[I ++] : EOF);
}

#define combine() K=FALSE

void skipSpace(byte s)
{
	uint c;
	if (!K) {
		K = TRUE;
		return;
	}
	while ((c = fileInput()) != EOF && (byte)c != s && isspace(c))
		;
	-- I;
}

void check(const byte* s)
{
	skipSpace(*s);
	while (*s) {
		char	c = fileInput();
		if (*s ++ != c)
			back();
	}
}

#define spoolOpen()	 F=1
#define spoolClose()	 F=0

void print(const byte* s)
{
	int z = strlen((const char*)s);
	if (F == 0) {
		fputs((const char*)s, FO); maxO += z;
	} else {
		fputs((const char*)s, FS); maxS += z;
	}
}

#define genNum()	genNumber(&a)

void genNumber(uint* d)
{
	static char s[6];
	if (*d == 0)
		*d = ++ D;
	sprintf(s, "%u", *d);
	print((byte*)s);
}

void spoolOutput()
{
	uint c;
	fclose(FS);
	FS = fopen("SPOOL.$$$", "r");
	while (!feof(FS)) {
		c = fgetc(FS);
		if (c == EOF)
			break;
		// display source
		putc(c, FO);
	}
	maxO += maxS;
}

#define try() save(),!setjmp((BS[B++].j))
#define ok() B--

void save()
{
	if (B >= BS_SIZE)
		abend("BS over");
	BS[B].e = E;
	BS[B].t = T;
	BS[B].i = I;
	BS[B].k = K;
	if (B >= maxB)
		maxB = B + 1;
}

void back()
{
	if (--B < 0)
		abend("syntax");
	E = BS[B].e;
	T = BS[B].t;
	I = BS[B].i;
	K = BS[B].k;
	++ cntB;
	longjmp(BS[B].j, 1);
}

void storeFunc(void (*f)(int, int))
{
	if (T > TS_SIZE)
		abend("TS over");
	TS[T ++].f = (int (*)())f;
	if (T > maxT)
		maxT = T;
}

void storeInt(int n)
{
	if (T >= TS_SIZE)
		abend("TS over");
	TS[T ++].n = n;
	if (T > maxT)
		maxT = T;
}

#define mknode(f) { void f(int,int); makeNode(f, e); }

void makeNode(void (*n)(int,int), int e)
{
	int i, t = T;
	storeFunc(n);
	storeInt(E - e);
	for (i = e ; i < E ; ++ i) {
		storeInt(ES[i]);
	}
	E = e;
	if (E >= ES_SIZE)
		abend("ES over");
	ES[E ++] = t;
	if (E > maxE)
		maxE = E;
}

#define call(a)		call2(n, a)	

void call2(int n, int b)
{
	int m;
	if (b > TS[n + 1].n || b < 1)
		abend("branch no");

	m = (TS[n + 1 + b].n);
	((void (*)(int, int))TS[m].f)(m, 0);
}

void exec()
{
	int t;
	if (E != 1)
		abend("exec");
	t = ES[-- E];
	((void (*)(int, int))TS[t].f)(t, 0);
}

int main(int argc, char* argv[])
{
	if (argc != 3) {
		printf(" Usage : %s file.def file.c e\n", argv[0]);
		exit(1);
	}

	init(argc, argv);
	firstcall(E);
	exec();
	stop("** normal end **");
	return 0;
}
