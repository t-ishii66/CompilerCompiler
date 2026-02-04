#include "comcom.h"
void _RPN(int e);
void _EXPR(int e);
void _TERM(int e);
void _FACTOR(int e);
void _NUMBER(int e);
void _DIGIT(int e);
void firstcall(int e) { _RPN(e); }

 void _RPN(int e) {
{ _EXPR(E); mknode(_f1);}
 }

 void _EXPR(int e) {
 if (try()) { _TERM(E); check("+"); _EXPR(E); mknode(_f2); ok(); }
  else  if (try()) { _TERM(E); check("-"); _EXPR(E); mknode(_f3); ok(); }
  else { _TERM(E); mknode(_f4);}
 }

 void _TERM(int e) {
 if (try()) { _FACTOR(E); check("*"); _TERM(E); mknode(_f5); ok(); }
  else  if (try()) { _FACTOR(E); check("/"); _TERM(E); mknode(_f6); ok(); }
  else { _FACTOR(E); mknode(_f7);}
 }

 void _FACTOR(int e) {
 if (try()) { check("("); _EXPR(E); check(")"); mknode(_f8); ok(); }
  else { _NUMBER(E); mknode(_f9);}
 }

 void _NUMBER(int e) {
 if (try()) { _DIGIT(E); combine(); _NUMBER(E); mknode(_f10); ok(); }
  else { _DIGIT(E); mknode(_f11);}
 }

 void _DIGIT(int e) {
 if (try()) { check("0"); mknode(_f12); ok(); }
  else  if (try()) { check("1"); mknode(_f13); ok(); }
  else  if (try()) { check("2"); mknode(_f14); ok(); }
  else  if (try()) { check("3"); mknode(_f15); ok(); }
  else  if (try()) { check("4"); mknode(_f16); ok(); }
  else  if (try()) { check("5"); mknode(_f17); ok(); }
  else  if (try()) { check("6"); mknode(_f18); ok(); }
  else  if (try()) { check("7"); mknode(_f19); ok(); }
  else  if (try()) { check("8"); mknode(_f20); ok(); }
  else { check("9"); mknode(_f21);}
 }
void _f1(int n, int a) {call(1);print("\n");}
void _f2(int n, int a) {call(1);print(" ");call(2);print(" +");}
void _f3(int n, int a) {call(1);print(" ");call(2);print(" -");}
void _f4(int n, int a) {call(1);}
void _f5(int n, int a) {call(1);print(" ");call(2);print(" *");}
void _f6(int n, int a) {call(1);print(" ");call(2);print(" /");}
void _f7(int n, int a) {call(1);}
void _f8(int n, int a) {call(1);}
void _f9(int n, int a) {call(1);}
void _f10(int n, int a) {call(1);call(2);}
void _f11(int n, int a) {call(1);}
void _f12(int n, int a) {print("0");}
void _f13(int n, int a) {print("1");}
void _f14(int n, int a) {print("2");}
void _f15(int n, int a) {print("3");}
void _f16(int n, int a) {print("4");}
void _f17(int n, int a) {print("5");}
void _f18(int n, int a) {print("6");}
void _f19(int n, int a) {print("7");}
void _f20(int n, int a) {print("8");}
void _f21(int n, int a) {print("9");}
