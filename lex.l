%{
#include <stdio.h>
#include <stdlib.h>

/* Error reporting */
void yyerror(const char *s);
%}

/* Definitions for regular expressions */
%x COMMENT

DIGIT       [0-9]
HEX         [0-9a-fA-F]
LETTER      [a-zA-Z_]
INT         {DIGIT}+
HEX_INT     0[xX]{HEX}+
FLOAT       {DIGIT}+"."{DIGIT}*
CHAR        '\\x'{HEX}|'\\'?.'
ID          {LETTER}({LETTER}|{DIGIT})*

%%

/* Keywords */
"int"            { return TYPE; }
"float"          { return TYPE; }
"char"           { return TYPE; }
"struct"         { return STRUCT; }
"if"             { return IF; }
"else"           { return ELSE; }
"while"          { return WHILE; }
"return"         { return RETURN; }

/* Operators and delimiters */
"."             { return DOT; }
";"             { return SEMI; }
","             { return COMMA; }
"="             { return ASSIGN; }
"<"             { return LT; }
"<="            { return LE; }
">"             { return GT; }
">="            { return GE; }
"!="            { return NE; }
"=="            { return EQ; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MUL; }
"/"             { return DIV; }
"&"             { return BAND; }
"&&"            { return AND; }
"|"             { return BOR; }
"||"            { return OR; }
"^"             { return XOR; }
"!"             { return NOT; }
"("             { return LP; }
")"             { return RP; }
"["             { return LB; }
"]"             { return RB; }
"{"             { return LC; }
"}"             { return RC; }

/* Literals */
{INT}            { yylval.intval = atoi(yytext); return INT; }
{HEX_INT}        { yylval.intval = strtol(yytext, NULL, 16); return INT; }
{FLOAT}          { yylval.floatval = atof(yytext); return FLOAT; }
{CHAR}           { yylval.charval = yytext[1]; return CHAR; }

/* Identifier */
{ID}             { return ID; }

/* Whitespace */
[ \t\n\r]+       { /* Skip whitespace */ }

/* Comments */
"/*"            { BEGIN(COMMENT); }
<COMMENT>"*/"   { BEGIN(INITIAL); }
<COMMENT>.       { /* Ignore comment content */ }

/* Error handling */
"@"|"#"         { fprintf(stderr, "Error: Undefined token '%s'\n", yytext); }
0[xX][^0-9a-fA-F]+  { fprintf(stderr, "Error: Illegal hex integer '%s'\n", yytext); }
"\\x"[^0-9a-fA-F] { fprintf(stderr, "Error: Illegal hex char '%s'\n", yytext); }
.                 { fprintf(stderr, "Error: Unknown token '%s'\n", yytext); }

%%

int yywrap() {
    return 1;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
} 
