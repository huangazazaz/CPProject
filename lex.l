%{
    #include "node.hpp"
    int isError = 0;
    #define LEXER_ERROR_OUTPUT stdout
%}
%{
    #include"syntax.tab.h"
    /* library inclusions */ 
    int yycolumn = 1;
    #define YY_USER_ACTION \
        yylloc.first_line = yylineno; \
        yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn; \
        yylloc.last_column = yycolumn + yyleng;\
        yycolumn += yyleng;

%}
%option noyywrap
%option yylineno
letters [A-Za-z]
letters_ [A-Za-z_]
digit [0-9]
digit_16 [0-9a-fA-F]
UINT32_10 (0|([1-9]{digit}*))
UINT32_16 0[xX](0|[1-9a-fA-F]{digit_16}*)
UINT32_16_error_leading_0 0(0|[1-9a-fA-F]{digit_16}*)
UINT32_16_error_more_0 0[xX](0{2,}{digit_16}*)
UINT32_16_error_illgeal_char 0[xX]([1-9a-fA-F]*)
UINT32 {UINT32_10}|{UINT32_16}
UFLOAT32 {digit}+\.{digit}+
ID {letters_}({letters_}|{digit}){0,31}
CHAR '.'
CHAR_16 '\\x(0|[1-9a-fA-F]{digit_16})'
CHAR_16_more0 '\\x00{digit_16}*'
CHAR_16_illgeal_char '\\x{digit_16}*([^0-9a-fA-F])+{digit_16}*'
CHAR_16_toolong '\\x{digit_16}{3,}'
STRING '{letters}{2,}'|\"{letters}{2,}\"
%%
"//" {
    char c = yyinput();
    while(c!='\n'){c=yyinput();}
}
"/*"([^*]|\*+[^*/])*"*"+"/"  { /* Ignore the multi-line comment */ }
"\n" {yycolumn = 1;}

[ \t\r]+ {}
"int" {
    yylval.Node_value = new Node("TYPE","int",Node_TYPE::STRING);
    return TYPE;
}
"float" {
    yylval.Node_value = new Node("TYPE","float",Node_TYPE::STRING);
    return TYPE;
}
"char" {
    yylval.Node_value = new Node("TYPE","char",Node_TYPE::STRING);
    return TYPE;
}
"bool" {
    yylval.Node_value = new Node("TYPE","bool",Node_TYPE::STRING);
    return TYPE;
}
"struct" {yylval.Node_value = new Node("STRUCT");return STRUCT;}
"if" {yylval.Node_value = new Node("IF");return IF;}
"else" {yylval.Node_value = new Node("ELSE");return ELSE;}
"while" {yylval.Node_value = new Node("WHILE");return WHILE;}
"for" {yylval.Node_value = new Node("FOR");return FOR;}
"return" {yylval.Node_value = new  Node("RETURN");return RETURN;}
"." {yylval.Node_value = new  Node("DOT");return DOT;}
";" {yylval.Node_value = new  Node("SEMI");return SEMI;}
"," {yylval.Node_value = new  Node("COMMA");return COMMA;}
"=" {yylval.Node_value = new  Node("ASSIGN");return ASSIGN;}
"<" {yylval.Node_value = new  Node("LT");return LT;}
"<=" {yylval.Node_value = new  Node("LE");return LE;}
">" {yylval.Node_value = new  Node("GT");return GT;}
">=" {yylval.Node_value = new  Node("GE");return GE;}
"!=" {yylval.Node_value = new  Node("NE");return NE;}
"==" {yylval.Node_value = new  Node("EQ");return EQ;}
"&&" {yylval.Node_value = new  Node("AND");return AND;}
"||" {yylval.Node_value = new  Node("OR");return OR;}
"+" {yylval.Node_value = new  Node("PLUS");return PLUS;}
"+=" {yylval.Node_value = new  Node("PLUS_ASSIGN");return PLUS_ASSIGN;}
"-" {yylval.Node_value = new  Node("MINUS");return MINUS;}
"-=" {yylval.Node_value = new  Node("MINUS_ASSIGN");return MINUS_ASSIGN;}
"*" {yylval.Node_value = new  Node("MUL");return MUL;}
"*=" {yylval.Node_value = new  Node("MUL_ASSIGN");return MUL_ASSIGN;}
"/" {yylval.Node_value = new  Node("DIV");return DIV;}
"/=" {yylval.Node_value = new  Node("DIV_ASSIGN");return DIV_ASSIGN;}
"%" {yylval.Node_value = new  Node("MOD");return MOD;}
"%=" {yylval.Node_value = new  Node("MOD");return MOD_ASSIGN;}
"&" {yylval.Node_value = new  Node("BAND");return BAND;}
"&=" {yylval.Node_value = new  Node("BAND");return BAND_ASSIGN;}
"|" {yylval.Node_value = new  Node("BOR");return BOR;}
"|=" {yylval.Node_value = new  Node("BOR");return BOR_ASSIGN;}
"^" {yylval.Node_value = new  Node("XOR");return XOR;}
"^=" {yylval.Node_value = new  Node("XOR");return XOR_ASSIGN;}
"?" {yylval.Node_value = new  Node("TERN");return TERN;}
"!" {yylval.Node_value = new  Node("NOT");return NOT;}
"(" {yylval.Node_value = new  Node("LP");return LP;}
")" {yylval.Node_value = new  Node("RP");return RP;}
"[" {yylval.Node_value = new  Node("LB");return LB;}
"]" {yylval.Node_value = new  Node("RB");return RB;}
"{" {yylval.Node_value = new  Node("LC");return LC;}
"}" {yylval.Node_value = new  Node("RC");return RC;}
":" {yylval.Node_value = new  Node("COLON");return COLON;}
"true" {
    yylval.Node_value = new  Node(true);
    return BOOLEAN;
}
"false" {
    yylval.Node_value = new  Node(false);
    return BOOLEAN;
}
{ID} {
    yylval.Node_value = new  Node("ID",yytext,Node_TYPE::STRING);
    return ID;
}
{UFLOAT32} {
    yylval.Node_value = new Node(static_cast<float>(atof(yytext)));
    return FLOAT;
}
{UINT32_10} {
    yylval.Node_value = new Node(atoi(yytext));
    return INT;
}
{UINT32_16} {
    yylval.Node_value = new Node(static_cast<int>(strtol(yytext,nullptr,0)));
    return INT;
}
{UINT32_16_error_more_0} {
    isError=1;
    yylval.Node_value = new Node(0);
    fprintf(LEXER_ERROR_OUTPUT, "Error at Line %d: '%s' - Illgeal UINT32 hex-Leading 0 \n", yylineno, yytext);
    return INT;
}
{UINT32_16_error_leading_0} {
    isError=1;
    yylval.Node_value = new Node(0);
    fprintf(LEXER_ERROR_OUTPUT, "Error at Line %d: '%s' - Illgeal UINT32 Leading 0 \n", yylineno, yytext);
    return INT;
}
{UINT32_16_error_illgeal_char} {
    isError=1;
    yylval.Node_value = new Node(0);
    fprintf(LEXER_ERROR_OUTPUT, "Error at Line %d: '%s' - UINT32_16_error_illgeal_char \n", yylineno, yytext);
    return INT;
}
{CHAR} {
    yylval.Node_value = new Node("CHAR",yytext,Node_TYPE::STRING);
    return CHAR;
}
{CHAR_16} {
    yylval.Node_value = new Node("CHAR",yytext,Node_TYPE::STRING);
    return CHAR;
}
{CHAR_16_more0} {
    isError=1;
    fprintf(LEXER_ERROR_OUTPUT,"Error at Line %d: unknown lexeme %s\n",yylineno, yytext);
    yylval.Node_value = new Node('0');
    return CHAR;
}
{CHAR_16_illgeal_char} {
    isError=1;
    fprintf(LEXER_ERROR_OUTPUT,"Error at Line %d: unknown lexeme %s\n",yylineno, yytext);
    yylval.Node_value = new Node('0');
    return CHAR;
}
{CHAR_16_toolong} {
    isError=1;
    fprintf(LEXER_ERROR_OUTPUT,"Error at Line %d: unknown lexeme %s\n",yylineno, yytext);
    yylval.Node_value = new Node('0');
    return CHAR;
}
{STRING} {
    isError=1;
    fprintf(LEXER_ERROR_OUTPUT,"Error at Line %d: unknown lexeme %s\n",yylineno, yytext);
    yylval.Node_value = new Node('0');
    return CHAR;
}
[^0-9a-zA-Z_'\\\(\)\[\]\{\}\;\,\+\-\*\/] {
    isError=1;
    // illgeal characters
    fprintf(LEXER_ERROR_OUTPUT,"Error at Line %d: unknown lexeme %s\n",yylineno, yytext);
    //yymore();
    return ID;
}
[0-9]*{ID} {
    isError=1;
    fprintf(LEXER_ERROR_OUTPUT,"Error at Line %d: unknown lexeme %s\n",yylineno, yytext);
    // TODO
    return ID;
}
%%