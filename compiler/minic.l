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
//	DBG_panic("bad default, input_mode..%d\n",
//		  minic_get_current_compiler()->input_mode);
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
    FILE *fp;
    fp = fopen("lex","ab");
    fwrite(buf,strlen(buf),1,fp);
    return;
}

%}

%start C_COMMENT CC_COMMENT STRING_LITERAL_STATE SHIFT_JIS_2ND_CHAR
%%
<INITIAL>"if"	{
	char buf[] = "if IF\n";
	output(buf);
	return IF;
}
<INITIAL>"else" {
	char buf[] = "else ELSE\n";
	output(buf);
	return ELSE;
}
<INITIAL>"elseif" {
	char buf[] = "elseif ELSEIF\n";
	output(buf);
	return ELSEIF;
}
<INITIAL>"while" {
	char buf[] = "while WHILE\n";
	output(buf);
	return WHILE;
}
<INITIAL>"for"	{
	char buf[] = "for FOR\n";
	output(buf);
	return FOR;
}
<INITIAL>"do"	{
	char buf[] = "do DO\n";
	output(buf);
	return DO_T;
}
<INITIAL>"foreach" {
	char buf[] = "foreach FOREACH\n";
	output(buf);
	return FOREACH;
}
<INITIAL>"return" {
	char buf[] = "return RETURN_T\n";
	output(buf);
	return RETURN_T;
}
<INITIAL>"break" {
	char buf[] = "break BREAK\n";
	output(buf);
	return BREAK;
}
<INITIAL>"continue" {
	char buf[] = "continue CONTINUE\n";
	output(buf);
	return CONTINUE;
}
<INITIAL>"true" {
	char buf[] = "true TURE_T\n";
	output(buf);
	return TRUE_T;
}
<INITIAL>"false" {
	char buf[] = "false FALSE_T\n";
	output(buf);
	return FALSE_T;
}
<INITIAL>"boolean" {
	char buf[] = "boolean BOOLEAN_T\n";
	output(buf);
	return BOOLEAN_T;
}
<INITIAL>"integer" {
	char buf[] = "integer INT_T\n";
	output(buf);
	return INT_T;
}
<INITIAL>"decimal" {
	char buf[] = "decimal DECIMAL_T\n";
	output(buf);
	return DECIMAL_T;
}
<INITIAL>"string" {
	char buf[] = "string STRING_T\n";
	output(buf);
	return STRING_T;
}
<INITIAL>"new"	{
	char buf[] = "new NEW\n";
	output(buf);
	return NEW;
}
<INITIAL>"null" {
	char buf[] = "null NULL_T\n";
	output(buf);
	return NULL_T;
}
<INITIAL>"void" {
	char buf[] = "void VOID_T\n";
	output(buf);
	return VOID_T;
}
<INITIAL>"struct" {
	char buf[] = "struct CLASS_T\n";
	output(buf);
	return CLASS_T;
}
<INITIAL>"("  {
	char buf[] = "( LP\n";
	output(buf);
	return LP;
}
<INITIAL>")"	{
	char buf[] = ") RP\n";
	output(buf);
	return RP;
}
<INITIAL>"{"	{
	char buf[] = "{ LC\n";
	output(buf);
	return LC;
}
<INITIAL>"}"	{
	char buf[] = "} RC\n";
	output(buf);
	return RC;
}
<INITIAL>"["	{
	char buf[] = "[ LB\n";
	output(buf);
	return LB;
}
<INITIAL>"]"	{
	char buf[] = "] RB\n";
	output(buf);
	return RB;
}
<INITIAL>";"	{
	char buf[] = "; SEMICOLON\n";
	output(buf);
	return SEMICOLON;
}
<INITIAL>":"	{
	char buf[] = ": COLON\n";
	output(buf);
	return COLON;
}
<INITIAL>","	{
	char buf[] = ", COMMA\n";
	output(buf);
	return COMMA;
}
<INITIAL>"&&"	{
	char buf[] = "&& LOGICAL_AND\n";
	output(buf);
	return LOGICAL_AND;
}
<INITIAL>"||"	{
	char buf[] = "|| LOGICAL_OR\n";
	output(buf);
	return LOGICAL_OR;
}
<INITIAL>":="	{
	char buf[] = ":= ASSIGN_T\n";
	output(buf);
	return ASSIGN_T;
}
<INITIAL>"="	{
	char buf[] = "= EQ\n";
	output(buf);
	return EQ;
}
<INITIAL>"!="	{
	char buf[] = "!= NE\n";
	output(buf);
	return NE;
}
<INITIAL>">"	{
	char buf[] = "> GT\n";
	output(buf);
	return GT;
}
<INITIAL>">="	{
	char buf[] = ">= GE\n";
	output(buf);
	return GE;
}
<INITIAL>"<"	{
	char buf[] = "< LT\n";
	output(buf);
	return LT;
}
<INITIAL>"<="	{
	char buf[] = "<= LE\n";
	output(buf);
	return LE;
}
<INITIAL>"+"	{
	char buf[] = "+ ADD\n";
	output(buf);
	return ADD;
}
<INITIAL>"-"	{
	char buf[] = "- SUB\n";
	output(buf);
	return SUB;
}
<INITIAL>"*"	{
	char buf[] = "* MUL\n";
	output(buf);
	return MUL;
}
<INITIAL>"/"	{
	char buf[] = "/ DIV\n";
	output(buf);
	return DIV;
}
<INITIAL>"%"	{
	char buf[] = "% MODE\n";
	output(buf);
	return MOD;
}
<INITIAL>"+="	{
	char buf[] = "+= ADD_ASSIGN_T\n";
	output(buf);
	return ADD_ASSIGN_T;
}
<INITIAL>"-="	{
	char buf[] = "-= SUB_ASSIGN_T\n";
	output(buf);
	return SUB_ASSIGN_T;
}
<INITIAL>"*="	{
	char buf[] = "*= MUL_ASSIGN_T\n";
	output(buf);
	return MUL_ASSIGN_T;
}
<INITIAL>"/="	{
	char buf[] = "/= DIV_ASSIGN_T\n";
	output(buf);
	return DIV_ASSIGN_T;
}
<INITIAL>"%="	{
	char buf[] = "%= MOD_ASSIGN_T\n";
	output(buf);
	return MOD_ASSIGN_T;
}
<INITIAL>"++"	{
	char buf[] = "++ INCREMENT\n";
	output(buf);
	return INCREMENT;
}
<INITIAL>"--"	{
	char buf[] = "-- DECREMENT\n";
	output(buf);
	return DECREMENT;
}
<INITIAL>"!"	{
	char buf[] = "! EXCLAMATION\n";
	output(buf);
	return EXCLAMATION;
}
<INITIAL>"."	{
	char buf[] = ". DOT\n";
	output(buf);
	return DOT;
}
<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
	yylval.identifier = minic_create_identifier(yytext);
	char buf[64];
	sprintf(buf,"%s %s\n",yylval.identifier,"IDENTIFIER");
	output(buf);
	return IDENTIFIER;
}
<INITIAL>[1-9][0-9]* {
	Expression *expression = minic_alloc_expression(INTEGER_EXPRESSION);
	sscanf(yytext, "%d", &expression->u.integer_value);
	yylval.expression = expression;
	char buf[64];
	sprintf(buf,"%s INT_LITERAL\n", yytext);
	output(buf);
	return INT_LITERAL;
}
<INITIAL>"0"[xX][0-9a-fA-F]+ {
	Expression *expression = minic_alloc_expression(INTEGER_EXPRESSION);
	sscanf(yytext, "%x", &expression->u.integer_value);
	yylval.expression = expression;
	char buf[64];
	sprintf(buf,"%s INT_LITERAL\n", yytext);
	output(buf);
	return INT_LITERAL;
}
<INITIAL>"0"  {
	Expression *expression = minic_alloc_expression(INTEGER_EXPRESSION);
	expression->u.integer_value = 0;
	yylval.expression = expression;
	char buf[] = "0 INT LITERAL\n";
	output(buf);
	return INT_LITERAL;
}
<INITIAL>[0-9]+\.[0-9]+ {
	Expression *expression = minic_alloc_expression(DECIMAL_EXPRESSION);
	sscanf(yytext, "%f", &expression->u.decimal_value);
	yylval.expression = expression;
	char buf[64];
	sprintf(buf, "%s DECIMAL_LITERAL\n", yytext);
	output(buf);
	return DECIMAL_LITERAL;
}
<INITIAL>\" {
	char buf[] = "\"  STRING_LITERAL_STATE\n";
	output(buf);
	minic_open_string_literal();
	BEGIN STRING_LITERAL_STATE;
}
<INITIAL>[ ]  {
	char buf[] = "  EMPTY\n";
	output(buf);
}
<INITIAL>\n {
	char buf[] = "\\n \n";
	output(buf);
	increment_line_number();
}
<INITIAL>"/*"	{
	char buf[] = "/* C_COMMENT\n";
	output(buf);
	BEGIN C_COMMENT;
}
<INITIAL>"//"	{
	char buf[] = "// CC_COMMENT\n";
	output(buf);
	BEGIN CC_COMMENT;
}
<INITIAL>.	{
	char buf[LINE_BUF_SIZE];

	if(isprint(yytext[0])) {
		buf[0] = yytext[0];
		buf[1] = '\0';
		output(buf);
	} else {
		sprintf(buf,"0x%02x", (unsigned char)yytext[0]);
		output(buf);
	}
	//minic_compile_error(minic_get_current_compiler()->current_line_number,
	//		    CHARACTER_INVALID_ERR,STRING_MESSAGE_ARGUMENT,
	//		    "bad char",buf,MESSAGE_ARGUMENT_END);
	printf("FROM LEX\nLine[%d]: %s-%c\n",minic_get_current_compiler()->current_line_number,"bad char",yytext[0]);
	exit(-1);;
}
<C_COMMENT>\n	{
	char buf[] = "\\n END_COMMENT\n";
	output(buf);
	increment_line_number();
}
<C_COMMENT>"*/" {
	char buf[] = "*/ END_COMMENT\n";
	output(buf);
	BEGIN INITIAL;
}
<C_COMMENT>.	{
	output(yytext);
}
<CC_COMMENT>\n	{
	char buf[] ="\\n NEW_LINE\n";
	output(buf);
	increment_line_number();
	BEGIN INITIAL;
}
<CC_COMMENT>.	{
	output(yytext);
}
<STRING_LITERAL_STATE>\"	{
	Expression *expression = minic_alloc_expression(STRING_EXPRESSION);
	expression->u.string_value = minic_close_string_literal();
	yylval.expression = expression;
	output(expression->u.string_value);
	BEGIN INITIAL;
	return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\n	{
	minic_add_string_literal('\n');
	increment_line_number();
}
<STRING_LITERAL_STATE>\\\"	minic_add_string_literal('"');
<STRING_LITERAL_STATE>\\n	minic_add_string_literal('\n');
<STRING_LITERAL_STATE>\\t	minic_add_string_literal('\t');
<STRING_LITERAL_STATE>\\\\	minic_add_string_literal('\\');
<STRING_LITERAL_STATE>.	{
	Encoding enc = minic_get_current_compiler()->source_encoding;
	minic_add_string_literal(yytext[0]);
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

