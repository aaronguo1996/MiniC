%{
#undef YY_INPUT
#define YY_INPUT(buf, result, max_size) (result = my_yyinput(buf,max_size))
#include <stdio.h>
#include <string.h>
#include "minic.h"
#include "y.tab.h"

static int
file_input(char *buf, int max_size)
{
    int ch;
    int len;

    if (feof(yyin)) return 0;

    for(len = 0; len < max_size; len++) {
	ch = getc(yyin);
	if(ch == EOF) break;
	buf[len] = ch;
    }
    return len;
}

static char **st_source_string;
static int st_current_source_line;
static int st_current_char_index;

void
minic_set_source_string(char **source)
{
    st_source_string = source;
    //source_code = malloc(CODE_SIZE);
    st_current_source_line = 0;
    st_current_char_index = 0;
}

static int
string_input(char *buf, int max_size)
{
    int len;
    if(st_source_string[st_current_source_line][st_current_char_index]
        == '\0'){
	st_current_source_line++;
	st_current_char_index = 0;
    }
    
    if(st_source_string[st_current_source_line] == NULL) return 0;
    
    len = smaller(strlen(st_source_string[st_current_source_line])
		  - st_current_char_index,
		  max_size);
    strncpy(buf,
            &st_source_string[st_current_source_line][st_current_char_index],
	    len);
    st_current_char_index += len;

    return len;
}

static int
my_yyinput(char *buf, int max_size)
{
    int result;
    
    switch (minic_get_current_compiler()->input_mode) {
    case MINIC_FILE_INPUT_MODE:
	result = file_input(buf, max_size);
	break;
    case MINIC_STRING_INPUT_MODE:
	result = string_input(buf, max_size);
	break;
    default:
	break;
    }

    return result;
}

int
yywrap(void)
{
    return 1;
}

static void
increment_line_number(void)
{
    minic_get_current_compiler()->current_line_number++;
}

static void
output(char *buf)
{
    strcat(source_code,buf);
    //printf("%s\n",source_code);
    return;
}

%}

%start C_COMMENT CC_COMMENT FILE_NAME STRING_LITERAL_STATE SHIFT_JIS_2ND_CHAR
%%
<INITIAL>"if"	{
	char buf[] = "if IF\t";
	output(buf);
	return IF;
}
<INITIAL>"else" {
	char buf[] = "else ELSE\t";
	output(buf);
	return ELSE;
}
<INITIAL>"elseif" {
	char buf[] = "elseif ELSEIF\t";
	output(buf);
	return ELSEIF;
}
<INITIAL>"while" {
	char buf[] = "while WHILE\t";
	output(buf);
	return WHILE;
}
<INITIAL>"for"	{
	char buf[] = "for FOR\t";
	output(buf);
	return FOR;
}
<INITIAL>"do"	{
	char buf[] = "do DO\t";
	output(buf);
	return DO_T;
}
<INITIAL>"foreach" {
	char buf[] = "foreach FOREACH\t";
	output(buf);
	return FOREACH;
}
<INITIAL>"return" {
	char buf[] = "return RETURN_T\t";
	output(buf);
	return RETURN_T;
}
<INITIAL>"break" {
	char buf[] = "break BREAK\t";
	output(buf);
	return BREAK;
}
<INITIAL>"continue" {
	char buf[] = "continue CONTINUE\t";
	output(buf);
	return CONTINUE;
}
<INITIAL>"true" {
	char buf[] = "true TURE_T\t";
	output(buf);
	return TRUE_T;
}
<INITIAL>"false" {
	char buf[] = "false FALSE_T\t";
	output(buf);
	return FALSE_T;
}
<INITIAL>"boolean" {
	char buf[] = "boolean BOOLEAN_T\t";
	output(buf);
	return BOOLEAN_T;
}
<INITIAL>"integer" {
	char buf[] = "integer INT_T\t";
	output(buf);
	return INT_T;
}
<INITIAL>"decimal" {
	char buf[] = "decimal DECIMAL_T\t";
	output(buf);
	return DECIMAL_T;
}
<INITIAL>"string" {
	char buf[] = "string STRING_T\t";
	output(buf);
	return STRING_T;
}
<INITIAL>"new"	{
	char buf[] = "new NEW\t";
	output(buf);
	return NEW;
}
<INITIAL>"null" {
	char buf[] = "null NULL_T\t";
	output(buf);
	return NULL_T;
}
<INITIAL>"void" {
	char buf[] = "void VOID_T\t";
	output(buf);
	return VOID_T;
}
<INITIAL>"structure" {
	char buf[] = "structure CLASS_T\t";
	output(buf);
	return CLASS_T;
}
<INITIAL>"reference" {
	char buf[] = "reference REFERENCE\t";
	output(buf);
	BEGIN FILE_NAME;
}
<INITIAL>"("  {
	char buf[] = "( LP\t";
	output(buf);
	return LP;
}
<INITIAL>")"	{
	char buf[] = ") RP\t";
	output(buf);
	return RP;
}
<INITIAL>"{"	{
	char buf[] = "{ LC\t";
	output(buf);
	return LC;
}
<INITIAL>"}"	{
	char buf[] = "} RC\t";
	output(buf);
	return RC;
}
<INITIAL>"["	{
	char buf[] = "[ LB\t";
	output(buf);
	return LB;
} 
<INITIAL>"]"	{
	char buf[] = "] RB\t";
	output(buf);
	return RB;
}
<INITIAL>";"	{
	char buf[] = "; SEMICOLON\t";
	output(buf);
	return SEMICOLON;
}
<INITIAL>":"	{
	char buf[] = ": COLON\t";
	output(buf);
	return COLON;
}
<INITIAL>","	{
	char buf[] = ", COMMA\t";
	output(buf);
	return COMMA;
}
<INITIAL>"&&"	{
	char buf[] = "&& LOGICAL_AND\t";
	output(buf);
	return LOGICAL_AND;
}
<INITIAL>"||"	{
	char buf[] = "|| LOGICAL_OR\t";
	output(buf);
	return LOGICAL_OR;
}
<INITIAL>":="	{
	char buf[] = ":= ASSIGN_T\t";
	output(buf);
	return ASSIGN_T;
}
<INITIAL>"="	{
	char buf[] = "= EQ\t";
	output(buf);
	return EQ;
}
<INITIAL>"!="	{
	char buf[] = "!= NE\t";
	output(buf);
	return NE;
}
<INITIAL>">"	{
	char buf[] = "> GT\t";
	output(buf);
	return GT;
}
<INITIAL>">="	{
	char buf[] = ">= GE\t";
	output(buf);
	return GE;
}
<INITIAL>"<"	{
	char buf[] = "< LT\t";
	output(buf);
	return LT;
}
<INITIAL>"<="	{
	char buf[] = "<= LE\t";
	output(buf);
	return LE;
}
<INITIAL>"+"	{
	char buf[] = "+ ADD\t";
	output(buf);
	return ADD;
}
<INITIAL>"-"	{
	char buf[] = "- SUB\t";
	output(buf);
	return SUB;
}
<INITIAL>"*"	{
	char buf[] = "* MUL\t";
	output(buf);
	return MUL;
}
<INITIAL>"/"	{
	char buf[] = "/ DIV\t";
	output(buf);
	return DIV;
}
<INITIAL>"%"	{
	char buf[] = "% MODE\t";
	output(buf);
	return MOD;
}
<INITIAL>"+="	{
	char buf[] = "+= ADD_ASSIGN_T\t";
	output(buf);
	return ADD_ASSIGN_T;
}
<INITIAL>"-="	{
	char buf[] = "-= SUB_ASSIGN_T\t";
	output(buf);
	return SUB_ASSIGN_T;
}
<INITIAL>"*="	{
	char buf[] = "*= MUL_ASSIGN_T\t";
	output(buf);
	return MUL_ASSIGN_T;
}
<INITIAL>"/="	{
	char buf[] = "/= DIV_ASSIGN_T\t";
	output(buf);
	return DIV_ASSIGN_T;
}
<INITIAL>"%="	{
	char buf[] = "%= MOD_ASSIGN_T\t";
	output(buf);
	return MOD_ASSIGN_T;
}
<INITIAL>"++"	{
	char buf[] = "++ INCREMENT\t";
	output(buf);
	return INCREMENT;
}
<INITIAL>"--"	{
	char buf[] = "-- DECREMENT\t";
	output(buf);
	return DECREMENT;
}
<INITIAL>"!"	{
	char buf[] = "! EXCLAMATION\t";
	output(buf);
	return EXCLAMATION;
}
<INITIAL>"."	{
	char buf[] = ". DOT\t";
	output(buf);
	return DOT;
}
<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
	yylval.identifier = minic_create_identifier(yytext);
	char buf[64];
	sprintf(buf,"%s %s\t",yylval.identifier,"IDENTIFIER");
	output(buf);
	return IDENTIFIER;
}
<INITIAL>[1-9][0-9]* {
	Expression *expression = minic_alloc_expression(INTEGER_EXPRESSION);
	sscanf(yytext, "%d", &expression->u.integer_value);
	yylval.expression = expression;
	char buf[64];
	sprintf(buf,"%s INT_LITERAL\t", yytext);
	output(buf);
	return INT_LITERAL;
}
<INITIAL>"0"[xX][0-9a-fA-F]+ {
	Expression *expression = minic_alloc_expression(INTEGER_EXPRESSION);
	sscanf(yytext, "%x", &expression->u.integer_value);
	yylval.expression = expression;
	char buf[64];
	sprintf(buf,"%s INT_LITERAL\t", yytext);
	output(buf);
	return INT_LITERAL;
}
<INITIAL>"0"  {
	Expression *expression = minic_alloc_expression(INTEGER_EXPRESSION);
	expression->u.integer_value = 0;
	yylval.expression = expression;
	char buf[] = "0 INT LITERAL\t";
	output(buf);
	return INT_LITERAL;
}
<INITIAL>[0-9]+\.[0-9]+ {
	Expression *expression = minic_alloc_expression(DECIMAL_EXPRESSION);
	sscanf(yytext, "%f", &expression->u.decimal_value);
	yylval.expression = expression;
	char buf[64];
	sprintf(buf, "%s DECIMAL_LITERAL\t", yytext);
	output(buf);
	return DECIMAL_LITERAL;
}
<INITIAL>\" {
	char buf[] = "\"  STRING_LITERAL_STATE\t";
	output(buf);
	minic_open_string_literal();
	BEGIN STRING_LITERAL_STATE;
}
<INITIAL>[ ]  {
}
<INITIAL>\n {
	char buf[] = "\\n NEW_LINE\t";
	output(buf);
	increment_line_number();
}
<INITIAL>"/*"	{
	char buf[] = "/* C_COMMENT\t";
	output(buf);
	BEGIN C_COMMENT;
}
<INITIAL>"//"	{
	char buf[] = "// CC_COMMENT\t";
	output(buf);
	BEGIN CC_COMMENT;
}
<INITIAL>.	{
	char buf[LINE_BUF_SIZE];
	char str[LINE_BUF_SIZE];
	if(isprint(yytext[0])) {
		buf[0] = yytext[0];
		buf[1] = '\t';
	} else {
		sprintf(buf,"0x%02x", (unsigned char)yytext[0]);
	}
	sprintf(str,"%s\t",buf);
	output(str);
	//minic_compile_error(minic_get_current_compiler()->current_line_number,
	//		    CHARACTER_INVALID_ERR,STRING_MESSAGE_ARGUMENT,
	//		    "bad char",buf,MESSAGE_ARGUMENT_END);
	printf("FROM LEX\nLine[%d]: %s - %c\n",minic_get_current_compiler()->current_line_number,"bad char",yytext[0]);
	exit(-1);
}
<C_COMMENT>\n	{
	char buf[] = "\\n END_COMMENT\t";
	output(buf);
	increment_line_number();
}
<C_COMMENT>"*/" {
	char buf[] = "*/ END_COMMENT\t";
	output(buf);
	BEGIN INITIAL;
}
<C_COMMENT>.	{
	char buf[LINE_BUF_SIZE];
	sprintf(buf,"%s\t",yytext);
	output(buf);
}
<CC_COMMENT>\n	{
	char buf[] ="\\n NEW_LINE\t";
	output(buf);
	increment_line_number();
	BEGIN INITIAL;
}
<CC_COMMENT>.	{
	output(yytext);
}

<FILE_NAME>[ ]  {
}

<FILE_NAME>[A-Za-z_][A-Za-z_0-9]*+\.[A-Za-z]*  {
	char buf[LINE_BUF_SIZE];
	sprintf(buf,"%s\t",yytext);
	output(buf);
}

<FILE_NAME>";" {
	char buf[] = "; SEMICOLON\t";
	output(buf);
	BEGIN INITIAL;
}

<STRING_LITERAL_STATE>\"	{
	Expression *expression = minic_alloc_expression(STRING_EXPRESSION);
	expression->u.string_value = minic_close_string_literal();
	yylval.expression = expression;
	char buf[] = "\"  END_LITERAL_STATE\t";
	output(buf);
	BEGIN INITIAL;
	return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\n	{
	minic_add_string_literal('\n');
	output("\\n STR_NEW_LINE\t");
	increment_line_number();
}
<STRING_LITERAL_STATE>\\\"	{
	minic_add_string_literal('"');
	output("\\\" STR_SLASH\t");
}
<STRING_LITERAL_STATE>\\n	{
	minic_add_string_literal('\n');
	output("\\n STRING\t");
}
<STRING_LITERAL_STATE>\\t	{
	minic_add_string_literal('\t');
	output("\\t STRING\t");
}
<STRING_LITERAL_STATE>\\\\	{
	minic_add_string_literal('\\');
	output("\\\\ STRING\t");
}
<STRING_LITERAL_STATE>.	{
	Encoding enc = minic_get_current_compiler()->source_encoding;
	minic_add_string_literal(yytext[0]);
	char buf[64];
	sprintf(buf,"%c STRING\t",yytext[0]);
	output(buf);
	if(enc == SHIFT_JIS_ENCODING && ((((unsigned char*)yytext)[0] >= 0x81
             && ((unsigned char*)yytext)[0] <= 0x9e)
            || (((unsigned char*)yytext)[0] >= 0xe0
                && ((unsigned char*)yytext)[0] <= 0xef))) {
        BEGIN SHIFT_JIS_2ND_CHAR;
    }
}
<SHIFT_JIS_2ND_CHAR>. {
    minic_add_string_literal(yytext[0]);
    BEGIN STRING_LITERAL_STATE;
}
%%
