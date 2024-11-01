%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(const char *s);
%}

%union {
    int intval;
    float floatval;
    char charval;
    char *id;
}

%token <intval> INT FLOAT CHAR
%token <id> ID
%token TYPE STRUCT IF ELSE WHILE RETURN
%token DOT SEMI COMMA ASSIGN LT LE GT GE NE EQ PLUS MINUS MUL DIV BAND AND BOR OR XOR NOT LP RP LB RB LC RC

%start Program

%%

/* High-level definition */
Program: ExtDefList
       ;

ExtDefList: ExtDef ExtDefList
          | /* empty */
          ;

ExtDef: Specifier ExtDecList SEMI
      | Specifier SEMI
      | Specifier FunDec CompSt
      ;

ExtDecList: VarDec
          | VarDec COMMA ExtDecList
          ;

/* Specifier */
Specifier: TYPE
         | StructSpecifier
         ;

StructSpecifier: STRUCT ID LC DefList RC
               | STRUCT ID
               ;

/* Declarator */
VarDec: ID
      | VarDec LB INT RB
      ;

FunDec: ID LP VarList RP
      | ID LP RP
      ;

VarList: ParamDec COMMA VarList
       | ParamDec
       ;

ParamDec: Specifier VarDec
        ;

/* Statement */
CompSt: LC DefList StmtList RC
      ;

StmtList: Stmt StmtList
        | /* empty */
        ;

Stmt: Exp SEMI
    | CompSt
    | RETURN Exp SEMI
    | IF LP Exp RP Stmt
    | IF LP Exp RP Stmt ELSE Stmt
    | WHILE LP Exp RP Stmt
    ;

/* Local definition */
DefList: Def DefList
       | /* empty */
       ;

Def: Specifier DecList SEMI
   ;

DecList: Dec
        | Dec COMMA DecList
        ;

Dec: VarDec
   | VarDec ASSIGN Exp
   ;

/* Expression */
Exp: Exp ASSIGN Exp
   | Exp AND Exp
   | Exp BAND Exp
   | Exp OR Exp
   | Exp BOR Exp
   | Exp XOR Exp
   | Exp LT Exp
   | Exp LE Exp
   | Exp GT Exp
   | Exp GE Exp
   | Exp NE Exp
   | Exp EQ Exp
   | Exp PLUS Exp
   | Exp MINUS Exp
   | Exp MUL Exp
   | Exp DIV Exp
   | LP Exp RP
   | MINUS Exp
   | NOT Exp
   | ID LP Args RP
   | ID LP RP
   | Exp LB Exp RB
   | Exp DOT ID
   | ID
   | INT
   | FLOAT
   | CHAR
   ;

Args: Exp COMMA Args
    | Exp
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main() {
    return yyparse();
}
