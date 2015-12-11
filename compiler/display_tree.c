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
    buf[] = "<tr>\n<td>";
    return 0;
}

int display_function_definition(FILE *fp,FunctionDefinition *fd)
{
    FunctionDefinition *pos;

    //type_specifier IDENTIFIER LP parameter_list RP block
    //type_specifier IDENTIFIER LP RP block
    //type_specifier IDENTIFIER LP parameter_list RP SEMICOLON
    //type_specifier IDENTIFIER LP RP SEMICOLON
    buf[] = "<tr>\n<td>Type Specifier</td><td>IDENTIFIER</td><td>LP</td>";
    if(fd->parameter){
	strcat(buf,"<td>Parameter List</td>");
    }
    //display_parameter_list(fp,pl);
    strcat(buf,"<td>RP</td>");
    if(fd->block){
	strcat(buf,"<td>Block</td>");
    }
    //display_block(fp,block);
    else{
	strcat(buf,"<td>SEMICOLON</td>");
    }
    //display_type_specifier(fp);
    //sprintf("<tr>\n<td>%s</td><td>%s</td>\n</tr>\n",);

    return 0;
}

int display_external_declaration(FILE *fp)
{
    if(display_function_definition(fp,minic_get_current_compiler()->function_list) == -1)
    	return error_message("external declaration","function_definition fail");
    if(display_statement(fp) == -1)
	return error_message("external declaration","statement fail");
    return 0;
}
    
int display_program()
{
    FILE *fp;
    if((fp = fopen("parse_tree.html","w+")) == NULL)
    {
	printf("fail to fopen: %s\n", "parse_tree.html");
	return -1;
    }
    char buf[] = "<html>\n<body>\n<h1>Parse Tree Of MiniC</h1>\n<table><tr><td>Program</td></tr>\n";
    fwrite(buf,strlen(buf),1,fp);
    fclose(fp);
    return 0;
}
