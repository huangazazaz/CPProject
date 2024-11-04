
#include "ierror.hpp"

#define PARSER_error_OUTPUT stdout

void ierror(IERROR_TYPE type)
{
    fprintf(PARSER_error_OUTPUT, "Missing %s\n", ierror_map.at(type).c_str());
}