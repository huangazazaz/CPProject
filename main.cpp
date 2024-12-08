#include "syntax.tab.c"

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        fprintf(PARSER_error_OUTPUT, "no input path");
        return 1;
    }
    else if (argc > 3)
    {
        fprintf(PARSER_error_OUTPUT, "too much input path");
        return 1;
    }
    else
    {
        FILE *f = fopen(argv[1], "r");
        if (!f)
        {
            fprintf(PARSER_error_OUTPUT, "error of path %s", argv[1]);
            return 1;
        }
        yyrestart(f);
        yyparse();
    }
    if (isError == 0 && is_sem_error == 0)
    {
        if (argv[2][0] == '3')
        {
            for (Node *node : ircodes)
            {
                node->print_vector_intercode();
            }
        }
        else
            root_node->print(0);
        // std::cout << symbolTable.size() << std::endl;
    }
    return 0;
}