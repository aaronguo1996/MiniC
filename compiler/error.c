#include "minic.h"
#include "y.tab.h"

int
yyerror(char const *str)
{
	FILE *fp = fopen("error.info","at");
    fprintf(fp,"FROM YYERROR\nLine[%d]: %s\n", minic_get_current_compiler()->current_line_number,str);

    return 0;
}
