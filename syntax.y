%{
    #include <string>
    #include <unordered_map>
    #include "type.hpp"
    #include "visitSyntaxTree.hpp"
    
    using std::string;
    using std::unordered_map;
    #define YYDEBUG 1
    #define YY_NO_UNPUT
    #include "lex.yy.c"
    void yyerror(const char *s);
    void lineinfor(void);
    Node* root_node;

    unordered_map<string,Type*> symbolTable;
    extern int isError;
    #define PARSER_error_OUTPUT stdout
    #include "ierror.hpp"
%}
%locations
%union{
    Node* Node_value;
}
%nonassoc LOWER_ERROR
%nonassoc <Node_value> ILLEGAL_TOKEN
%nonassoc <Node_value> LOWER_THAN_ELSE
%nonassoc <Node_value> ELSE
%token <Node_value> TYPE STRUCT
%token <Node_value> IF WHILE RETURN
%token <Node_value> INT
%token <Node_value> FLOAT
%token <Node_value> CHAR
%token <Node_value> BOOLEAN
%token <Node_value> ID
%right <Node_value> ASSIGN PLUS_ASSIGN MINUS_ASSIGN MUL_ASSIGN DIV_ASSIGN
%left <Node_value> OR
%left <Node_value> AND
%left <Node_value> BOR
%left <Node_value> XOR
%left <Node_value> BAND
%left <Node_value> LT LE GT GE NE EQ
%nonassoc LOWER_MINUS
%left <Node_value> PLUS MINUS
%left <Node_value> MUL DIV
%right <Node_value> NOT
%left <Node_value> LP RP LB RB DOT
%token <Node_value> SEMI COMMA
%token <Node_value> LC RC
%token <Node_value> STRING
%token <Node_value> FOR

%type <Node_value> Program ExtDefList
%type <Node_value> ExtDef ExtDecList Specifier StructSpecifier VarDec Specifier_FunDec_Recv
%type <Node_value> FunDec VarList ParamDec CompSt CompList StmtList Stmt DefList
%type <Node_value> Def DecList Dec Args Exp
%%
/* high-level definition */
Program: ExtDefList {
    $$= new Node("Program",@$.first_line);
    $$->push_back($1);
    root_node=$$;
    // root_node->print(0);
};
ExtDefList:{$$=new Node("ExtDefList",@$.first_line,Node_TYPE::NOTHING);}
    | ExtDef ExtDefList {$$=new Node("ExtDefList",@$.first_line); $$->push_back($1,$2);}
    ;
ExtDef: Specifier ExtDecList SEMI  {
    $$=new Node("ExtDef",@$.first_line);
    $$->push_back($1,$2,$3);
    extDefVisit_SES($$);
    }
    | Specifier SEMI {
    $$=new Node("ExtDef",@$.first_line);
    $$->push_back($1,$2);
    extDefVisit_SS($$);
    }
    | Specifier_FunDec_Recv CompSt {

        // printf("Extern def with function \n");
        $$=new Node("ExtDef",@$.first_line);
        $$->push_back($1->nodes[0],$1->nodes[1],$2);
        extDefVisit_SFC($$);
    }
    | Specifier ExtDecList error  {ierror(IERROR_TYPE::SEMI);}
    | Specifier error {ierror(IERROR_TYPE::SEMI);}
    ;
Specifier_FunDec_Recv:Specifier FunDec{
    $$=new Node("Specifier_FunDec_Recv",@$.first_line);
    $$->push_back($1,$2);
    Specifier_FunDec_Recv_SF($$);
};
ExtDecList: VarDec {$$=new Node("ExtDecList",@$.first_line);$$->push_back($1);}
    | VarDec COMMA ExtDecList {$$=new Node("ExtDecList",@$.first_line);$$->push_back($1,$2,$3);}
    | VarDec ExtDecList error {ierror(IERROR_TYPE::COMMA);}
    ;
/* specifier: for function and struct */
Specifier: TYPE {

    $$=new Node("Specifier",@$.first_line);$$->push_back($1);
    }
    | StructSpecifier {
        $$=new Node("Specifier",@$.first_line);$$->push_back($1);
        }
    ;
StructSpecifier: STRUCT ID LC DefList RC {
    $$=new Node("StructSpecifier",@$.first_line); $$->push_back($1,$2,$3,$4,$5);}
    | STRUCT ID  {
        
        $$=new Node("StructSpecifier",@$.first_line); $$->push_back($1,$2);
        
        }
    | STRUCT ID LC DefList error { isError = 1;ierror(IERROR_TYPE::RC); }
    ;
/* declarator */
VarDec: ID {$$=new Node("VarDec",@$.first_line);$$->push_back($1);}
    | VarDec LB INT RB {
    $$=new Node("VarDec",@$.first_line); $$->push_back($1,$2,$3,$4);}
    | VarDec LB INT error %prec LOWER_ERROR {ierror(IERROR_TYPE::RB);}
FunDec: ID LP VarList RP {

    $$=new Node("FunDec",@$.first_line); $$->push_back($1,$2,$3,$4);funDecVisit($$);
            string idName = std::get<string>($1->value);
            // printf("Func ID %s\n", idName.c_str() );
    }
    | ID LP RP  {
        $$=new Node("FunDec",@$.first_line); $$->push_back($1,$2,$3);funDecVisit($$);
        }
    | ID LP VarList error {ierror(IERROR_TYPE::RP);}
    | ID LP error {ierror(IERROR_TYPE::RP);
    }
    ;
VarList: ParamDec COMMA VarList {$$=new Node("VarList",@$.first_line); $$->push_back($1,$2,$3);}
    | ParamDec VarList error {ierror(IERROR_TYPE::COMMA);}
    | ParamDec {$$=new Node("VarList",@$.first_line); $$->push_back($1);}
    ;
ParamDec: Specifier VarDec {$$=new Node("ParamDec",@$.first_line); $$->push_back($1,$2);}
    ;
/* statement, planning to add scoping */
CompSt: LC CompList RC {
        $$=new Node("CompSt",@$.first_line); 
        $$->push_back($1,$2,$3); 
    }
;

CompList: {$$=new Node("CompList",@$.first_line,Node_TYPE::NOTHING);}
    | Def CompList {$$=new Node("CompList",@$.first_line); $$->push_back($1,$2);}
    | Stmt CompList {$$=new Node("CompList",@$.first_line); $$->push_back($1,$2);}

StmtList:  {$$=new Node("StmtList",@$.first_line,Node_TYPE::NOTHING);}
    |  Stmt StmtList {$$=new Node("StmtList",@$.first_line); $$->push_back($1,$2);}
    ;
Stmt: Exp SEMI {$$=new Node("Stmt",@$.first_line); $$->push_back($1,$2);}
    | CompSt {$$=new Node("Stmt",@$.first_line);$$->push_back($1);}
    | RETURN Exp SEMI {$$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3);}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3,$4,$5);}
    | IF LP Exp RP Stmt ELSE Stmt {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3,$4,$5,$6,$7);}
    | WHILE LP Exp RP Stmt {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3,$4,$5);}
    | FOR LP Def Exp SEMI Exp RP Stmt {
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, $6, $7, $8);
    }
    | FOR LP Def Exp SEMI Exp error Stmt {ierror(IERROR_TYPE::RP); }
    | FOR error Def Exp SEMI Exp RP Stmt {ierror(IERROR_TYPE::LP); }
    | WHILE error Exp RP Stmt {ierror(IERROR_TYPE::LP); }
    | WHILE LP Exp error Stmt {ierror(IERROR_TYPE::RP); }
    | Exp error {ierror(IERROR_TYPE::SEMI);}
    | RETURN Exp error {ierror(IERROR_TYPE::SEMI);}
    | IF LP Exp error Stmt  {YYERROR;ierror(IERROR_TYPE::RP); }
    | IF error Exp RP Stmt {ierror(IERROR_TYPE::LP); }
    ;
/* local definition, DefList is only a recursive structure that holds the def  */
DefList: {$$=new Node("DefList",@$.first_line,Node_TYPE::NOTHING);}
    | Def DefList {$$=new Node("DefList",@$.first_line); $$->push_back($1,$2);}
    ;
/*
// Definition of basic name: int x,y,z;
// */
Def: Specifier DecList SEMI {

    // printf("Definition of variable detected\n");
    $$=new Node("Def",@$.first_line);
    $$->push_back($1,$2,$3);
    defVisit($$);
    }
    | Specifier DecList error {ierror(IERROR_TYPE::SEMI);}
    // | %prec LOWER_ERROR DecList SEMI {
    // ierror(IERROR_TYPE::SPEC);
    // printf("error\n");
    // $$->print();
    // $2->print();
    // }
    ;
DecList: Dec {$$=new Node("DecList",@$.first_line);$$->push_back($1);}
    | Dec COMMA DecList {$$=new Node("DecList",@$.first_line); $$->push_back($1,$2,$3);}
    | Dec  DecList error {ierror(IERROR_TYPE::COMMA);}
;
Dec: VarDec {$$=new Node("Dec",@$.first_line); $$->push_back($1);}
    | VarDec ASSIGN Exp {
    $$=new Node("Dec",@$.first_line); $$->push_back($1,$2,$3);
    // 声明时初始化
    }
    ;
/* Expression */
Args: Exp COMMA Args  {$$=new Node("Args",@$.first_line); $$->push_back($1,$2,$3);}
    | Exp {$$=new Node("Args",@$.first_line);$$->push_back($1);}
/*TODO the lack of COMMA in exp and Args*/
    ;
Exp: Exp ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp PLUS_ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp MINUS_ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp MUL_ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp DIV_ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp AND Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getBoolOperatorType($$,$1,$3);}
    | Exp OR Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getBoolOperatorType($$,$1,$3);}
    | Exp LT Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getComparisonOperatorType($$,$1,$3);}
    | Exp LE Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getComparisonOperatorType($$,$1,$3);}
    | Exp GT Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getComparisonOperatorType($$,$1,$3);}
    | Exp GE Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getComparisonOperatorType($$,$1,$3);}
    | Exp NE Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getComparisonOperatorType($$,$1,$3);}
    | Exp EQ Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getComparisonOperatorType($$,$1,$3);}
    | Exp PLUS Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp MINUS Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp MUL Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp DIV Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp BOR Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp BAND Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp XOR Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | LP Exp RP {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);$$->type=$2->type;} // lp is (
    | LP Exp error {ierror(IERROR_TYPE::RP);} // TODO 参数判断有问题， 比如 func(p1, );
    | MINUS Exp %prec LOWER_MINUS {$$=new Node("Exp",@$.first_line);$$->push_back($1,$2);$$->type=$2->type;checkAlrthOperatorType($2);}
    | NOT Exp {$$=new Node("Exp",@$.first_line);$$->push_back($1,$2);$$->type=$2->type;}
    | ID LP Args RP {

      // If expression is an ID + parantheses, this is a function invoke
      checkInvokeExist($1,@1.first_line);
      checkFunctionParams($1,$3,@3.first_line);

      //append node that resembles the return type of that function   
      $$=new Node("Exp",@$.first_line);
      $$->push_back($1,$2,$3,$4);
      getReturnTypeOfFunction($$,$1);
      }
    | ID LP Args error {ierror(IERROR_TYPE::RP);}
    | ID LP RP {
      checkInvokeExist($1,@1.first_line);
      checkFunctionParams($1,nullptr,@3.first_line);
      $$=new Node("Exp",@$.first_line);
      $$->push_back($1,$2,$3);
      getReturnTypeOfFunction($$,$1);
    }
    | ID LP error {ierror(IERROR_TYPE::RP);}
    | Exp LB Exp RB{
        $$=new Node("Exp",@$.first_line);
        $$->push_back($1,$2,$3,$4);
        // LB is [
        checkArrayExists($1);
        getArrayType($$,$1,$3);
    }
    | Exp LB Exp error {ierror(IERROR_TYPE::RB);}
    | Exp DOT ID {
        $$=new Node("Exp",@$.first_line);
        $$->push_back($1,$2,$3);
        checkNoSuchMember($$);
        searchAndPutTypeOfDot($$,$1,$3);
    }
    | ID {
        $$=new Node("Exp",@$.first_line);$$->push_back($1);
        checkIdExists($1,@1.first_line);
        idToExp($$,$1);
    }
    | BOOLEAN {
        $$=new Node("Exp",@$.first_line);$$->push_back($1);
        $$->type = Type::getPrimitiveBOOLEAN();
    }
    | INT {
        $$=new Node("Exp",@$.first_line);$$->push_back($1);
        $$->type = Type::getPrimitiveINT();
    }
    | FLOAT {
        $$=new Node("Exp",@$.first_line);$$->push_back($1);
        $$->type = Type::getPrimitiveFLOAT();
        }
    | CHAR {
        $$=new Node("Exp",@$.first_line);$$->push_back($1);
        $$->type = Type::getPrimitiveCHAR();}
    | Exp ILLEGAL_TOKEN Exp {}
    | ILLEGAL_TOKEN {}
    ;

%%
void yyerror(const char *s){
    isError=1;
    if(s[0]  == '0'){}
    // fprintf(PARSER_error_OUTPUT,"Error at Line %d: ",yylloc.first_line-1);
    // fprintf(PARSER_error_OUTPUT, "syntax Error: %s\n", s);
    //lineinfor();
}

void lineinfor(void){
    fprintf(PARSER_error_OUTPUT, "begin at:(%d,%d)\n",yylloc.first_line,yylloc.first_column);
    fprintf(PARSER_error_OUTPUT, "end at:(%d,%d)\n",yylloc.last_line,yylloc.last_column);
}
