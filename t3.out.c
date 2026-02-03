#include "comcom.h"

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

void firstcall(int e) { _COMCOM(e); }

 void _COMCOM(int e) {
{ check("START("); _NAME(E); check(")"); _STMTS(E); check("END"); mknode(_f1);}
 }

 void _STMTS(int e) {
 if (try()) { _STMT(E); _STMTS(E); mknode(_f2); ok(); }
  else { _STMT(E); mknode(_f3);}
 }

 void _STMT(int e) {
{ _NAME(E); check(":"); _RULES(E); check(";"); mknode(_f4);}
 }

 void _RULES(int e) {
 if (try()) { _RULE(E); check("|"); _RULES(E); mknode(_f5); ok(); }
  else { _RULE(E); mknode(_f6);}
 }

 void _RULE(int e) {
{ _TERMS(E); check("{"); _OUTS(E); check("}"); mknode(_f7);}
 }

 void _TERMS(int e) {
 if (try()) { _TERM(E); _TERMS(E); mknode(_f8); ok(); }
  else { _TERM(E); mknode(_f9);}
 }

 void _TERM(int e) {
 if (try()) { _NAME(E); mknode(_f10); ok(); }
  else  if (try()) { _QSTR(E); mknode(_f11); ok(); }
  else { check("+"); mknode(_f12);}
 }

 void _OUTS(int e) {
 if (try()) { _OUT(E); _OUTS(E); mknode(_f13); ok(); }
  else { _OUT(E); mknode(_f14);}
 }

 void _OUT(int e) {
 if (try()) { check("call("); _NUMS(E); check(");"); mknode(_f15); ok(); }
  else  if (try()) { check("print("); _QSTR(E); check(");"); mknode(_f16); ok(); }
  else  if (try()) { check("genNum();"); mknode(_f17); ok(); }
  else { check("<!--"); _OUTS(E); check("// -->"); mknode(_f18);}
 }

 void _NAME(int e) {
 if (try()) { _CHR(E); combine(); _NAME(E); mknode(_f19); ok(); }
  else { _CHR(E); mknode(_f20);}
 }

 void _QSTR(int e) {
{ check("\""); combine(); _QSTR1(E); mknode(_f21);}
 }

 void _QSTR1(int e) {
 if (try()) { check("\""); mknode(_f22); ok(); }
  else  if (try()) { _CHR(E); combine(); _QSTR1(E); mknode(_f23); ok(); }
  else { _MCHR(E); combine(); _QSTR1(E); mknode(_f24);}
 }

 void _CHR(int e) {
 if (try()) { _ALPH(E); mknode(_f25); ok(); }
  else  if (try()) { _SALPH(E); mknode(_f26); ok(); }
  else { _NUM(E); mknode(_f27);}
 }

 void _MCHR(int e) {
 if (try()) { check("\\"); combine(); _MARK(E); mknode(_f28); ok(); }
  else { _MARK(E); mknode(_f29);}
 }

 void _NUMS(int e) {
 if (try()) { _NUM(E); combine(); _NUMS(E); mknode(_f30); ok(); }
  else { _NUM(E); mknode(_f31);}
 }

 void _ALPH(int e) {
 if (try()) { check("A"); mknode(_f32); ok(); }
  else  if (try()) { check("B"); mknode(_f33); ok(); }
  else  if (try()) { check("C"); mknode(_f34); ok(); }
  else  if (try()) { check("D"); mknode(_f35); ok(); }
  else  if (try()) { check("E"); mknode(_f36); ok(); }
  else  if (try()) { check("F"); mknode(_f37); ok(); }
  else  if (try()) { check("G"); mknode(_f38); ok(); }
  else  if (try()) { check("H"); mknode(_f39); ok(); }
  else  if (try()) { check("I"); mknode(_f40); ok(); }
  else  if (try()) { check("J"); mknode(_f41); ok(); }
  else  if (try()) { check("K"); mknode(_f42); ok(); }
  else  if (try()) { check("L"); mknode(_f43); ok(); }
  else  if (try()) { check("M"); mknode(_f44); ok(); }
  else  if (try()) { check("N"); mknode(_f45); ok(); }
  else  if (try()) { check("O"); mknode(_f46); ok(); }
  else  if (try()) { check("P"); mknode(_f47); ok(); }
  else  if (try()) { check("Q"); mknode(_f48); ok(); }
  else  if (try()) { check("R"); mknode(_f49); ok(); }
  else  if (try()) { check("S"); mknode(_f50); ok(); }
  else  if (try()) { check("T"); mknode(_f51); ok(); }
  else  if (try()) { check("U"); mknode(_f52); ok(); }
  else  if (try()) { check("V"); mknode(_f53); ok(); }
  else  if (try()) { check("W"); mknode(_f54); ok(); }
  else  if (try()) { check("X"); mknode(_f55); ok(); }
  else  if (try()) { check("Y"); mknode(_f56); ok(); }
  else { check("Z"); mknode(_f57);}
 }

 void _SALPH(int e) {
 if (try()) { check("a"); mknode(_f58); ok(); }
  else  if (try()) { check("b"); mknode(_f59); ok(); }
  else  if (try()) { check("c"); mknode(_f60); ok(); }
  else  if (try()) { check("d"); mknode(_f61); ok(); }
  else  if (try()) { check("e"); mknode(_f62); ok(); }
  else  if (try()) { check("f"); mknode(_f63); ok(); }
  else  if (try()) { check("g"); mknode(_f64); ok(); }
  else  if (try()) { check("h"); mknode(_f65); ok(); }
  else  if (try()) { check("i"); mknode(_f66); ok(); }
  else  if (try()) { check("j"); mknode(_f67); ok(); }
  else  if (try()) { check("k"); mknode(_f68); ok(); }
  else  if (try()) { check("l"); mknode(_f69); ok(); }
  else  if (try()) { check("m"); mknode(_f70); ok(); }
  else  if (try()) { check("n"); mknode(_f71); ok(); }
  else  if (try()) { check("o"); mknode(_f72); ok(); }
  else  if (try()) { check("p"); mknode(_f73); ok(); }
  else  if (try()) { check("q"); mknode(_f74); ok(); }
  else  if (try()) { check("r"); mknode(_f75); ok(); }
  else  if (try()) { check("s"); mknode(_f76); ok(); }
  else  if (try()) { check("t"); mknode(_f77); ok(); }
  else  if (try()) { check("u"); mknode(_f78); ok(); }
  else  if (try()) { check("v"); mknode(_f79); ok(); }
  else  if (try()) { check("w"); mknode(_f80); ok(); }
  else  if (try()) { check("x"); mknode(_f81); ok(); }
  else  if (try()) { check("y"); mknode(_f82); ok(); }
  else { check("z"); mknode(_f83);}
 }

 void _NUM(int e) {
 if (try()) { check("0"); mknode(_f84); ok(); }
  else  if (try()) { check("1"); mknode(_f85); ok(); }
  else  if (try()) { check("2"); mknode(_f86); ok(); }
  else  if (try()) { check("3"); mknode(_f87); ok(); }
  else  if (try()) { check("4"); mknode(_f88); ok(); }
  else  if (try()) { check("5"); mknode(_f89); ok(); }
  else  if (try()) { check("6"); mknode(_f90); ok(); }
  else  if (try()) { check("7"); mknode(_f91); ok(); }
  else  if (try()) { check("8"); mknode(_f92); ok(); }
  else { check("9"); mknode(_f93);}
 }

 void _MARK(int e) {
 if (try()) { check(" "); mknode(_f94); ok(); }
  else  if (try()) { check("!"); mknode(_f95); ok(); }
  else  if (try()) { check("\""); mknode(_f96); ok(); }
  else  if (try()) { check("#"); mknode(_f97); ok(); }
  else  if (try()) { check("$"); mknode(_f98); ok(); }
  else  if (try()) { check("%"); mknode(_f99); ok(); }
  else  if (try()) { check("&"); mknode(_f100); ok(); }
  else  if (try()) { check("'"); mknode(_f101); ok(); }
  else  if (try()) { check("("); mknode(_f102); ok(); }
  else  if (try()) { check(")"); mknode(_f103); ok(); }
  else  if (try()) { check("*"); mknode(_f104); ok(); }
  else  if (try()) { check("+"); mknode(_f105); ok(); }
  else  if (try()) { check(","); mknode(_f106); ok(); }
  else  if (try()) { check("-"); mknode(_f107); ok(); }
  else  if (try()) { check("."); mknode(_f108); ok(); }
  else  if (try()) { check("/"); mknode(_f109); ok(); }
  else  if (try()) { check(":"); mknode(_f110); ok(); }
  else  if (try()) { check(";"); mknode(_f111); ok(); }
  else  if (try()) { check("<"); mknode(_f112); ok(); }
  else  if (try()) { check("="); mknode(_f113); ok(); }
  else  if (try()) { check(">"); mknode(_f114); ok(); }
  else  if (try()) { check("?"); mknode(_f115); ok(); }
  else  if (try()) { check("@"); mknode(_f116); ok(); }
  else  if (try()) { check("["); mknode(_f117); ok(); }
  else  if (try()) { check("]"); mknode(_f118); ok(); }
  else  if (try()) { check("\\"); mknode(_f119); ok(); }
  else  if (try()) { check("^"); mknode(_f120); ok(); }
  else  if (try()) { check("_"); mknode(_f121); ok(); }
  else  if (try()) { check("|"); mknode(_f122); ok(); }
  else  if (try()) { check("~"); mknode(_f123); ok(); }
  else  if (try()) { check("{"); mknode(_f124); ok(); }
  else { check("}"); mknode(_f125);}
 }
void _f1(int n, int a) {print("#include \"comcom.h\"\n");print("void firstcall(int e) { _");call(1);print("(e); }\n");call(2);}
void _f2(int n, int a) {call(1);call(2);}
void _f3(int n, int a) {call(1);}
void _f4(int n, int a) {print("\n void _");call(1);print("(int e) {\n");call(2);print("\n }\n");}
void _f5(int n, int a) {print(" if (try()) {");call(1);print(" ok(); }\n  else ");call(2);}
void _f6(int n, int a) {print("{");call(1);print("}");}
void _f7(int n, int a) {call(1);print(" mknode(_f");genNum();print(");");spoolOpen();
print("void _f");genNum();print("(int n, int a) {");call(2);print("}\n");spoolClose();
}
void _f8(int n, int a) {call(1);call(2);}
void _f9(int n, int a) {call(1);}
void _f10(int n, int a) {print(" _");call(1);print("(E);");}
void _f11(int n, int a) {print(" check(");call(1);print(");");}
void _f12(int n, int a) {print(" combine();");}
void _f13(int n, int a) {call(1);call(2);}
void _f14(int n, int a) {call(1);}
void _f15(int n, int a) {print("call(");call(1);print(");");}
void _f16(int n, int a) {print("print(");call(1);print(");");}
void _f17(int n, int a) {print("genNum();");}
void _f18(int n, int a) {print("spoolOpen();\n");call(1);print("spoolClose();\n");}
void _f19(int n, int a) {call(1);call(2);}
void _f20(int n, int a) {call(1);}
void _f21(int n, int a) {print("\"");call(1);}
void _f22(int n, int a) {print("\"");}
void _f23(int n, int a) {call(1);call(2);}
void _f24(int n, int a) {call(1);call(2);}
void _f25(int n, int a) {call(1);}
void _f26(int n, int a) {call(1);}
void _f27(int n, int a) {call(1);}
void _f28(int n, int a) {print("\\");call(1);}
void _f29(int n, int a) {call(1);}
void _f30(int n, int a) {call(1);call(2);}
void _f31(int n, int a) {call(1);}
void _f32(int n, int a) {print("A");}
void _f33(int n, int a) {print("B");}
void _f34(int n, int a) {print("C");}
void _f35(int n, int a) {print("D");}
void _f36(int n, int a) {print("E");}
void _f37(int n, int a) {print("F");}
void _f38(int n, int a) {print("G");}
void _f39(int n, int a) {print("H");}
void _f40(int n, int a) {print("I");}
void _f41(int n, int a) {print("J");}
void _f42(int n, int a) {print("K");}
void _f43(int n, int a) {print("L");}
void _f44(int n, int a) {print("M");}
void _f45(int n, int a) {print("N");}
void _f46(int n, int a) {print("O");}
void _f47(int n, int a) {print("P");}
void _f48(int n, int a) {print("Q");}
void _f49(int n, int a) {print("R");}
void _f50(int n, int a) {print("S");}
void _f51(int n, int a) {print("T");}
void _f52(int n, int a) {print("U");}
void _f53(int n, int a) {print("V");}
void _f54(int n, int a) {print("W");}
void _f55(int n, int a) {print("X");}
void _f56(int n, int a) {print("Y");}
void _f57(int n, int a) {print("Z");}
void _f58(int n, int a) {print("a");}
void _f59(int n, int a) {print("b");}
void _f60(int n, int a) {print("c");}
void _f61(int n, int a) {print("d");}
void _f62(int n, int a) {print("e");}
void _f63(int n, int a) {print("f");}
void _f64(int n, int a) {print("g");}
void _f65(int n, int a) {print("h");}
void _f66(int n, int a) {print("i");}
void _f67(int n, int a) {print("j");}
void _f68(int n, int a) {print("k");}
void _f69(int n, int a) {print("l");}
void _f70(int n, int a) {print("m");}
void _f71(int n, int a) {print("n");}
void _f72(int n, int a) {print("o");}
void _f73(int n, int a) {print("p");}
void _f74(int n, int a) {print("q");}
void _f75(int n, int a) {print("r");}
void _f76(int n, int a) {print("s");}
void _f77(int n, int a) {print("t");}
void _f78(int n, int a) {print("u");}
void _f79(int n, int a) {print("v");}
void _f80(int n, int a) {print("w");}
void _f81(int n, int a) {print("x");}
void _f82(int n, int a) {print("y");}
void _f83(int n, int a) {print("z");}
void _f84(int n, int a) {print("0");}
void _f85(int n, int a) {print("1");}
void _f86(int n, int a) {print("2");}
void _f87(int n, int a) {print("3");}
void _f88(int n, int a) {print("4");}
void _f89(int n, int a) {print("5");}
void _f90(int n, int a) {print("6");}
void _f91(int n, int a) {print("7");}
void _f92(int n, int a) {print("8");}
void _f93(int n, int a) {print("9");}
void _f94(int n, int a) {print(" ");}
void _f95(int n, int a) {print("!");}
void _f96(int n, int a) {print("\"");}
void _f97(int n, int a) {print("#");}
void _f98(int n, int a) {print("$");}
void _f99(int n, int a) {print("%");}
void _f100(int n, int a) {print("&");}
void _f101(int n, int a) {print("'");}
void _f102(int n, int a) {print("(");}
void _f103(int n, int a) {print(")");}
void _f104(int n, int a) {print("*");}
void _f105(int n, int a) {print("+");}
void _f106(int n, int a) {print(",");}
void _f107(int n, int a) {print("-");}
void _f108(int n, int a) {print(".");}
void _f109(int n, int a) {print("/");}
void _f110(int n, int a) {print(":");}
void _f111(int n, int a) {print(";");}
void _f112(int n, int a) {print("<");}
void _f113(int n, int a) {print("=");}
void _f114(int n, int a) {print(">");}
void _f115(int n, int a) {print("?");}
void _f116(int n, int a) {print("@");}
void _f117(int n, int a) {print("[");}
void _f118(int n, int a) {print("]");}
void _f119(int n, int a) {print("\\");}
void _f120(int n, int a) {print("^");}
void _f121(int n, int a) {print("_");}
void _f122(int n, int a) {print("|");}
void _f123(int n, int a) {print("~");}
void _f124(int n, int a) {print("{");}
void _f125(int n, int a) {print("}");}
