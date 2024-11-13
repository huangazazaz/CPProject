
#include "semanticError.hpp"

void variableNoDefinition(int lineNum, const std::string &name)
{
    printf("Error at Line %d: undefined variable: %s\n", lineNum, name.c_str());
}

void functionNoDefinition(int lineNum, const std::string &name)
{
    printf("Error at Line %d: undefined function: %s\n", lineNum, name.c_str());
}

void variableRedefined(int lineNum, const std::string &name)
{
    printf("Error at Line %d: redefine variable: %s\n", lineNum, name.c_str());
}

void functionRedefined(int lineNum, const std::string &name)
{
    printf("Error at Line %d: redefine function: %s\n", lineNum, name.c_str());
}

void nonMatchTypeBothSide(int lineNum)
{
    printf("Error at Line %d: unmatching types appear at both sides of the assignment operator\n", lineNum);
}

void rvalueLeftSetError(int lineNum)
{
    printf("Error at Line %d: rvalue appears on the left-hand side of the assignment operator\n", lineNum);
}

void binaryOperatorNonNumber(int lineNum)
{
    printf("Error at Line %d: binary operation on non-number variables\n", lineNum);
}

void returnTypeDisMatch(int lineNum)
{
    printf("Error at Line %d: incompatiable return type\n", lineNum);
}

void invalidArgumentNumber(int lineNum, const std::string &name, int expect, int actually)
{
    printf("Error at Line %d: invalid argument number for %s, expect %d, got %d\n", lineNum, name.c_str(),
           expect, actually);
}

void invalidArgumentType(int lineNum, const std::string &name, const std::string &expect, const std::string &actually)
{
    printf("Error at Line %d: invalid argument type for %s, expect %s, got %s\n", lineNum, name.c_str(),
           expect.c_str(), actually.c_str());
}

void indexOnNonArray(int lineNum)
{
    printf("Error at Line %d: indexing on non-array variable\n", lineNum);
}

void invokeNonFunctionVariable(int lineNum, const std::string &name)
{
    printf("Error at Line %d: invoking non-function variable: %s\n", lineNum, name.c_str());
}

void nonIntegerTypeIndexing(int lineNum)
{
    printf("Error at Line %d: indexing by non-integer\n", lineNum);
}

void nonStructFVariable(int lineNum)
{
    printf("Error at Line %d: accessing members of a non-struct variable\n", lineNum);
}

void noSuchMember(int lineNum, const std::string &name)
{
    printf("Error at Line %d: no such member: %s\n", lineNum, name.c_str());
}

void structRedefined(int lineNum, const std::string &name)
{
    printf("Error at Line %d: redefine struct: %s\n", lineNum, name.c_str());
}

void structNoDefinition(int lineNum, const std::string &name)
{
    printf("Error at Line %d: struct %s haven't define\n", lineNum, name.c_str());
}

void invalidTernaryOperator(int lineNum)
{
    printf("Error at Line %d: Invalid ternary condition\n", lineNum);
}