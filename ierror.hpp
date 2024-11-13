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
    SPEC,
    SEMI,
    COMMA
};

const std::unordered_map<IERROR_TYPE, std::string> ierror_map = {
    {IERROR_TYPE::RC, R"(closing curly braces  })"},
    {IERROR_TYPE::RB, R"(closing bracket ])"},
    {IERROR_TYPE::RP, R"(closing parenthesis ))"},
    {IERROR_TYPE::LC, R"(left curly braces  {)"},
    {IERROR_TYPE::LB, R"(left bracket [)"},
    {IERROR_TYPE::LP, R"(left parenthesis ()"},
    {IERROR_TYPE::SPEC, R"(specifier)"},
    {IERROR_TYPE::SEMI, R"(semicolon ;)"},
    {IERROR_TYPE::COMMA, R"(COMMA ,)"},
};

void ierror(int line, IERROR_TYPE type);

#endif
