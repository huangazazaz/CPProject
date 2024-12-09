%{
    #include <string>
    #include <unordered_map>
    #include "type.hpp"
    #include "visitSyntaxTree.hpp"
    #include "semanticError.hpp"
    #include "scopeStack.hpp"

    
    using std::string;
    using std::unordered_map;
    #define YYDEBUG 1
    #define YY_NO_UNPUT
    #include "lex.yy.c"
    void yyerror(const char *s);
    Node* root_node;

    unordered_map<string,Type*> symbolTable;
    ScopeStack scopeStack;
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
%token <Node_value> IF WHILE RETURN FOR
%token <Node_value> INT
%token <Node_value> FLOAT
%token <Node_value> CHAR
%token <Node_value> BOOLEAN
%token <Node_value> ID
%right <Node_value> ASSIGN PLUS_ASSIGN MINUS_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN BOR_ASSIGN BAND_ASSIGN XOR_ASSIGN
%right <Node_value> TERN COLON
%left <Node_value> OR
%left <Node_value> AND
%left <Node_value> BOR
%left <Node_value> XOR
%left <Node_value> BAND
%nonassoc <Node_value> LT LE GT GE NE EQ
%nonassoc LOWER_MINUS LOWER_PLUS
%left <Node_value> PLUS MINUS
%left <Node_value> MOD
%left <Node_value> MUL DIV
%right <Node_value> NOT
%left <Node_value> LP RP LB RB DOT
%token <Node_value> SEMI COMMA
%token <Node_value> LC RC

%type <Node_value> Program ExtDefList
%type <Node_value> ExtDef ExtDecList Specifier StructSpecifier VarDec Specifier_FunDec_Recv
%type <Node_value> FunDec VarList ParamDec CompSt Comp CompList Stmt TernaryStmt DefList
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
        scopeStack.exitScope();
    }
    | Specifier ExtDecList error  {ierror(@$.first_line, IERROR_TYPE::SEMI);
        $$=new Node("ExtDef",@$.first_line);
        $$->push_back($1,$2, new Node("SEMI"));
        extDefVisit_SES($$);
    }
    | Specifier error {ierror(@$.first_line, IERROR_TYPE::SEMI);
        $$=new Node("ExtDef",@$.first_line);
        $$->push_back($1,new Node("SEMI"));
        extDefVisit_SS($$);
}
    | ExtDecList SEMI error {ierror(@$.first_line, IERROR_TYPE::SPEC);
        $$=new Node("ExtDef",@$.first_line);
        Node* spec = new Node("Specifier");
        spec->push_back(new Node("TYPE","int",Node_TYPE::STRING));
        $$->push_back(spec, $1,$2);
        extDefVisit_SS($$);
}
    ;
Specifier_FunDec_Recv:Specifier FunDec{
    $$=new Node("Specifier_FunDec_Recv",@$.first_line);
    $$->push_back($1,$2);
    Specifier_FunDec_Recv_SF($$);
};
ExtDecList: VarDec {$$=new Node("ExtDecList",@$.first_line);$$->push_back($1);}
    | VarDec COMMA ExtDecList {$$=new Node("ExtDecList",@$.first_line);$$->push_back($1,$2,$3);}
    | VarDec COMMA error {ierror(@$.first_line, IERROR_TYPE::VAR);
        $$=new Node("ExtDecList",@$.first_line);$$->push_back($1);}
    | VarDec ExtDecList error {ierror(@$.first_line, IERROR_TYPE::COMMA);
    $$=new Node("ExtDecList",@$.first_line);$$->push_back($1,new Node("COMMA"),$2);}
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
    | STRUCT ID LC DefList error { ierror(@$.first_line, IERROR_TYPE::RC); 
    $$=new Node("StructSpecifier",@$.first_line); $$->push_back($1,$2,$3,$4,new Node("RC"));
    }
    ;
/* declarator */
VarDec: ID {$$=new Node("VarDec",@$.first_line);$$->push_back($1);}
    | VarDec LB INT RB {
    $$=new Node("VarDec",@$.first_line); $$->push_back($1,$2,$3,$4);}
    | VarDec LB INT error %prec LOWER_ERROR {ierror(@$.first_line, IERROR_TYPE::RB);
    $$=new Node("VarDec",@$.first_line); $$->push_back($1,$2,$3,new Node("RB"));}
FunDec: ID LP VarList RP {

    $$=new Node("FunDec",@$.first_line); $$->push_back($1,$2,$3,$4);funDecVisit($$);
            string idName = std::get<string>($1->value);
            // printf("Func ID %s\n", idName.c_str() );
    }
    | ID LP RP  {
        $$=new Node("FunDec",@$.first_line); $$->push_back($1,$2,$3);funDecVisit($$);
        }
    | ID LP VarList error {ierror(@$.first_line, IERROR_TYPE::RP);
      $$=new Node("FunDec",@$.first_line); $$->push_back($1,$2,$3,new Node("RP"));funDecVisit($$);
  
    }
    | ID LP error {ierror(@$.first_line, IERROR_TYPE::RP);
        $$=new Node("FunDec",@$.first_line); $$->push_back($1,$2,new Node("RP"));funDecVisit($$);
    }
    ;
VarList: ParamDec COMMA VarList {$$=new Node("VarList",@$.first_line); $$->push_back($1,$2,$3);}
    | ParamDec VarList error {ierror(@$.first_line, IERROR_TYPE::COMMA);
    $$=new Node("VarList",@$.first_line); $$->push_back($1,new Node("COMMA"),$2);}
    | ParamDec {$$=new Node("VarList",@$.first_line); $$->push_back($1);}
    | ParamDec COMMA error{
        ierror(@$.first_line, IERROR_TYPE::VAR);
        $$=new Node("VarList",@$.first_line); $$->push_back($1);}
    ;
ParamDec: Specifier VarDec {$$=new Node("ParamDec",@$.first_line); $$->push_back($1,$2);}
    | VarDec error {
        ierror(@$.first_line, IERROR_TYPE::SPEC);
        Node* spec = new Node("Specifier");
        spec->push_back(new Node("TYPE","int",Node_TYPE::STRING));
        $$=new Node("ParamDec",@$.first_line); $$->push_back(spec,$1);}
    | Specifier error {
        ierror(@$.first_line, IERROR_TYPE::VARDEC);
        Node* var = new Node("VarDec");
        var->push_back(new Node("ID",yytext,Node_TYPE::STRING));
        $$=new Node("ParamDec",@$.first_line); $$->push_back($1,var);}
    ;



/* statement, planning to add scoping */
CompSt: LC CompList RC {
        $$=new Node("CompSt",@$.first_line); 
        $$->push_back($1,$2,$3); 
    }   
    | LC CompList error {
        ierror(@$.first_line, IERROR_TYPE::RC);
        $$=new Node("CompSt",@$.first_line); 
        $$->push_back($1,$2,new Node("RC")); 
    }   
;

Comp: Def {$$=new Node("Comp",@$.first_line); $$->push_back($1);}
    | Stmt {$$=new Node("Comp",@$.first_line); $$->push_back($1);}

CompList: {$$=new Node("CompList",@$.first_line,Node_TYPE::NOTHING);}
    | Comp CompList {$$=new Node("CompList",@$.first_line); $$->push_back($1,$2);}


Stmt: Exp SEMI {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2);}
    | Exp error {ierror(@$.first_line, IERROR_TYPE::SEMI);
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,new Node("SEMI"));}
    | CompSt {
    $$=new Node("Stmt",@$.first_line);$$->push_back($1);}
    | RETURN Exp SEMI {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3);}
    | RETURN Exp error {ierror(@$.first_line, IERROR_TYPE::SEMI);
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,new Node("SEMI"));}
    | IF LP Exp RP Comp %prec LOWER_THAN_ELSE {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3,$4,$5);}
    | IF LP Exp error Comp  {ierror(@$.first_line, IERROR_TYPE::RP);
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3,new Node("RP"),$5);}
    | IF error Exp RP Comp {ierror(@$.first_line, IERROR_TYPE::LP); 
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,new Node("LP"),$3,$4,$5);}
    | IF LP RP Comp error {ierror(@$.first_line, IERROR_TYPE::EXPIF); 
    Node* n = new Node("Exp",@$.first_line);
    n->push_back(new Node("BOOLEAN"));
    n->type = Type::getPrimitiveBOOLEAN();
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,n,$3,$4);}
    | IF LP Exp RP Comp ELSE Comp {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3,$4,$5,$6,$7);}
    | ELSE Comp error {
    ierror(@$.first_line, IERROR_TYPE::IF);
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2);}
    | WHILE LP Exp RP Comp {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3,$4,$5);}
    | WHILE LP RP Comp {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3,$4);}
    | WHILE error Exp RP Comp {ierror(@$.first_line, IERROR_TYPE::LP); 
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,new Node("LP"),$3,$4,$5);}
    | WHILE LP Exp error Comp {ierror(@$.first_line, IERROR_TYPE::RP); 
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3,new Node("RP"),$5);}
    | FOR LP Def Exp SEMI Exp RP Comp {
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, $6, $7, $8);
    }
    | FOR LP Def Exp SEMI Exp error Comp {ierror(@$.first_line, IERROR_TYPE::RP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, $6, new Node("RP"), $8);}
    | FOR error Def Exp SEMI Exp RP Comp {ierror(@$.first_line, IERROR_TYPE::LP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, new Node("LP"), $3, $4, $5, $6, $7, $8);}
    | FOR LP Def Exp SEMI RP Comp {
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, $6, $7);
    }
    | FOR LP Def Exp SEMI error Comp {ierror(@$.first_line, IERROR_TYPE::RP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, new Node("RP"), $7);}
    | FOR error Def Exp SEMI RP Comp {ierror(@$.first_line, IERROR_TYPE::LP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, new Node("LP"), $3, $4, $5, $6, $7);}
    | FOR LP Def SEMI Exp RP Comp {
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, $6, $7);
    }
    | FOR LP Def SEMI Exp error Comp {ierror(@$.first_line, IERROR_TYPE::RP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, new Node("RP"), $7);}
    | FOR error Def SEMI Exp RP Comp {ierror(@$.first_line, IERROR_TYPE::LP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, new Node("LP"), $3, $4, $5, $6, $7);}
    | FOR LP Def SEMI RP Comp {
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, $6);}
    | FOR LP Def SEMI error Comp {ierror(@$.first_line, IERROR_TYPE::RP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, new Node("RP"), $6);}
    | FOR error Def SEMI RP Comp {ierror(@$.first_line, IERROR_TYPE::LP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, new Node("LP"), $3, $4, $5, $6);}
    | FOR LP SEMI Exp SEMI Exp RP Comp {
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, $6, $7, $8);
    }
    | FOR LP SEMI Exp SEMI Exp error Comp {ierror(@$.first_line, IERROR_TYPE::RP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, $6, new Node("RP"), $8);}
    | FOR error SEMI Exp SEMI Exp RP Comp {ierror(@$.first_line, IERROR_TYPE::LP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, new Node("LP"), $3, $4, $5, $6, $7, $8);}
    | FOR LP SEMI Exp SEMI RP Comp {
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, $6, $7);
    }
    | FOR LP SEMI Exp SEMI error Comp {ierror(@$.first_line, IERROR_TYPE::RP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, new Node("RP"), $7);}
    | FOR error SEMI Exp SEMI RP Comp {ierror(@$.first_line, IERROR_TYPE::LP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, new Node("LP"), $3, $4, $5, $6, $7);}
    | FOR LP SEMI SEMI Exp RP Comp {
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, $6, $7);
    }
    | FOR LP SEMI SEMI Exp error Comp {ierror(@$.first_line, IERROR_TYPE::RP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, new Node("RP"), $7);}
    | FOR error SEMI SEMI Exp RP Comp {ierror(@$.first_line, IERROR_TYPE::LP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, new Node("LP"), $3, $4, $5, $6, $7);}
    | FOR LP SEMI SEMI RP Comp {
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, $5, $6);}
    | FOR LP SEMI SEMI error Comp {ierror(@$.first_line, IERROR_TYPE::RP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, $2, $3, $4, new Node("RP"), $6);}
    | FOR error SEMI SEMI RP Comp {ierror(@$.first_line, IERROR_TYPE::LP); 
        $$ = new Node("Stmt", @$.first_line);
        $$->push_back($1, new Node("LP"), $3, $4, $5, $6);}


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
    | Specifier DecList error {
        ierror(@$.first_line, IERROR_TYPE::SEMI);
        $$=new Node("Def",@$.first_line);
        $$->push_back($1,$2,new Node("SEMI"));
        defVisit($$);
    };
    // | %prec LOWER_ERROR DecList SEMI {
    // ierror(@$.first_line, IERROR_TYPE::SPEC);
    // printf("error\n");
    // $$->print();
    // $2->print();
    // }
    
DecList: Dec {$$=new Node("DecList",@$.first_line);$$->push_back($1);}
    | Dec COMMA DecList {
        $$=new Node("DecList",@$.first_line); $$->push_back($1,$2,$3);}
    | Dec DecList error {ierror(@$.first_line, IERROR_TYPE::COMMA);
        $$=new Node("DecList",@$.first_line); $$->push_back($1,new Node("COMMA"),$2);}
;
Dec: VarDec {$$=new Node("Dec",@$.first_line); $$->push_back($1);}
    | VarDec ASSIGN Exp {
    $$=new Node("Dec",@$.first_line); $$->push_back($1,$2,$3);
    // 声明时初始化
    }
    ;
/* Expression */
Args: Exp COMMA Args  {$$=new Node("Args",@$.first_line); $$->push_back($1,$2,$3);}
    | Exp COMMA error  {ierror(@$.first_line, IERROR_TYPE::ARG);
        $$=new Node("Args",@$.first_line); $$->push_back($1);}
    | Exp {$$=new Node("Args",@$.first_line);$$->push_back($1);}
    ;

TernaryStmt:
      Exp TERN Exp COLON Exp {
          $$ = new Node("TernaryStmt", @$.first_line);
          $$->type = $3->type;
          $$->push_back($1, $2, $3, $4, $5);
          if (!checkBoolOperatorType($1)) {
              invalidTernaryOperator(@1.first_line);
          }
          checkTypeMatch($3, $5, @3.first_line);
      }
    // | Exp TERN Exp error Exp {
    //       ierror(@$.first_line, IERROR_TYPE::COLON);
    //       $$ = new Node("TernaryStmt", @$.first_line);
    //       $$->push_back($1, $2, $3, new Node("COLON"), $5); // 临时使用 $3 补充类型
    //   }
    | Exp TERN Exp error {
          ierror(@$.first_line, IERROR_TYPE::EXPTERN);
          $$ = new Node("TernaryStmt", @$.first_line);
          $$->push_back($1, $2, $3, new Node("COLON"), $3); // 临时使用 $3 补充类型
      }
    | Exp TERN error COLON Exp {
          ierror(@$.first_line, IERROR_TYPE::EXPTERN);
          $$ = new Node("TernaryStmt", @$.first_line);
          Node* n = new Node("Exp",@$.first_line);
          n->push_back(new Node("INT"));
          n->type = Type::getPrimitiveINT();
          $$->push_back($1, $2, n, $4, $5);
      }
    | Exp TERN Exp COLON error {
          ierror(@$.first_line, IERROR_TYPE::EXPTERN);
          $$ = new Node("TernaryStmt", @$.first_line);
          Node* n = new Node("Exp",@$.first_line);
          n->push_back(new Node("INT"));
          n->type = Type::getPrimitiveINT();
          $$->push_back($1, $2, $3, $4, n);
      }
    // | Exp error Exp COLON Exp {
    //       ierror(@$.first_line, IERROR_TYPE::TERN);
    //       $$ = new Node("TernaryStmt", @$.first_line);
    //       $$->push_back($1, new Node("TERN"), $3, $4, $5);
    //   };


Exp: Exp ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp ASSIGN error {
    ierror(@$.first_line, IERROR_TYPE::RVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$1);
    checkRvalueInLeftSide($$);
    }
    | ASSIGN Exp error{
    ierror(@$.first_line, IERROR_TYPE::LVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($2,$1,$2);
    }
    | Exp PLUS_ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp PLUS_ASSIGN error {
    ierror(@$.first_line, IERROR_TYPE::RVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$1);
    checkRvalueInLeftSide($$);
    }
    | PLUS_ASSIGN Exp error{
    ierror(@$.first_line, IERROR_TYPE::LVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($2,$1,$2);
    }
    | Exp MINUS_ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp MINUS_ASSIGN error {
    ierror(@$.first_line, IERROR_TYPE::RVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$1);
    checkRvalueInLeftSide($$);
    }
    | MINUS_ASSIGN Exp error{
    ierror(@$.first_line, IERROR_TYPE::LVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($2,$1,$2);
    }
    | Exp MUL_ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp MUL_ASSIGN error {
    ierror(@$.first_line, IERROR_TYPE::RVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$1);
    checkRvalueInLeftSide($$);
    }
    | MUL_ASSIGN Exp error{
    ierror(@$.first_line, IERROR_TYPE::LVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($2,$1,$2);
    }
    | Exp DIV_ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp DIV_ASSIGN error {
    ierror(@$.first_line, IERROR_TYPE::RVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$1);
    checkRvalueInLeftSide($$);
    }
    | DIV_ASSIGN Exp error{
    ierror(@$.first_line, IERROR_TYPE::LVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($2,$1,$2);
    }
    | Exp MOD_ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp MOD_ASSIGN error {
    ierror(@$.first_line, IERROR_TYPE::RVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$1);
    checkRvalueInLeftSide($$);
    }
    | MOD_ASSIGN Exp error{
    ierror(@$.first_line, IERROR_TYPE::LVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($2,$1,$2);
    }
    | Exp BOR_ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp BOR_ASSIGN error {
    ierror(@$.first_line, IERROR_TYPE::RVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$1);
    checkRvalueInLeftSide($$);
    }
    | BOR_ASSIGN Exp error{
    ierror(@$.first_line, IERROR_TYPE::LVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($2,$1,$2);
    }
    | Exp BAND_ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp BAND_ASSIGN error {
    ierror(@$.first_line, IERROR_TYPE::RVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$1);
    checkRvalueInLeftSide($$);
    }
    | BAND_ASSIGN Exp error{
    ierror(@$.first_line, IERROR_TYPE::LVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($2,$1,$2);
    }
    | Exp XOR_ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    }
    | Exp XOR_ASSIGN error {
    ierror(@$.first_line, IERROR_TYPE::RVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$1);
    checkRvalueInLeftSide($$);
    }
    | XOR_ASSIGN Exp error{
    ierror(@$.first_line, IERROR_TYPE::LVALUE);
    $$=new Node("Exp",@$.first_line);
    $$->push_back($2,$1,$2);
    }
    | Exp AND Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getBoolOperatorType($$,$1,$3);}
    | Exp AND error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getBoolOperatorType($$,$1,$1);}
    | Exp OR Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getBoolOperatorType($$,$1,$3);}
    | Exp OR error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getBoolOperatorType($$,$1,$1);}
    | Exp LT Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getComparisonOperatorType($$,$1,$3);}
    | Exp LT error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getComparisonOperatorType($$,$1,$1);}
    | Exp LE Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getComparisonOperatorType($$,$1,$3);}
    | Exp LE error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getComparisonOperatorType($$,$1,$1);}
    | Exp GT Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getComparisonOperatorType($$,$1,$3);}
    | Exp GT error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getComparisonOperatorType($$,$1,$1);}
    | Exp GE Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getComparisonOperatorType($$,$1,$3);}
    | Exp GE error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getComparisonOperatorType($$,$1,$1);}
    | Exp NE Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getComparisonOperatorType($$,$1,$3);}
    | Exp NE error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getComparisonOperatorType($$,$1,$1);}
    | Exp EQ Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getComparisonOperatorType($$,$1,$3);}
    | Exp EQ error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getComparisonOperatorType($$,$1,$1);}
    | Exp MOD Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp MOD error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getAlrthOperatorType($$,$1,$1);}
    | Exp PLUS Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp PLUS error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getAlrthOperatorType($$,$1,$1);}
    | Exp MINUS Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp MINUS error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getAlrthOperatorType($$,$1,$1);}
    | Exp MUL Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp MUL error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getAlrthOperatorType($$,$1,$1);}
    | Exp DIV Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp DIV error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getAlrthOperatorType($$,$1,$1);}
    | Exp BOR Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp BOR error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getAlrthOperatorType($$,$1,$1);}
    | Exp BAND Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp BAND error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getAlrthOperatorType($$,$1,$1);}
    | Exp XOR Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp XOR error {ierror(@$.first_line, IERROR_TYPE::EXPOP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$1);getAlrthOperatorType($$,$1,$1);}
    | LP Exp RP {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);$$->type=$2->type;}
    | LP Exp error {ierror(@$.first_line, IERROR_TYPE::RP);
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,new Node("RP"));$$->type=$2->type;}
    | MINUS Exp %prec LOWER_MINUS {$$=new Node("Exp",@$.first_line);$$->push_back($1,$2);$$->type=$2->type;checkAlrthOperatorType($2);}
    | PLUS Exp %prec LOWER_PLUS {$$=new Node("Exp",@$.first_line);$$->push_back($2);$$->type=$2->type;checkAlrthOperatorType($2);}
    | NOT Exp {
        $$=new Node("Exp",@$.first_line);
        $$->push_back($1,$2);
        $$->type=$2->type;}
    | TernaryStmt {
        $$=$1;
    }
    // | Exp TERN Exp Exp error {
    //     $$=new Node("Exp",@$.first_line); 
    //     $$->type=$3->type;
    //     $$->push_back($1,$2,$3,$4,new Node("COLON")); 
    //     if(!checkBoolOperatorType($1)){
    //         invalidTernaryOperator(@1.first_line);
    //     };
    //     checkTypeMatch($3,$4,@3.first_line);
    // }
    // | Exp Exp COLON Exp error {
    //     $$=new Node("Exp",@$.first_line); 
    //     $$->type=$3->type;
    //     $$->push_back($1,$2,$3,$4,new Node("TERN")); 
    //     if(!checkBoolOperatorType($1)){
    //         invalidTernaryOperator(@1.first_line);
    //     };
    //     checkTypeMatch($2,$4,@2.first_line);
    // }
    // | Exp TERN COLON Exp error{
    //     printf("Wrong ternary declaration!!\n");
    // }
    | ID LP Args RP {

      // If expression is an ID + parantheses, this is a function invoke
      checkInvokeExist($1,@1.first_line);
      checkFunctionParams($1,$3,@3.first_line);

      //append node that resembles the return type of that function   
      $$=new Node("Exp",@$.first_line);
      $$->push_back($1,$2,$3,$4);
      getReturnTypeOfFunction($$,$1);
      }
    | ID LP Args error {ierror(@$.first_line, IERROR_TYPE::RP);
      // If expression is an ID + parantheses, this is a function invoke
      checkInvokeExist($1,@1.first_line);
      checkFunctionParams($1,$3,@3.first_line);

      //append node that resembles the return type of that function   
      $$=new Node("Exp",@$.first_line);
      $$->push_back($1,$2,$3,new Node("RP"));
      getReturnTypeOfFunction($$,$1);
    }
    | ID LP RP {
      checkInvokeExist($1,@1.first_line);
      checkFunctionParams($1,nullptr,@3.first_line);
      $$=new Node("Exp",@$.first_line);
      $$->push_back($1,$2,$3);
      getReturnTypeOfFunction($$,$1);
    }
    | ID LP error {ierror(@$.first_line, IERROR_TYPE::RP);
      checkInvokeExist($1,@1.first_line);
      checkFunctionParams($1,nullptr,@3.first_line);
      $$=new Node("Exp",@$.first_line);
      $$->push_back($1,$2,new Node("RP"));
      getReturnTypeOfFunction($$,$1);
 }
    | Exp LB Exp RB{
        $$=new Node("Exp",@$.first_line);
        $$->push_back($1,$2,$3,$4);
        // LB is [
        checkArrayExists($1);
        getArrayType($$,$1,$3);
    }
    | Exp LB Exp error {ierror(@$.first_line, IERROR_TYPE::RB);
        $$=new Node("Exp",@$.first_line);
        $$->push_back($1,$2,$3,new Node("RB"));
        // LB is [
        checkArrayExists($1);
        getArrayType($$,$1,$3);
    }
    | Exp DOT ID {

        // For checking struct members
        $$=new Node("Exp",@$.first_line);
        $$->push_back($1,$2,$3);
        checkNoSuchMember($$);
        searchAndPutTypeOfDot($$,$1,$3);
    }
    | Exp DOT error {
        ierror(@$.first_line, IERROR_TYPE::FIELD);
        $$=new Node("Exp",@$.first_line);
        Node* id = new Node("ID","Missing_ID",Node_TYPE::STRING);
        $$->push_back($1,$2,id);
        checkNoSuchMember($$);
        searchAndPutTypeOfDot($$,$1,id);
    }
    // | Exp TERN Exp 
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
    ;

%%

void yyerror(const char *s){
    isError=1;
    if(s[0] == 0){}
    // printf("Error at Line %d: %s\n",yylloc.first_line-1, s);
}
