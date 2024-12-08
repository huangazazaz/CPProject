
#ifndef TRANSLATE_HPP
#define TRANSLATE_HPP

#include <string>
#include <unordered_map>
#include "type.hpp"
#include "node.hpp"
#include "interCode.hpp"

using std::string;
using std::unordered_map;
extern unordered_map<string, Type *> symbolTable;

InterCode *translate_Exp(Node *exp, const string &place = "");

InterCode *translate_functionInvoke(Node *stmt);

InterCode *translate_functionWithParamInvoke(Node *stmt);

InterCode *translate_enterFunction(Node *stmt);

InterCode *translate_Return(Node *stmt);

void translate_functionBodyDefine(Node *stmt, Node *Specifier_FunDec_Recv, Node *CompSt);

void translate_CompstMerge(Node *CompSt, Node *CompList);

void translate_StmtlistMerge(Node *StmtList);

void translate_DeflistMerge(Node *StmtList);

void translate_StmtMergeExp(Node *StmtMergeExp);

void translate_ifelse(Node *stmt);

void translate_if(Node *stmt);

void translate_while(Node *stmt);

InterCode *translate_minus_exp(Node *exp);
InterCode *translate_plus_exp(Node *exp);

InterCode *translate_relop(Node *exp, string label_true, string label_false);

InterCode *translate_exp_or_exp(Node *exp, const string &label_true, const string &label_false);

InterCode *translate_varDecAssign(Node *dec);

void translate_DecListMerge(Node *decList);
InterCode *translate_Exp_RightElement(Node *exp, const string &place = "");

InterCode *translate_Exp_INT(Node *intExp);

InterCode *translate_Exp_Bio_Exp(Node *exp);

InterCode *translate_Exp_Assign_Exp(Node *exp);

InterCode *translate_Exp_Comp_Assign_Exp(Node *exp);

void translate_Cond(Node *stmt, string label_true, const string &label_false);

inline void insertAJumpLabelToExpNode(Node *exp, string labelName);

inline void insertAGotoLabelToExpNode(Node *exp, string labelName);

#endif
