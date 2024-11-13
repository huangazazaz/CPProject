
#include "ierror.hpp"

#define PARSER_error_OUTPUT stdout

void ierror(int line, IERROR_TYPE type)
{
    fprintf(PARSER_error_OUTPUT, "Missing %s at line %d\n", ierror_map.at(type).c_str(), line);
}