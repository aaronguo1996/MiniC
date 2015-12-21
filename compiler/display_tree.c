#include "minic.h"
#include "y.tab.h"

#define MAX_BUFFER_SIZE 1024

int error_message(char *error_stage, char *error_msg)
{
    printf("fail to display %s : %s\n",error_stage, error_msg);
    return -1;
}

int display_statement(FILE *fp)
{
    return 0;
}

int display_specifier(FILE *fp)
{
    return 0;
}

int display_function_definition(FILE *fp,FunctionDefinition *fd)
{
    return 0;
}

int display_external_declaration(FILE *fp)
{
    return 0;
}
    
int display_program()
{
    return 0;
}
