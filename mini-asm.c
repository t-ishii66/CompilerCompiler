#include "comcom.h"
void _MINI(int e);
void _STMTS(int e);
void _STMT(int e);
void _BLOCK(int e);
void _COND(int e);
void _EXPR(int e);
void _TERM(int e);
void _NAME(int e);
void _NUM(int e);
void _ALPHA(int e);
void _DIGIT(int e);
void firstcall(int e) { _MINI(e); }

 void _MINI(int e) {
{ _STMTS(E); mknode(_f1);}
 }

 void _STMTS(int e) {
 if (try()) { _STMT(E); _STMTS(E); mknode(_f2); ok(); }
  else { _STMT(E); mknode(_f3);}
 }

 void _STMT(int e) {
 if (try()) { check("var"); _NAME(E); mknode(_f4); ok(); }
  else  if (try()) { check("set"); _NAME(E); _EXPR(E); mknode(_f5); ok(); }
  else  if (try()) { check("input"); _NAME(E); mknode(_f6); ok(); }
  else  if (try()) { check("out"); _EXPR(E); mknode(_f7); ok(); }
  else  if (try()) { check("if"); _COND(E); _BLOCK(E); mknode(_f8); ok(); }
  else { check("while"); _COND(E); _BLOCK(E); mknode(_f9);}
 }

 void _BLOCK(int e) {
 if (try()) { _STMT(E); _BLOCK(E); mknode(_f10); ok(); }
  else { check("end"); mknode(_f11);}
 }

 void _COND(int e) {
 if (try()) { _EXPR(E); check(">"); _EXPR(E); mknode(_f12); ok(); }
  else  if (try()) { _EXPR(E); check("<"); _EXPR(E); mknode(_f13); ok(); }
  else { _EXPR(E); check("="); _EXPR(E); mknode(_f14);}
 }

 void _EXPR(int e) {
 if (try()) { _TERM(E); check("+"); _TERM(E); mknode(_f15); ok(); }
  else  if (try()) { _TERM(E); check("-"); _TERM(E); mknode(_f16); ok(); }
  else  if (try()) { _TERM(E); check("*"); _TERM(E); mknode(_f17); ok(); }
  else  if (try()) { _TERM(E); check("/"); _TERM(E); mknode(_f18); ok(); }
  else { _TERM(E); mknode(_f19);}
 }

 void _TERM(int e) {
 if (try()) { _NAME(E); mknode(_f20); ok(); }
  else { _NUM(E); mknode(_f21);}
 }

 void _NAME(int e) {
 if (try()) { _ALPHA(E); combine(); _NAME(E); mknode(_f22); ok(); }
  else { _ALPHA(E); mknode(_f23);}
 }

 void _NUM(int e) {
 if (try()) { _DIGIT(E); combine(); _NUM(E); mknode(_f24); ok(); }
  else { _DIGIT(E); mknode(_f25);}
 }

 void _ALPHA(int e) {
 if (try()) { check("a"); mknode(_f26); ok(); }
  else  if (try()) { check("b"); mknode(_f27); ok(); }
  else  if (try()) { check("c"); mknode(_f28); ok(); }
  else  if (try()) { check("d"); mknode(_f29); ok(); }
  else  if (try()) { check("e"); mknode(_f30); ok(); }
  else  if (try()) { check("f"); mknode(_f31); ok(); }
  else  if (try()) { check("g"); mknode(_f32); ok(); }
  else  if (try()) { check("h"); mknode(_f33); ok(); }
  else  if (try()) { check("i"); mknode(_f34); ok(); }
  else  if (try()) { check("j"); mknode(_f35); ok(); }
  else  if (try()) { check("k"); mknode(_f36); ok(); }
  else  if (try()) { check("l"); mknode(_f37); ok(); }
  else  if (try()) { check("m"); mknode(_f38); ok(); }
  else  if (try()) { check("n"); mknode(_f39); ok(); }
  else  if (try()) { check("o"); mknode(_f40); ok(); }
  else  if (try()) { check("p"); mknode(_f41); ok(); }
  else  if (try()) { check("q"); mknode(_f42); ok(); }
  else  if (try()) { check("r"); mknode(_f43); ok(); }
  else  if (try()) { check("s"); mknode(_f44); ok(); }
  else  if (try()) { check("t"); mknode(_f45); ok(); }
  else  if (try()) { check("u"); mknode(_f46); ok(); }
  else  if (try()) { check("v"); mknode(_f47); ok(); }
  else  if (try()) { check("w"); mknode(_f48); ok(); }
  else  if (try()) { check("x"); mknode(_f49); ok(); }
  else  if (try()) { check("y"); mknode(_f50); ok(); }
  else { check("z"); mknode(_f51);}
 }

 void _DIGIT(int e) {
 if (try()) { check("0"); mknode(_f52); ok(); }
  else  if (try()) { check("1"); mknode(_f53); ok(); }
  else  if (try()) { check("2"); mknode(_f54); ok(); }
  else  if (try()) { check("3"); mknode(_f55); ok(); }
  else  if (try()) { check("4"); mknode(_f56); ok(); }
  else  if (try()) { check("5"); mknode(_f57); ok(); }
  else  if (try()) { check("6"); mknode(_f58); ok(); }
  else  if (try()) { check("7"); mknode(_f59); ok(); }
  else  if (try()) { check("8"); mknode(_f60); ok(); }
  else { check("9"); mknode(_f61);}
 }
void _f1(int n, int a) {print(".text\n");print(".globl main\n");print("main:\n");print("    pushq %rbp\n");print("    movq %rsp, %rbp\n");call(1);print("    xorl %eax, %eax\n");print("    popq %rbp\n");print("    ret\n");spoolOpen();
print(".data\n");print("fmt_out: .string \"%ld\\n\"\n");print("fmt_in: .string \"%ld\"\n");spoolClose();
}
void _f2(int n, int a) {call(1);call(2);}
void _f3(int n, int a) {call(1);}
void _f4(int n, int a) {spoolOpen();
spoolOpen();
print("_");call(1);print(": .quad 0\n");spoolClose();
spoolClose();
}
void _f5(int n, int a) {call(2);print("    movq %rax, _");call(1);print("(%rip)\n");}
void _f6(int n, int a) {print("    leaq _");call(1);print("(%rip), %rsi\n");print("    leaq fmt_in(%rip), %rdi\n");print("    xorl %eax, %eax\n");print("    call scanf\n");}
void _f7(int n, int a) {call(1);print("    movq %rax, %rsi\n");print("    leaq fmt_out(%rip), %rdi\n");print("    xorl %eax, %eax\n");print("    call printf\n");}
void _f8(int n, int a) {call(1);print("    testq %rax, %rax\n");print("    jz .Lif");genNum();print("\n");call(2);print(".Lif");genNum();print(":\n");}
void _f9(int n, int a) {print(".Lws");genNum();print(":\n");call(1);print("    testq %rax, %rax\n");print("    jz .Lwe");genNum();print("\n");call(2);print("    jmp .Lws");genNum();print("\n");print(".Lwe");genNum();print(":\n");}
void _f10(int n, int a) {call(1);call(2);}
void _f11(int n, int a) {print("");}
void _f12(int n, int a) {call(1);print("    pushq %rax\n");call(2);print("    popq %rbx\n");print("    cmpq %rax, %rbx\n");print("    setg %al\n");print("    movzbq %al, %rax\n");}
void _f13(int n, int a) {call(1);print("    pushq %rax\n");call(2);print("    popq %rbx\n");print("    cmpq %rax, %rbx\n");print("    setl %al\n");print("    movzbq %al, %rax\n");}
void _f14(int n, int a) {call(1);print("    pushq %rax\n");call(2);print("    popq %rbx\n");print("    cmpq %rax, %rbx\n");print("    sete %al\n");print("    movzbq %al, %rax\n");}
void _f15(int n, int a) {call(1);print("    pushq %rax\n");call(2);print("    popq %rbx\n");print("    addq %rbx, %rax\n");}
void _f16(int n, int a) {call(1);print("    pushq %rax\n");call(2);print("    movq %rax, %rbx\n");print("    popq %rax\n");print("    subq %rbx, %rax\n");}
void _f17(int n, int a) {call(1);print("    pushq %rax\n");call(2);print("    popq %rbx\n");print("    imulq %rbx, %rax\n");}
void _f18(int n, int a) {call(1);print("    pushq %rax\n");call(2);print("    movq %rax, %rbx\n");print("    popq %rax\n");print("    cqto\n");print("    idivq %rbx\n");}
void _f19(int n, int a) {call(1);}
void _f20(int n, int a) {print("    movq _");call(1);print("(%rip), %rax\n");}
void _f21(int n, int a) {print("    movq $");call(1);print(", %rax\n");}
void _f22(int n, int a) {call(1);call(2);}
void _f23(int n, int a) {call(1);}
void _f24(int n, int a) {call(1);call(2);}
void _f25(int n, int a) {call(1);}
void _f26(int n, int a) {print("a");}
void _f27(int n, int a) {print("b");}
void _f28(int n, int a) {print("c");}
void _f29(int n, int a) {print("d");}
void _f30(int n, int a) {print("e");}
void _f31(int n, int a) {print("f");}
void _f32(int n, int a) {print("g");}
void _f33(int n, int a) {print("h");}
void _f34(int n, int a) {print("i");}
void _f35(int n, int a) {print("j");}
void _f36(int n, int a) {print("k");}
void _f37(int n, int a) {print("l");}
void _f38(int n, int a) {print("m");}
void _f39(int n, int a) {print("n");}
void _f40(int n, int a) {print("o");}
void _f41(int n, int a) {print("p");}
void _f42(int n, int a) {print("q");}
void _f43(int n, int a) {print("r");}
void _f44(int n, int a) {print("s");}
void _f45(int n, int a) {print("t");}
void _f46(int n, int a) {print("u");}
void _f47(int n, int a) {print("v");}
void _f48(int n, int a) {print("w");}
void _f49(int n, int a) {print("x");}
void _f50(int n, int a) {print("y");}
void _f51(int n, int a) {print("z");}
void _f52(int n, int a) {print("0");}
void _f53(int n, int a) {print("1");}
void _f54(int n, int a) {print("2");}
void _f55(int n, int a) {print("3");}
void _f56(int n, int a) {print("4");}
void _f57(int n, int a) {print("5");}
void _f58(int n, int a) {print("6");}
void _f59(int n, int a) {print("7");}
void _f60(int n, int a) {print("8");}
void _f61(int n, int a) {print("9");}
