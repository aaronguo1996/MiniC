#include "minic.h"
#include "y.tab.h"

int
yyerror(char const *str)
{
    printf("FROM YYERROR\nLine[%d]: %s\n", minic_get_current_compiler()->current_line_number,str);

    return 0;
}
