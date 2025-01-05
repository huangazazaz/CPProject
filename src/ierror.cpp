
#include "ierror.hpp"

#define PARSER_error_OUTPUT stdout

void ierror(int line, IERROR_TYPE type)
{
    fprintf(PARSER_error_OUTPUT, "Error at Line %d: Missing %s\n", line, ierror_map.at(type).c_str());
}