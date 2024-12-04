
#ifndef VISITSYNTAXTREE_HPP
#define VISITSYNTAXTREE_HPP

#include <string>
#include <unordered_map>
#include "type.hpp"
#include "node.hpp"

using std::string;
using std::unordered_map;
extern unordered_map<string, Type *> symbolTable;

void idToExp(Node *exp, Node *id);

void defVisit(Node *node);

void extDefVisit_SES(Node *node);

void extDefVisit_SS(Node *node);

void extDefVisit_SFC(Node *node);

void Specifier_FunDec_Recv_SF(Node *node);

void expVisit(Node *node);

void checkRvalueInLeftSide(Node *node);

void checkIdExists(Node *node, int lineNum);

void funDecVisit(Node *funDec);

void checkNoSuchMember(Node *node);

void searchAndPutTypeOfDot(Node *expOut, Node *expIn, Node *ID);

void checkInvokeExist(Node *node, int lineNum);

void getReturnTypeOfFunction(Node *expOut, Node *ID);

void checkFunctionParams(Node *ID, Node *args, int lineNum);

void checkArrayExists(Node *Exp);

// void checkIntegerExp(Node *Exp);

void getArrayType(Node *expOut, Node *expIn, Node *Integer);

bool checkBoolOperatorType(Node *exp);
//
Node_TYPE checkAlrthOperatorType(Node *exp);

void getBoolOperatorType(Node *expOut, Node *expIn1, Node *expIn2);

void getComparisonOperatorType(Node *expOut, Node *expIn1, Node *expIn2);

void getAlrthOperatorType(Node *expOut, Node *expIn1, Node *expIn2);

void checkTypeMatch(Node *left, Node *right, int lineNum);

void checkReturnValueMatchDeclaredType(Node *extDefSfc);
void defStructTypeVisit(Node *node);

void defPureTypeVisit(Node *node);

string getStrValueFromDecList(Node *node);

void defStructDefinition(Node *node);

void defStructObjectDefinition(Node *node);

FieldList *getFiledListFromDefList(Node *node);

void extDefVisit_SES_PureType(Node *node);

void extDefVisit_SES_StructType(Node *node);

Array *getArrayFromVarDec(Node *node, Type *type);

// func is a single print file
void checkTypeMatchType(Type *leftType, Type *rightType, int lineNum, const std::function<void(int)> &func);

void checkReturnValueFromStmtList(Type *type, Node *stmtList);

void checkReturnValueFromStmt(Type *type, Node *stmt);

void checkReturnValueFromCompStmt(Type *type, Node *compStmt);

void getNamesOfDefList(Node *node, vector<Node *> &namesofFileds);

#endif
