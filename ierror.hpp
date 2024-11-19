#ifndef IERROR_HPP
#define IERROR_HPP

#include <string>
#include <unordered_map>

enum class IERROR_TYPE
{
    RC,
    RB,
    RP,
    LC,
    LB,
    LP,
    RVALUE,
    LVALUE,
    VAR,
    ARG,
    VARDEC,
    FIELD,
    SPEC,
    SEMI,
    COMMA,
    EXPMUL,
    EXPDIV,
    EXPPLUS,
    EXPMINUS,
    EXPMOD,
    EXPBOR,
    EXPBAND,
    EXPXOR,
    EXPIF,
    EXPWHILE,
    EXPTERN,
    IF,
    COLON,
};

const std::unordered_map<IERROR_TYPE, std::string> ierror_map = {
    {IERROR_TYPE::RC, R"(closing curly braces  '}')"},
    {IERROR_TYPE::RB, R"(closing bracket ']')"},
    {IERROR_TYPE::RP, R"(closing parenthesis ')')"},
    {IERROR_TYPE::LC, R"(left curly braces  '{')"},
    {IERROR_TYPE::LB, R"(left bracket '[')"},
    {IERROR_TYPE::LP, R"(left parenthesis '(')"},
    {IERROR_TYPE::COLON, R"(colon ':')"},
    {IERROR_TYPE::LVALUE, R"(left value)"},
    {IERROR_TYPE::RVALUE, R"(right value)"},
    {IERROR_TYPE::VAR, R"(variable)"},
    {IERROR_TYPE::ARG, R"(argument)"},
    {IERROR_TYPE::VARDEC, R"(variable name)"},
    {IERROR_TYPE::FIELD, R"(field)"},
    {IERROR_TYPE::SPEC, R"(specifier)"},
    {IERROR_TYPE::SEMI, R"(semicolon ';')"},
    {IERROR_TYPE::COMMA, R"(comma ',')"},
    {IERROR_TYPE::EXPMUL, R"(Exp after *)"},
    {IERROR_TYPE::EXPDIV, R"(Exp after /)"},
    {IERROR_TYPE::EXPPLUS, R"(Exp after +)"},
    {IERROR_TYPE::EXPMINUS, R"(Exp after -)"},
    {IERROR_TYPE::EXPMOD, R"(Exp after %)"},
    {IERROR_TYPE::EXPBOR, R"(Exp after |)"},
    {IERROR_TYPE::EXPBAND, R"(Exp after &)"},
    {IERROR_TYPE::EXPXOR, R"(Exp after ^)"},
    {IERROR_TYPE::EXPIF, R"(Exp in if)"},
    {IERROR_TYPE::EXPWHILE, R"(Exp in while)"},
    {IERROR_TYPE::EXPTERN, R"(Exp in ternary)"},
    {IERROR_TYPE::IF, R"('if' before 'else')"},
};

void ierror(int line, IERROR_TYPE type);

#endif
