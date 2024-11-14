
#ifndef SEMANTICERROR_HPP
#define SEMANTICERROR_HPP

#include <string>
#include <unordered_map>

void variableNoDefinition(int lineNum, const std::string &name);

void functionNoDefinition(int lineNum, const std::string &name);

void variableRedefined(int lineNum, const std::string &name);

void functionRedefined(int lineNum, const std::string &name);

void nonMatchTypeBothSide(int lineNum);

void rvalueLeftSetError(int lineNum);

void binaryOperatorNonNumber(int lineNum);

void returnTypeDisMatch(int lineNum);

void invalidArgumentNumber(int lineNum, const std::string &name, int expect, int actually);

void invalidArgumentType(int lineNum, const std::string &name, const std::string &expect, const std::string &actually);

void indexOnNonArray(int lineNum);

void invokeNonFunctionVariable(int lineNum, const std::string &name);

void nonIntegerTypeIndexing(int lineNum);

void nonStructFVariable(int lineNum);

void noSuchMember(int lineNum, const std::string &name);

void structRedefined(int lineNum, const std::string &name);

void structNoDefinition(int lineNum, const std::string &name);

void invalidTernaryOperator(int lineNum);

#endif