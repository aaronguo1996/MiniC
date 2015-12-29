%{
#include <stdio.h>
#include "minic.h"
#include "node.h"
#define YYDEBUG 1

int node_idx = 0;
%}
%union {
    char 		*identifier;
    ParameterList	*parameter_list;
    ArgumentList	*argument_list;
    Expression		*expression;
    ExpressionList	*expression_list;
    Statement		*statement;
    StatementList	*statement_list;
    Block		*block;
    Elseif		*elseif;
    TypeSpecifier	*type_specifier;
    AssignmentOperator	assignment_operator;
    MVM_BasicType	basic_type_specifier;
    ArrayDimension	*array_dimension;
    MemberDeclaration	*member_declaration;
    ClassDefinition     *class_definition;
}
%token <expression>	INT_LITERAL
%token <expression>	DECIMAL_LITERAL
%token <expression>	STRING_LITERAL
%token <expression>	REGEXP_LITERAL
%token <identifier>	IDENTIFIER
%token IF ELSE ELSEIF WHILE DO_T FOR FOREACH RETURN_T BREAK CONTINUE NULL_T NEW
	LP RP LC RC LB RB SEMICOLON COLON COMMA ASSIGN_T LOGICAL_AND LOGICAL_OR
	EQ NE GT GE LT LE ADD SUB MUL DIV MOD TRUE_T FALSE_T EXCLAMATION DOT
	ADD_ASSIGN_T SUB_ASSIGN_T MUL_ASSIGN_T DIV_ASSIGN_T MOD_ASSIGN_T VOID_T
	INCREMENT DECREMENT BOOLEAN_T INT_T DECIMAL_T STRING_T CLASS_T
%type <parameter_list>	parameter_list
%type <argument_list>	argument_list
%type <expression>	expression	expression_opt
			assignment_expression	logical_and_expression
			logical_or_expression	equality_expression
			relational_expression	additive_expression
			multiplicative_expression	unary_expression
			primary_expression	postfix_expression
			array_literal	array_creation	primary_no_new_array
%type <expression_list> expression_list;
%type <statement>	statement	if_statement do_while_statement
			while_statement	for_statement	foreach_statement	
			return_statement break_statement continue_statement	
			declaration_statement
%type <statement_list>	statement_list
%type <block>		block
%type <elseif>		elseif elseif_list
%type <assignment_operator>	assignment_operator
%type <identifier>	identifier_opt
%type <type_specifier>	type_specifier class_type_specifier array_type_specifier
%type <basic_type_specifier>	basic_type_specifier
%type <array_dimension>	dimension_expression	dimension_expression_list
                        dimension_list
%type <member_declaration> member_declaration member_declaration_list
%type <class_definition>  class_definition
%%

program 		: external_declaration_list 
			{ 
			    TreeNode *program = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(program->name,"program");
			    TreeNode *edcl = nodes[--node_idx];
			    program->child = edcl;
			    program->sibling = NULL;
			    nodes[node_idx++] = program;
			    tree = program;
			}
			;
external_declaration_list : external_declaration
			{
			    TreeNode *program = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(program->name,"external_declaration_list");
			    TreeNode *edcl = nodes[--node_idx];
			    program->child = edcl;
			    program->sibling = NULL;
			    nodes[node_idx++] = program;
			}
			| external_declaration_list external_declaration
			{
			    TreeNode *program = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(program->name,"external_declaration_list");
			    TreeNode *edcl = nodes[--node_idx];
			    TreeNode *prog = nodes[--node_idx];
			    prog->sibling = edcl;
			    program->child = prog;
			    program->sibling = NULL;
			    nodes[node_idx++] = program;
			}
			;
external_declaration 	: function_definition
			{
			    TreeNode *fd = nodes[--node_idx];
			    TreeNode *edcl = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(edcl->name,"external_declaration");
			    edcl->child = fd;
			    edcl->sibling = NULL;
			    nodes[node_idx++] = edcl;
			}
			| class_definition
			{
                TreeNode *fd = nodes[--node_idx];
                TreeNode *edcl = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(edcl->name,"external_declaration");
                edcl->child = fd;
                edcl->sibling = NULL;
                nodes[node_idx++] = edcl;
			}
			| statement
			{
			    MINIC_Compiler *compiler = minic_get_current_compiler();
			    compiler->statement_list = minic_chain_statement_list(compiler->statement_list,$1);
			    TreeNode *st = nodes[--node_idx];
			    TreeNode *edcl = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(edcl->name,"external_declaration");
			    edcl->child = st;
			    edcl->sibling = NULL;
			    nodes[node_idx++] = edcl;
			}
			;
basic_type_specifier	: VOID_T
			{
                $$ = MVM_VOID_TYPE;
                TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ts->name,"basic_type_specifier");
                TreeNode *bn = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(bn->name,"void");
                bn->child = NULL;
                bn->sibling = NULL;
                ts->child = bn;
                ts->sibling = NULL;
                nodes[node_idx++] = ts;
			}
			| BOOLEAN_T 
			{ 
			    $$ = MVM_BOOLEAN_TYPE;
			    TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ts->name,"basic_type_specifier");
			    TreeNode *bn = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(bn->name,"boolean");
			    bn->child = NULL;
                bn->sibling = NULL;
                ts->child = bn;
                ts->sibling = NULL;
			    nodes[node_idx++] = ts;
			}
			| INT_T	    
			{ 
			    $$ = MVM_INTEGER_TYPE;
			    TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ts->name,"basic_type_specifier");
			    TreeNode *in = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(in->name,"integer");
			    in->child = NULL;
                in->sibling = NULL;
                ts->child = in;
                ts->sibling = NULL;
			    nodes[node_idx++] = ts;
			}
			| DECIMAL_T 
			{ 
			    $$ = MVM_DECIMAL_TYPE;
			    TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ts->name,"basic_type_specifier");
			    TreeNode *dn = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(dn->name,"decimal");
			    dn->child = NULL;
                dn->sibling = NULL;
                ts->child = dn;
                ts->sibling = NULL;
			    nodes[node_idx++] = ts;
			}
			| STRING_T  
			{ 
			    $$ = MVM_STRING_TYPE;  
			    TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ts->name,"basic_type_specifier");
			    TreeNode *sn = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(sn->name,"string");
			    sn->child = NULL;
                sn->sibling = NULL;
                ts->child = sn;
                ts->sibling = NULL;
			    nodes[node_idx++] = ts;
			}
			;
class_type_specifier	: IDENTIFIER
			{
			    $$ = minic_create_class_type_specifier($1);
			    TreeNode *id = malloc(sizeof(TreeNode));
			    strcpy(id->name,$1);
			    TreeNode *cts = malloc(sizeof(TreeNode));
			    strcpy(cts->name,"class_type_specifier");
			    id->child = NULL;
			    id->sibling = NULL;
			    cts->sibling = NULL;
			    cts->child = id;
			    nodes[node_idx++] = cts;
			}
			;
array_type_specifier	: basic_type_specifier LB RB
			{
			    TypeSpecifier *basic_type
				= minic_create_type_specifier($1);
			    $$ = minic_create_array_type_specifier(basic_type);
			    TreeNode *rb = malloc(sizeof(TreeNode));
			    strcpy(rb->name,"]");
			    rb->child = NULL;
			    rb->sibling = NULL;
			    TreeNode *lb = malloc(sizeof(TreeNode));
			    strcpy(lb->name,"[");
			    lb->child = NULL;
			    TreeNode *bts = nodes[--node_idx];
			    TreeNode *ats = malloc(sizeof(TreeNode));
			    strcpy(ats->name,"array_type_specifier");
			    ats->sibling = NULL;
			    lb->sibling = rb;
			    bts->sibling = lb;
			    ats->child = bts;
		 	    nodes[node_idx++] = ats;
			}
			| IDENTIFIER LB RB
			{
			    TypeSpecifier *class_type
				= minic_create_class_type_specifier($1);
			    $$ = minic_create_array_type_specifier(class_type);
			    TreeNode *rb = malloc(sizeof(TreeNode));
			    strcpy(rb->name,"]");
			    TreeNode *lb = malloc(sizeof(TreeNode));
			    strcpy(lb->name,"[");
			    TreeNode *id = malloc(sizeof(TreeNode));
			    strcpy(id->name,"array_type_specifier");
			    id->child = NULL;
			    lb->child = NULL;
			    rb->child = NULL;
			    rb->sibling = NULL;
			    lb->sibling = rb;
			    id->sibling = lb;
			    TreeNode *ats = malloc(sizeof(TreeNode));
			    strcpy(ats->name,"array_type_specifier");
			    ats->child = id;
			    nodes[node_idx++] = ats;
			}
			| array_type_specifier LB RB
			{
			    $$ = minic_create_array_type_specifier($1);
                TreeNode *rb = malloc(sizeof(TreeNode));
                strcpy(rb->name,"]");
                rb->child = NULL;
                rb->sibling = NULL;
                TreeNode *lb = malloc(sizeof(TreeNode));
                strcpy(lb->name,"[");
                lb->child = NULL;
			    TreeNode *atspc = nodes[--node_idx];
                lb->sibling = rb;
                atspc->sibling = lb;
                TreeNode *ats = malloc(sizeof(TreeNode));
                strcpy(ats->name,"array_type_specifier");
                ats->child = atspc;
                ats->sibling = NULL;
                nodes[node_idx++] = ats;
			}
			;
type_specifier		:basic_type_specifier
			{
			    $$ = minic_create_type_specifier($1);
			    TreeNode *bts = nodes[--node_idx];
			    TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ts->name,"type_specifier");
			    ts->sibling = NULL;
			    ts->child = bts;
			    nodes[node_idx++] = ts;
			}
			| array_type_specifier
			{
			    TreeNode *tspc = nodes[--node_idx];
			    TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ts->name,"type_specifier");
			    ts->child = tspc;
			    ts->sibling = NULL;
			    nodes[node_idx++] = ts;
			}
			| class_type_specifier
			{
                TreeNode *tspc = nodes[--node_idx];
                TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ts->name,"type_specifier");
                ts->child = tspc;
                ts->sibling = NULL;
                nodes[node_idx++] = ts;
			}
			;
function_definition	: type_specifier IDENTIFIER LP parameter_list RP block
			{
			    minic_function_define($1,$2,$4,$6);
			    TreeNode *bnode = nodes[--node_idx];
			    TreeNode *rpNode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(rpNode->name,")");
				rpNode->child = NULL;
			    rpNode->sibling = bnode;
			    TreeNode *plnode = nodes[--node_idx];
			    plnode->sibling = rpNode;
			    TreeNode *lpNode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lpNode->name,"(");
			    lpNode->sibling = plnode;
			    lpNode->child = NULL;
			    TreeNode *idnode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(idnode->name,$2);
			    idnode->sibling = lpNode;
			    idnode->child = NULL;
			    TreeNode *tsnode = nodes[--node_idx];
			    tsnode->sibling = idnode;
			    TreeNode *fdnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(fdnode->name,"function_definition");
			    fdnode->child = tsnode;
			    fdnode->sibling = NULL;
			    nodes[node_idx++] = fdnode;
			    
			}
			| type_specifier IDENTIFIER LP RP block
			{
			    minic_function_define($1,$2,NULL,$5);
			    TreeNode *bnode = nodes[--node_idx];
                TreeNode *rpNode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rpNode->name,")");
				rpNode->child = NULL;
                rpNode->sibling = bnode;
                TreeNode *lpNode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lpNode->name,"(");
                lpNode->sibling = rpNode;
                lpNode->child = NULL;
                TreeNode *idnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(idnode->name,$2);
                idnode->child = NULL;
                idnode->sibling = lpNode;
                TreeNode *tsnode = nodes[--node_idx];
                tsnode->sibling = idnode;
                TreeNode *fdnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(fdnode->name,"function_definition");
                fdnode->child = tsnode;
                fdnode->sibling = NULL;
                nodes[node_idx++] = fdnode;
			}
			| type_specifier IDENTIFIER LP parameter_list RP SEMICOLON
			{
			    minic_function_define($1,$2,$4,NULL);
			    TreeNode *semnode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semnode->name,";");
			    semnode->child = NULL;
			    semnode->sibling = NULL;
                TreeNode *rpNode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rpNode->name,")");
                rpNode->sibling = semnode;
                rpNode->child = NULL;
                TreeNode *plnode = nodes[--node_idx];
                plnode->sibling = rpNode;
                TreeNode *lpNode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lpNode->name,"(");
                lpNode->sibling = plnode;
                lpNode->child = NULL;
                TreeNode *idnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(idnode->name,$2);
                idnode->sibling = lpNode;
                idnode->child = NULL;
                TreeNode *tsnode = nodes[--node_idx];
                tsnode->sibling = idnode;
                TreeNode *fdnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(fdnode->name,"function_definition");
                fdnode->child = tsnode;
                fdnode->sibling = NULL;
                nodes[node_idx++] = fdnode;
			}
			| type_specifier IDENTIFIER LP RP SEMICOLON
			{
			    minic_function_define($1,$2,NULL,NULL);
			    TreeNode *semnode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semnode->name,";");
			    semnode->child = NULL;
			    semnode->sibling = NULL;
                TreeNode *rpNode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rpNode->name,")");
                rpNode->sibling = semnode;
                rpNode->child = NULL;
                TreeNode *lpNode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lpNode->name,"(");
                lpNode->sibling = rpNode;
                lpNode->child = NULL;
                TreeNode *idnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(idnode->name,$2);
                idnode->sibling = lpNode;
                idnode->child = NULL;
                TreeNode *tsnode = nodes[--node_idx];
                tsnode->sibling = idnode;
                TreeNode *fdnode = (TreeNode*)malloc(sizeof(TreeNode));
    			strcpy(fdnode->name,"function_definition");
                fdnode->child = tsnode;
                fdnode->sibling = NULL;
                nodes[node_idx++] = fdnode;
			}
			;
parameter_list		: type_specifier IDENTIFIER
			{
			    $$ = minic_create_parameter($1,$2);
			    TreeNode *idnode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(idnode->name,$2);
			    idnode->child = NULL;
			    idnode->sibling = NULL;
			    TreeNode *tsnode = nodes[--node_idx];
			    tsnode->sibling = idnode;
			    TreeNode *plnode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(plnode->name,"parameter_list");
			    plnode->child = tsnode;
			    plnode->sibling = NULL;
			    nodes[node_idx++] = plnode;
			}
			| parameter_list COMMA type_specifier IDENTIFIER
			{
			    $$ = minic_chain_parameter($1,$3,$4);
			    TreeNode *idnode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(idnode->name,$4);
			    idnode->child = NULL;
			    idnode->sibling = NULL;
			    TreeNode *tsnode = nodes[--node_idx];
			    tsnode->sibling = idnode;
			    TreeNode *comma = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(comma->name,",");
			    comma->sibling = tsnode;
			    comma->child = NULL;
			    TreeNode *pl = nodes[--node_idx];
			    pl->sibling = comma;
			    TreeNode *pll = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(pll->name,"parameter_list");
			    pll->child = pl;
			    pll->sibling = NULL;
			    nodes[node_idx++] = pll;
			}
			;
argument_list		: assignment_expression
			{
			    $$ = minic_create_argument_list($1);
			    TreeNode *ase = nodes[--node_idx];
			    TreeNode *al = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(al->name,"argument_list");
			    al->child = ase;
			    al->sibling = NULL;
			    nodes[node_idx++] = al;
			}
			| argument_list COMMA assignment_expression
			{
			    $$ = minic_chain_argument_list($1,$3);
			    TreeNode *ase = nodes[--node_idx];
			    TreeNode *comma = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(comma->name,",");
			    comma->sibling = ase;
			    comma->child = NULL;
			    TreeNode *arl = nodes[--node_idx];
			    arl->sibling = comma;
			    TreeNode *al = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(al->name,"argument_list");
			    al->child = arl;
			    al->sibling = NULL;
			    nodes[node_idx++] = al;
			}
			;
statement_list		: statement
			{
			    $$ = minic_create_statement_list($1);
			    TreeNode *st = nodes[--node_idx];
			    TreeNode *sl = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(sl->name,"statement_list");
			    sl->child = st;
			    sl->sibling = NULL;
			    nodes[node_idx++] = sl;
			}
			| statement_list statement
			{
			    $$ = minic_chain_statement_list($1,$2);
			    TreeNode *st = nodes[--node_idx];
			    TreeNode *stl = nodes[--node_idx];
			    stl->sibling = st;
			    TreeNode *sl = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(sl->name,"statement_list");
			    sl->child = stl;
			    sl->sibling = NULL;
			    nodes[node_idx++] = sl;
			}
			;
expression		: assignment_expression
			{
			    TreeNode *ase = nodes[--node_idx];
			    TreeNode *exp = (TreeNode*)malloc(sizeof(TreeNode));
			    exp->child = ase;
			    exp->sibling = NULL;
			    strcpy(exp->name,"expression");
			    nodes[node_idx++] = exp;
			}
			| expression COMMA assignment_expression
			{
			    $$ = minic_create_comma_expression($1,$3);
			    TreeNode *ase = nodes[--node_idx];
			    TreeNode *comma = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(comma->name,",");
			    comma->sibling = ase;
			    comma->child = NULL;
			    TreeNode *expr = nodes[--node_idx];
			    expr->sibling = comma;
			    TreeNode *exp = (TreeNode*)malloc(sizeof(TreeNode));
                exp->child = expr;
                exp->sibling = NULL;
                strcpy(exp->name,"expression");
                nodes[node_idx++] = exp;
			}
			;
assignment_expression	: logical_or_expression
			{
			    TreeNode *loe = nodes[--node_idx];
			    TreeNode *ase = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ase->name,"assignment_expression");
			    ase->child = loe;
			    ase->sibling = NULL;
			    nodes[node_idx++] = ase;
			}
			| primary_expression assignment_operator assignment_expression
			{
			    $$ = minic_create_assign_expression($1,$2,$3);
			    TreeNode *ase = nodes[--node_idx];
			    TreeNode *aso = nodes[--node_idx];
			    TreeNode *pe = nodes[--node_idx];
			    aso->sibling = ase;
			    pe->sibling = aso;
			    TreeNode *ae = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ae->name,"assignment_expression");
			    ae->child = pe;
			    ae->sibling = NULL;
			    nodes[node_idx++] = ae;
			}
			;
assignment_operator	: ASSIGN_T	
			{ 
			    $$ = NORMAL_ASSIGN;
			    TreeNode *assign = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(assign->name,":=");
			    assign->child = NULL;
			    assign->sibling = NULL;
			    TreeNode *ao = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ao->name,"assignment_operator");
			    ao->child = assign;
			    ao->sibling = NULL;
			    nodes[node_idx++] = ao;	
			}
			| ADD_ASSIGN_T	
			{
			    $$ = ADD_ASSIGN;
			    TreeNode *assign = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(assign->name,"+=");  
                assign->child = NULL;
			    assign->sibling = NULL;
                TreeNode *ao = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ao->name,"assignment_operator");     
                ao->child = assign;
                ao->sibling = NULL;
                nodes[node_idx++] = ao;
			}
			| SUB_ASSIGN_T	
			{ 
                TreeNode *assign = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(assign->name,"-="); 
                assign->child = NULL;
			    assign->sibling = NULL; 
                TreeNode *ao = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ao->name,"assignment_operator");     
                ao->child = assign;
                ao->sibling = NULL;
                nodes[node_idx++] = ao;
 			    $$ = SUB_ASSIGN;	
			}
			| MUL_ASSIGN_T	
			{ 
			    $$ = MUL_ASSIGN;	
                TreeNode *assign = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(assign->name,"*=");
                assign->child = NULL;
			    assign->sibling = NULL;
                TreeNode *ao = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ao->name,"assignment_operator");     
                ao->child = assign;
                ao->sibling = NULL;
                nodes[node_idx++] = ao;
 			}
			| DIV_ASSIGN_T	
			{ 
			    $$ = DIV_ASSIGN;	
                TreeNode *assign = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(assign->name,"/=");
                assign->child = NULL;
			    assign->sibling = NULL;
                TreeNode *ao = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ao->name,"assignment_operator");     
                ao->child = assign;
                ao->sibling = NULL;
                nodes[node_idx++] = ao;
 			}
			| MOD_ASSIGN_T	
			{ 
			    $$ = MOD_ASSIGN;	
                TreeNode *assign = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(assign->name,"%=");
                assign->child = NULL;
			    assign->sibling = NULL;
                TreeNode *ao = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ao->name,"assignment_operator");     
                ao->child = assign;
                ao->sibling = NULL;
                nodes[node_idx++] = ao;
 			}
logical_or_expression	: logical_and_expression
			{
			    TreeNode *lae = nodes[--node_idx];
			    TreeNode *loe = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(loe->name,"logical_or_expression");
			    loe->child = lae;
			    loe->sibling = NULL;
			    nodes[node_idx++] = loe;
			}
			| logical_or_expression LOGICAL_OR logical_and_expression
			{
			    $$ = minic_create_binary_expression(LOGICAL_OR_EXPRESSION,$1,$3);
			    TreeNode *lae = nodes[--node_idx];
			    TreeNode *logicalor = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(logicalor->name,"||");
			    logicalor->sibling = lae;
			    logicalor->child = NULL;
			    TreeNode *loexp = nodes[--node_idx];
			    loexp->sibling = logicalor;
			    TreeNode *loe = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(loe->name,"logical_or_expression");
			    loe->child = loexp;
			    loe->sibling = NULL;
			    nodes[node_idx++] = loe;
			}
			;
logical_and_expression	: equality_expression
			{
			    TreeNode *eexp = nodes[--node_idx];
			    TreeNode *lae = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lae->name,"logical_and_expression");
			    lae->child = eexp;
			    lae->sibling = NULL;
			    nodes[node_idx++] = lae;
			}
			| logical_and_expression LOGICAL_AND equality_expression
			{
			    $$ = minic_create_binary_expression(LOGICAL_AND_EXPRESSION,$1,$3);
			    TreeNode *eexp = nodes[--node_idx];
			    TreeNode *logicaland = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(logicaland->name,"&&");
			    logicaland->sibling = eexp;
			    logicaland->child = NULL;
			    TreeNode *laexp = nodes[--node_idx];
			    laexp->sibling = logicaland;
			    TreeNode *lae = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lae->name,"logical_and_expression");
			    lae->child = laexp;
			    lae->sibling = NULL;	
			    nodes[node_idx++] = lae;
			}
			;
equality_expression	: relational_expression
			{
			    TreeNode *rexp = nodes[--node_idx];
			    TreeNode *eexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(eexp->name,"equality_expression");
			    eexp->child = rexp;
			    eexp->sibling = NULL;
			    nodes[node_idx++] = eexp;
			}
			| equality_expression EQ relational_expression
			{
			    $$ = minic_create_binary_expression(EQ_EXPRESSION,$1,$3);
			    TreeNode *rexp = nodes[--node_idx];
			    TreeNode *eq = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(eq->name,"=");
			    eq->sibling = rexp;
			    eq->child = NULL;
			    TreeNode *ee = nodes[--node_idx];
			    ee->sibling = eq;
			    TreeNode *eexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(eexp->name,"equlity_expression");
			    eexp->child = ee;
			    eexp->sibling = NULL;
			    nodes[node_idx++] = eexp;
			}
			| equality_expression NE relational_expression
			{
			    $$ = minic_create_binary_expression(NE_EXPRESSION,$1,$3);
			    TreeNode *rexp = nodes[--node_idx];
                TreeNode *eq = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(eq->name,"!=");
                eq->sibling = rexp;
                eq->child = NULL;
                TreeNode *ee = nodes[--node_idx];
                ee->sibling = eq;
                TreeNode *eexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(eexp->name,"equlity_expression");
                eexp->child = ee;
                eexp->sibling = NULL;
                nodes[node_idx++] = eexp;
			}
			;
relational_expression	: additive_expression
			{
			    TreeNode *aexp = nodes[--node_idx];
                TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rexp->name,"relation_expression");
                rexp->child = aexp;
                rexp->sibling = NULL;
                nodes[node_idx++] = rexp;
			}
			| relational_expression GT additive_expression
			{
			    $$ = minic_create_binary_expression(GT_EXPRESSION,$1,$3);
                TreeNode *aexp = nodes[--node_idx];
                TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(gt->name,">");
                gt->sibling = aexp;
                gt->child = NULL;
                TreeNode *re = nodes[--node_idx];
                re->sibling = gt;
                TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rexp->name,"relation_expression");
                rexp->child = re;
                rexp->sibling = NULL;
                nodes[node_idx++] = rexp;
 			}
			| relational_expression GE additive_expression
			{
			    $$ = minic_create_binary_expression(GE_EXPRESSION,$1,$3);
                TreeNode *aexp = nodes[--node_idx];
                TreeNode *ge = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ge->name,">=");
                ge->sibling = aexp;
                ge->child = NULL;
                TreeNode *re = nodes[--node_idx];
                re->sibling = ge;
                TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rexp->name,"relation_expression");
                rexp->child = re;
                rexp->sibling = NULL;
                nodes[node_idx++] = rexp;
  			}
			| relational_expression LT additive_expression
			{
			    $$ = minic_create_binary_expression(LT_EXPRESSION,$1,$3);
                TreeNode *aexp = nodes[--node_idx];
                TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(gt->name,"<");
                gt->sibling = aexp;
                gt->child = NULL;
                TreeNode *re = nodes[--node_idx];
                re->sibling = gt;
                TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rexp->name,"relation_expression");
                rexp->child = re;
                rexp->sibling = NULL;
                nodes[node_idx++] = rexp;
  			}
			| relational_expression LE additive_expression
			{
			    $$ = minic_create_binary_expression(LE_EXPRESSION,$1,$3);
                TreeNode *aexp = nodes[--node_idx];
                TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(gt->name,"<=");
                gt->sibling = aexp;
                gt->child = NULL;
                TreeNode *re = nodes[--node_idx];
                re->sibling = gt;
                TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rexp->name,"relation_expression");
                rexp->child = re;
                rexp->sibling = NULL;
                nodes[node_idx++] = rexp;
  			}
			;
additive_expression	: multiplicative_expression
			{
			    TreeNode *me = nodes[--node_idx];
			    TreeNode *aexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(aexp->name,"additive_expression");
			    aexp->child = me;
			    aexp->sibling = NULL;
			    nodes[node_idx++] = aexp;
			}
			| additive_expression ADD multiplicative_expression
			{
			    $$ = minic_create_binary_expression(ADD_EXPRESSION,$1,$3);
                TreeNode *aexp = nodes[--node_idx];
                TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(gt->name,"+");
                gt->sibling = aexp;
                gt->child = NULL;
                TreeNode *re = nodes[--node_idx];
                re->sibling = gt;
                TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rexp->name,"additive_expression");
                rexp->child = re;
                rexp->sibling = NULL;
                nodes[node_idx++] = rexp;
  			}
			| additive_expression SUB multiplicative_expression
			{
			    $$ = minic_create_binary_expression(SUB_EXPRESSION,$1,$3);
                TreeNode *aexp = nodes[--node_idx];
                TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(gt->name,"-");
                gt->sibling = aexp;
                gt->child = NULL;
                TreeNode *re = nodes[--node_idx];
                re->sibling = gt;
                TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rexp->name,"additive_expression");
                rexp->child = re;
                rexp->sibling = NULL;
                nodes[node_idx++] = rexp;
  			}
			;
multiplicative_expression
			: unary_expression
			{
			    TreeNode *uexp = nodes[--node_idx];
			    TreeNode *me = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(me->name,"multiplicative_expression");
			    me->child = uexp;
			    me->sibling = NULL;
			    nodes[node_idx++] = me;
			}
			| multiplicative_expression MUL unary_expression
			{
			    $$ = minic_create_binary_expression(MUL_EXPRESSION,$1,$3);
                TreeNode *aexp = nodes[--node_idx];
                TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(gt->name,"*");
                gt->sibling = aexp;
                gt->child = NULL;
                TreeNode *re = nodes[--node_idx];
                re->sibling = gt;
                TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rexp->name,"multiplicative_expression");
                rexp->child = re;
                rexp->sibling = NULL;
                nodes[node_idx++] = rexp;
  			}
			| multiplicative_expression DIV unary_expression
			{
			    $$ = minic_create_binary_expression(DIV_EXPRESSION,$1,$3);
                TreeNode *aexp = nodes[--node_idx];
                TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(gt->name,"/");
                gt->sibling = aexp;
                gt->child = NULL;
                TreeNode *re = nodes[--node_idx];
                re->sibling = gt;
                TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rexp->name,"multiplicative_expression");
                rexp->child = re;
                rexp->sibling = NULL;
                nodes[node_idx++] = rexp;
  			}
			| multiplicative_expression MOD unary_expression
			{
			    $$ = minic_create_binary_expression(MOD_EXPRESSION,$1,$3);
                TreeNode *aexp = nodes[--node_idx];
                TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(gt->name,"%");
                gt->sibling = aexp;
                gt->child = NULL;
                TreeNode *re = nodes[--node_idx];
                re->sibling = gt;
                TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rexp->name,"multiplicative_expression");
                rexp->child = re;
                rexp->sibling = NULL;
                nodes[node_idx++] = rexp;
  			}
			;
unary_expression	: postfix_expression
			{
			    TreeNode *postexp = nodes[--node_idx];
			    TreeNode *unaryexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(unaryexp->name,"unary_expression");
			    unaryexp->child = postexp;
			    unaryexp->sibling = NULL;
			    nodes[node_idx++] = unaryexp;
			}
			| SUB unary_expression	
			{ 
			    $$ = minic_create_minus_expression($2);
                TreeNode *exp = nodes[--node_idx];
                TreeNode *sub = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(sub->name,"-");
                sub->sibling = exp;
                sub->child = NULL;
                TreeNode *uexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(uexp->name,"unary_expression");
                uexp->child = sub;
                uexp->sibling = NULL;
                nodes[node_idx++] = uexp;
  
			}
			| EXCLAMATION unary_expression	
			{ 
                TreeNode *exp = nodes[--node_idx];
                TreeNode *sub = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(sub->name,"!");
                sub->sibling = exp;
                sub->child = NULL;
                TreeNode *uexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(uexp->name,"unary_expression");
                uexp->child = sub;
                uexp->sibling = NULL;
                nodes[node_idx++] = uexp;
			    $$ = minic_create_logical_not_expression($2);
			}
			;
postfix_expression	: primary_expression
			{
			    TreeNode *pexp = nodes[--node_idx];
			    TreeNode *postexp = malloc(sizeof(TreeNode));
			    strcpy(postexp->name,"postfix_expression");
			    postexp->child = pexp;
			    postexp->sibling = NULL;
			    nodes[node_idx++] = postexp;
			}
            | primary_expression INCREMENT
            {
                $$ = minic_create_incdec_expression($1,INCREMENT_EXPRESSION);
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,"++");
                rp->child =  NULL;
                rp->sibling = NULL;
                TreeNode *posexp = nodes[--node_idx];
                posexp->sibling = rp;
                TreeNode *postexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(postexp->name,"postfix_expression");
                postexp->child = posexp;
                postexp->sibling = NULL;
                nodes[node_idx++] = postexp;
            }
            | primary_expression DECREMENT
            {
                $$ = minic_create_incdec_expression($1,DECREMENT_EXPRESSION);
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,"--");
                rp->child =  NULL;
                rp->sibling = NULL;
                TreeNode *posexp = nodes[--node_idx];
                posexp->sibling = rp;
                TreeNode *postexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(postexp->name,"postfix_expression");
                postexp->child = posexp;
                postexp->sibling = NULL;
                nodes[node_idx++] = postexp;
            }
			;
primary_expression	: primary_no_new_array
			{
			    TreeNode *pexp = nodes[--node_idx];
			    TreeNode *postexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(postexp->name,"primary_expression");
			    postexp->child = pexp;
			    postexp->sibling = NULL;
			    nodes[node_idx++] = postexp;
			}
			| array_creation
			{
			    TreeNode *ac = nodes[--node_idx];
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"primary_expression");
                pexp->child = ac;
                pexp->sibling =  NULL;
                nodes[node_idx++] = pexp;
			}
            | IDENTIFIER    
            { 
                $$ = minic_create_identifier_expression($1);
                TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(id->name,$1);
                id->child = NULL;
                id->sibling = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"primary_expression");
                pexp->child = id;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
            }
			;
primary_no_new_array	: primary_no_new_array LB expression RB
			{
			    $$ = minic_create_index_expression($1,$3);
			    TreeNode *rb = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(rb->name,"]");
			    rb->child = NULL;
			    rb->sibling = NULL;
			    TreeNode *exp = nodes[--node_idx];
			    TreeNode *lb = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lb->name,"[");
			    lb->child = NULL;
			    TreeNode *pna = nodes[--node_idx];
			    exp->sibling = rb;
			    lb->sibling = exp;
			    pna->sibling = lb;
			    TreeNode *pnna = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(pnna->name,"primary_no_new_array");
			    pnna->child = pna;
			    pnna->sibling = NULL;
			    nodes[node_idx++] = pnna;
			}
			| IDENTIFIER LB expression RB
			{
			    Expression *identifier = minic_create_identifier_expression($1);
			    $$ = minic_create_index_expression(identifier,$3);
			    TreeNode *rb = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rb->name,"]");
                rb->child = NULL;
                rb->sibling = NULL;
                TreeNode *exp = nodes[--node_idx];
                TreeNode *lb = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lb->name,"[");
                lb->child = NULL;
                TreeNode *id = malloc(sizeof(TreeNode));
			    strcpy(id->name,$1);
			    id->child = NULL;
                exp->sibling = rb;
                lb->sibling = exp;
                id->sibling = lb;
                TreeNode *pnna = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pnna->name,"primary_no_new_array");
                pnna->child = id;
                pnna->sibling = NULL;
                nodes[node_idx++] = pnna;
			}
			| primary_expression DOT IDENTIFIER
			{
			    $$ = minic_create_member_expression($1,$3);
			    TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(id->name,$3);
			    id->child = NULL;
			    id->sibling = NULL;
			    TreeNode *dot = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(dot->name,".");
			    dot->child = NULL;
			    TreeNode *pe = nodes[--node_idx];
			    dot->sibling = id;
			    pe->sibling = dot;
			    TreeNode *pnna = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(pnna->name,"primary_no_new_array");
			    pnna->child = pe;
			    pnna->sibling = NULL;
			    nodes[node_idx++] = pnna;
			}
			| primary_expression LP argument_list RP
			{
			    $$ = minic_create_function_call_expression($1,$3);
			    TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(rp->name,")");
				rp->child = NULL;
				rp->sibling = NULL;
			    TreeNode *al = nodes[--node_idx];
			    al->sibling = rp;
			    TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lp->name,"(");
			    lp->sibling = al;
			    lp->child = NULL;
			    TreeNode *posexp = nodes[--node_idx];
			    posexp->sibling = lp;
			    TreeNode *postexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(postexp->name,"primary_no_new_expression");
			    postexp->child = posexp;
			    postexp->sibling = NULL;
			    nodes[node_idx++] = postexp;
			}
			| primary_expression LP RP
			{
			    $$ = minic_create_function_call_expression($1,NULL);
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
				rp->child = NULL;
				rp->sibling = NULL;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = rp;
                lp->child = NULL;
                TreeNode *posexp = nodes[--node_idx];
                posexp->sibling = lp;
                TreeNode *postexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(postexp->name,"primary_no_new_expression");
                postexp->child = posexp;
                postexp->sibling = NULL;
                nodes[node_idx++] = postexp;
			}
			| LP expression RP	
			{ 
			    $$ = $2;
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
				rp->child = NULL;
				rp->sibling = NULL;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = exp;
                lp->child = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"primary_no_new_expression");
                pexp->child = lp;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			     	
			}
			| INT_LITERAL
			{
                TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                sprintf(id->name,"%d",$1->u.integer_value);
                id->child = NULL;
                id->sibling = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"primary_no_new_expression");
                pexp->child = id;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			| DECIMAL_LITERAL
			{
                TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                sprintf(id->name,"%f",$1->u.decimal_value);
                id->child = NULL;
                id->sibling = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"primary_no_new_expression");
                pexp->child = id;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			| STRING_LITERAL
			{
                TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                sprintf(id->name,"%s",$1->u.string_value);
                id->child = NULL;
                id->sibling = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"primary_no_new_expression");
                pexp->child = id;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			| REGEXP_LITERAL
			{
                TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                sprintf(id->name,"%s",$1->u.string_value);
                id->child = NULL;
                id->sibling = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"primary_no_new_expression");
                pexp->child = id;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			| TRUE_T	
			{ 
			    $$ = minic_create_boolean_expression(MVM_TRUE);
                TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(id->name,"true");
                id->child = NULL;
                id->sibling = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"primary_no_new_expression");
                pexp->child = id;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			| FALSE_T	
			{ 
			    $$ = minic_create_boolean_expression(MVM_FALSE);
                TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(id->name,"false");
                id->child = NULL;
                id->sibling = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"primary_no_new_expression");
                pexp->child = id;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			| NULL_T
			{
			    $$ = minic_create_null_expression();
                TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(id->name,"null");
                id->child = NULL;
                id->sibling = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"primary_no_new_expression");
                pexp->child = id;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			| array_literal
			{
                TreeNode *id = nodes[--node_idx];
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"primary_no_new_expression");
                pexp->child = id;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			;
array_literal		: LC expression_list RC
			{
			    $$ = minic_create_array_literal_expression($2);
			    TreeNode *rc = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(rc->name,"}");
			    rc->child = NULL;
			    rc->sibling = NULL;
			    TreeNode *expl = nodes[--node_idx];
			    TreeNode *lc = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lc->name,"{");
			    lc->child = NULL;
			    TreeNode *arrl = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(arrl->name,"array_literal");
			    arrl->sibling = NULL;
			    expl->sibling = rc;
			    lc->sibling = expl;
			    arrl->child = lc;
			    nodes[node_idx++] = arrl;
			}
			| LC expression_list COMMA RC
			{
			    $$ = minic_create_array_literal_expression($2);
                TreeNode *rc = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rc->name,"}");
                rc->child = NULL;
			    rc->sibling = NULL;
			    TreeNode *comma = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(comma->name,",");
			    comma->child = NULL;
                TreeNode *expl = nodes[--node_idx];
                TreeNode *lc = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lc->name,"{");
                lc->child = NULL;
                TreeNode *arrl = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(arrl->name,"array_literal");
                comma->sibling = rc;
    			expl->sibling = comma;
                lc->sibling = expl;
                arrl->child = lc;
                arrl->sibling = NULL;
                nodes[node_idx++] = arrl;
			}
			;
array_creation		: NEW basic_type_specifier dimension_expression_list
			{
			    $$ = minic_create_basic_array_creation($2,$3,NULL);
			    TreeNode *del = nodes[--node_idx];
			    TreeNode *bts = nodes[--node_idx];
			    TreeNode *new = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(new->name,"new");
			    new->child = NULL;
			    TreeNode *ac = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ac->name,"array_creation");
			    bts->sibling = del;
			    new->sibling = bts;
			    ac->child = new;
			    ac->sibling = NULL;
			    nodes[node_idx++] = ac;
			}
			| NEW basic_type_specifier dimension_expression_list dimension_list
			{
			    $$ = minic_create_basic_array_creation($2,$3,$4);
			    TreeNode *dl = nodes[--node_idx];
                TreeNode *del = nodes[--node_idx];
                TreeNode *bts = nodes[--node_idx];
                TreeNode *new = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(new->name,"new");
                new->child = NULL;
                TreeNode *ac = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ac->name,"array_creation");
    			del->sibling = dl;
                bts->sibling = del;
                new->sibling = bts;
                ac->child = new;
                ac->sibling = NULL;
                nodes[node_idx++] = ac;
			}
			|NEW class_type_specifier dimension_expression_list
            {
                $$ = minic_create_class_array_creation($2,$3,NULL);
                TreeNode *del = nodes[--node_idx];
                TreeNode *bts = nodes[--node_idx];
                TreeNode *new = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(new->name,"new");
                new->child = NULL;
                TreeNode *ac = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ac->name,"array_creation");
                bts->sibling = del;
                new->sibling = bts;
                ac->child = new;
                ac->sibling = NULL;
                nodes[node_idx++] = ac;
            }
            | NEW class_type_specifier dimension_expression_list dimension_list
            {
                $$ = minic_create_class_array_creation($2,$3,$4);
                TreeNode *dl = nodes[--node_idx];
                TreeNode *del = nodes[--node_idx];
                TreeNode *bts = nodes[--node_idx];
                TreeNode *new = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(new->name,"new");
                new->child = NULL;
    			TreeNode *ac = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ac->name,"array_creation");
                del->sibling = dl;
                bts->sibling = del;
                new->sibling = bts;
                ac->child = new;
                ac->sibling = NULL;
                nodes[node_idx++] = ac;
            }
			;
dimension_expression_list: dimension_expression
			{
			    TreeNode *de = nodes[--node_idx];
			    TreeNode *del = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(del->name,"dimension_expression_list");
			    del->child = de;
			    del->sibling = NULL;
			    nodes[node_idx++] = del;
			}
			| dimension_expression_list dimension_expression
			{
			    $$ = minic_chain_array_dimension($1,$2);
			    TreeNode *de = nodes[--node_idx];
			    TreeNode *delist = nodes[--node_idx];
			    TreeNode *del = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(del->name,"dimension_expression_list");
                delist->sibling = de;
    			del->child = delist;
    			del->sibling = NULL;
                nodes[node_idx++] = del;
			}
			;
dimension_expression	: LB expression RB
			{
			    $$ = minic_create_array_dimension($2);
			    TreeNode *rb = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(rb->name,"]");
			    rb->child = NULL;
			    rb->sibling = NULL;
			    TreeNode *exp = nodes[--node_idx];
			    TreeNode *lb = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lb->name,"[");
			    lb->child = NULL;
			    TreeNode *dimexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(dimexp->name,"dimension_expression");
			    exp->sibling = rb;
			    lb->sibling = exp;
			    dimexp->child = lb;
			    dimexp->sibling = NULL;
			    nodes[node_idx++] = dimexp;
			}
			;
dimension_list		: LB RB
			{
			    $$ = minic_create_array_dimension(NULL);
			    TreeNode *rb = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rb->name,"]");
                rb->child = NULL;
			    rb->sibling = NULL;
                TreeNode *lb = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lb->name,"[");
                lb->child = NULL;
                TreeNode *dimexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(dimexp->name,"dimension_list");
                lb->sibling = rb;
                dimexp->child = lb;
                dimexp->sibling = NULL;
                nodes[node_idx++] = dimexp;
			}
			| dimension_list LB RB
			{
			    $$ = minic_chain_array_dimension($1,minic_create_array_dimension(NULL));
			    TreeNode *rb = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rb->name,"]");
                rb->child = NULL;
			    rb->sibling = NULL;
                TreeNode *lb = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lb->name,"[");
                lb->child = NULL;
    			TreeNode *dl = nodes[--node_idx];
                TreeNode *dimexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(dimexp->name,"dimension_list");
                lb->sibling = rb;
                dl->sibling = lb;
                dimexp->child = dl;
                dimexp->sibling = NULL;
                nodes[node_idx++] = dimexp;
			}
			;
expression_list		: /* empty */
			{
			    $$ = NULL;
			    TreeNode *empty = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(empty->name,"#");
			    empty->child = NULL;
			    empty->sibling = NULL;
			    TreeNode *expl = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(expl->name,"expression_list");
			    expl->child = empty;
			    expl->sibling = NULL;
			    nodes[node_idx++] = expl;
			}
			| assignment_expression
			{
			    $$ = minic_create_expression_list($1);
			    TreeNode *ae = nodes[--node_idx];
			    TreeNode *expl = (TreeNode*)malloc(sizeof(TreeNode));	
			    strcpy(expl->name,"expression_list");
			    expl->child = ae;
			    expl->sibling =  NULL;
			    nodes[node_idx++] = expl;
			}
			| expression_list COMMA assignment_expression
			{
			    $$ = minic_chain_expression_list($1,$3);
			    TreeNode *ae = nodes[--node_idx];
                TreeNode *comma = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(comma->name,",");
			    comma->child = NULL;
			    TreeNode *explist = nodes[--node_idx];
			    TreeNode *expl = (TreeNode*)malloc(sizeof(TreeNode));                       
                strcpy(expl->name,"expression_list");
			    comma->sibling = ae;
			    explist->sibling = comma;
                expl->child = explist;
                expl->sibling = NULL;
                nodes[node_idx++] = expl;
			}
			;
statement		: expression SEMICOLON
			{
			    $$ = minic_create_expression_statement($1);
			    TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semi->name,";");
			    semi->child = NULL;
			    semi->sibling = NULL;
			    TreeNode *exp = nodes[--node_idx];
			    exp->sibling = semi;
			    TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(statement->name,"statement");
			    statement->child = exp;
			    statement->sibling =  NULL;
			    nodes[node_idx++] = statement;
			}
			| if_statement
			{
			    TreeNode *stmt = nodes[--node_idx];
			    TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(statement->name,"statement");
			    statement->child = stmt;
			    statement->sibling = NULL;
			    nodes[node_idx++] = statement;
			}
			| while_statement
            {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                statement->sibling = stmt;
                nodes[node_idx++] = statement;
            }
			| do_while_statement
            {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                statement->sibling = stmt;
                nodes[node_idx++] = statement;
            }
			| for_statement
            {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                statement->sibling = stmt;
                nodes[node_idx++] = statement;
            }
			| foreach_statement
            {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                statement->sibling = stmt;
                nodes[node_idx++] = statement;
            }
			| return_statement
            {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                statement->sibling = stmt;
                nodes[node_idx++] = statement;
            }
			| break_statement
            {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                statement->sibling = stmt;
                nodes[node_idx++] = statement;
            }
			| continue_statement
            {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                statement->sibling = stmt;
                nodes[node_idx++] = statement;
            }
			| declaration_statement
            {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                statement->sibling = stmt;
                nodes[node_idx++] = statement;
            }
			;
if_statement		: IF LP expression RP block
			{
			    $$ = minic_create_if_statement($3,$5,NULL,NULL);
			    TreeNode *bnode = nodes[--node_idx];
				TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
				strcpy(rp->name,")");
				rp->child = NULL;
				rp->sibling = bnode;
				TreeNode *exp = nodes[--node_idx];
				exp->sibling = rp;
				TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
				strcpy(lp->name,"(");
				lp->sibling = exp;
				lp->child = NULL;
				TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
				strcpy(ifnode->name,"IF");
				ifnode->sibling = lp;
				ifnode->child = NULL;
				TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
				strcpy(pexp->name,"if_statement");
				pexp->child = ifnode;
				pexp->sibling = NULL;
				nodes[node_idx++] = pexp;
			}
			| IF LP expression RP block ELSE block
			{
			    $$ = minic_create_if_statement($3,$5,NULL,$7);
			    TreeNode *block = nodes[--node_idx];
			    TreeNode *elsenode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(elsenode->name,"ELSE");
			    elsenode->sibling = block;
			    elsenode->child = NULL;
                TreeNode *bnode = nodes[--node_idx];
    			bnode->sibling = elsenode;
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                rp->child = NULL;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = exp;
                lp->child = NULL;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"IF");
                ifnode->sibling = lp;
                ifnode->child = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"if_statement");
                pexp->child = ifnode;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			| IF LP expression RP block elseif_list
			{
			    $$ = minic_create_if_statement($3,$5,$6,NULL);
                TreeNode *elsenode = nodes[--node_idx];
                TreeNode *bnode = nodes[--node_idx];
                bnode->sibling = elsenode;
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                rp->child = NULL;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = exp;
                lp->child = NULL;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"IF");
                ifnode->sibling = lp;
                ifnode->child = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"if_statement");
                pexp->child = ifnode;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			| IF LP expression RP block elseif_list ELSE block
			{
			    $$ = minic_create_if_statement($3,$5,$6,$8);
                TreeNode *block = nodes[--node_idx];
                TreeNode *elsenode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(elsenode->name,"ELSE");
                elsenode->sibling = block;
                elsenode->child = NULL;
			    TreeNode *elselist = nodes[--node_idx];
			    elselist->sibling = elsenode;
                TreeNode *bnode = nodes[--node_idx];
                bnode->sibling = elselist;
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                rp->child = NULL;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = exp;
                lp->child = NULL;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"IF");
                ifnode->sibling = lp;
                ifnode->child = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"if_statement");
                pexp->child = ifnode;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			;
elseif_list		: elseif
			{
			    TreeNode *elseifnode = nodes[--node_idx];
			    TreeNode *elselist = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(elselist->name,"elseif_list");
			    elselist->child = elseifnode;
			    elselist->sibling = NULL;
			    nodes[node_idx++] = elselist;
			}
			| elseif_list elseif
			{
			    $$ = minic_chain_elseif_list($1,$2);
			    TreeNode *elseifnode = nodes[--node_idx];
			    TreeNode *elnode = nodes[--node_idx];
			    elnode->sibling = elseifnode;
			    TreeNode *elselist = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(elselist->name,"elseif_list");
			    elselist->child = elnode;
			    elselist->sibling = NULL;
			    nodes[node_idx++] = elselist;
			}
			;
elseif			: ELSEIF LP expression RP block
			{
			    $$ = minic_create_elseif($3,$5);
                TreeNode *bnode = nodes[--node_idx];
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                rp->child = NULL;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = exp;
                lp->child = NULL;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"ELSEIF");
                ifnode->sibling = lp;
                ifnode->child = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"elseif");
                pexp->child = ifnode;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			;
while_statement		: WHILE LP expression RP block
			{
			    $$ = minic_create_while_statement(NULL,$3,$5);
                TreeNode *bnode = nodes[--node_idx];
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                rp->child = NULL;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = exp;
                lp->child = NULL;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"while");
                ifnode->sibling = lp;
                ifnode->child = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"while_statement");
                pexp->child = ifnode;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			;
for_statement		: FOR LP expression_opt SEMICOLON 
			  expression_opt SEMICOLON expression_opt RP block
			{
			    $$ = minic_create_for_statement(NULL,$3,$5,$7,$9);
                TreeNode *bnode = nodes[--node_idx];
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                rp->child = NULL;
                TreeNode *postexp = nodes[--node_idx];
                postexp->sibling = rp;
			    TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semi->name,";");
			    semi->sibling = postexp;
			    semi->child = NULL;
			    TreeNode *condexp = nodes[--node_idx];
			    condexp->sibling = semi;
			    TreeNode *semic = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semic->name,";");
			    semic->sibling = condexp;
			    semic->child = NULL;
			    TreeNode *initexp = nodes[--node_idx];
			    initexp->sibling = semic;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = initexp;
                lp->child = NULL;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"for");
                ifnode->sibling = lp;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"for_statement");
                pexp->child = ifnode;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			;
do_while_statement	: DO_T block WHILE LP expression RP SEMICOLON
			{
			    $$ = minic_create_do_while_statement(NULL,$2,$5);
			    TreeNode *semi = malloc(sizeof(TreeNode));
			    strcpy(semi->name,";");
			    semi->child = NULL;
			    semi->sibling = NULL;
			    TreeNode *rp = malloc(sizeof(TreeNode));
			    strcpy(rp->name,")");
				rp->child = NULL;
			    TreeNode *exp = nodes[--node_idx];
			    TreeNode *lp = malloc(sizeof(TreeNode));
			    strcpy(lp->name,"(");
			    lp->child = NULL;
			    TreeNode *wnode = malloc(sizeof(TreeNode));
			    strcpy(wnode->name,"while");
			    wnode->child = NULL;
			    TreeNode *bnode = nodes[--node_idx];
			    TreeNode *dnode = malloc(sizeof(TreeNode));
			    strcpy(dnode->name,"do");
			    dnode->child = NULL;
			    TreeNode *dwstmt = malloc(sizeof(TreeNode));
			    strcpy(dwstmt->name,"do_while_statement");
			    rp->sibling = semi;
			    exp->sibling = rp;
			    lp->sibling = exp;
			    wnode->sibling = lp;
			    bnode->sibling = wnode;
			    dnode->sibling = bnode;
			    dwstmt->child = dnode;
			    dwstmt->sibling = NULL;
			    nodes[node_idx++] = dwstmt;
			}
			;
foreach_statement	: FOREACH LP IDENTIFIER COLON expression RP block
			{
			    $$ = minic_create_foreach_statement(NULL,$3,$5,$7);
                TreeNode *bnode = nodes[--node_idx];
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                rp->child = NULL;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
			    TreeNode *colon = (TreeNode*)malloc(sizeof(TreeNode));
		  	    strcpy(colon->name,":");
			    colon->sibling = exp;
			    colon->child = NULL;
			    TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(id->name,$3);
			    id->sibling = colon;
			    id->child = NULL;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = id;
                lp->child = NULL;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"foreach");
                ifnode->sibling = lp;
                ifnode->child = NULL;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"foreach_statement");
                pexp->child = ifnode;
                pexp->sibling = NULL;
                nodes[node_idx++] = pexp;
			}
			;
expression_opt		: /* empty */	
			{ 
			    $$ = NULL;
			    TreeNode *empty = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(empty->name,"#");
			    empty->child = NULL;
			    empty->sibling = NULL;
			    TreeNode *eopt = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(eopt->name,"expression_opt");
			    eopt->child = empty;
			    eopt->sibling = NULL;
			    nodes[node_idx++] = eopt;
			}
			| expression
			{
                TreeNode *empty = nodes[--node_idx];
                TreeNode *eopt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(eopt->name,"expression_opt");
                eopt->child = empty;
                eopt->sibling = NULL;
                nodes[node_idx++] = eopt;
			}
			;
return_statement	: RETURN_T expression_opt SEMICOLON
			{
			    $$ = minic_create_return_statement($2);
			    TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semi->name,";");
			    semi->child = NULL;
			    semi->sibling = NULL;
			    TreeNode *exp = nodes[--node_idx];
			    exp->sibling = semi;
			    TreeNode *ret = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ret->name,"return");
			    ret->sibling = exp;
			    ret->child = NULL;
			    TreeNode *retstmt = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(retstmt->name,"return_statement");
			    retstmt->child = ret;
			    retstmt->sibling = NULL;
			    nodes[node_idx++] = retstmt;
			}
			;
identifier_opt		: /* empty */	
			{ 
			    $$ = NULL;
			    TreeNode *empty = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(empty->name,"#");
                empty->child = NULL;
			    empty->sibling = NULL;
                TreeNode *iopt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(iopt->name,"identifier_opt");
                iopt->child = empty;
                iopt->sibling = NULL;
                nodes[node_idx++] = iopt;
			}
			| IDENTIFIER
			{
			    TreeNode *empty = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(empty->name,$1);
                empty->child = NULL;
			    empty->sibling = NULL;
                TreeNode *iopt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(iopt->name,"identifier_opt");
                iopt->child = empty;
                iopt->sibling = NULL;
                nodes[node_idx++] = iopt;
			}
			;
break_statement		: BREAK identifier_opt SEMICOLON
			{
			    $$ = minic_create_break_statement($2);
                TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(semi->name,";");
                semi->child = NULL;
			    semi->sibling = NULL;
                TreeNode *id = nodes[--node_idx];
                id->sibling = semi;
                TreeNode *brea = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(brea->name,"break");
                brea->sibling = id;
                brea->child = NULL;
                TreeNode *retstmt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(retstmt->name,"break_statement");
                retstmt->child = brea;
                retstmt->sibling = NULL;
                nodes[node_idx++] = retstmt;
			}
			;
continue_statement	: CONTINUE identifier_opt SEMICOLON
			{
			    $$ = minic_create_continue_statement($2);
                TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(semi->name,";");
                semi->child = NULL;
			    semi->sibling = NULL;
                TreeNode *id = nodes[--node_idx];
                id->sibling = semi;
                TreeNode *cont = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(cont->name,"continue");
                cont->sibling = id;
                cont->child = NULL;
                TreeNode *retstmt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(retstmt->name,"continue_statement");
                retstmt->child = cont;
                retstmt->sibling = NULL;
                nodes[node_idx++] = retstmt;
			}
			;
declaration_statement	: type_specifier IDENTIFIER SEMICOLON
			{
			    $$ = minic_create_declaration_statement($1,$2,NULL);
                TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
    			strcpy(semi->name,";");
    			semi->child = NULL;
			    semi->sibling = NULL;
                TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(id->name,$2);
                id->sibling = semi;
                id->child = NULL;
			    TreeNode *tsnode = nodes[--node_idx];
		 	    tsnode->sibling = id;
                TreeNode *decstmt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(decstmt->name,"declaration_statement");
                decstmt->child = tsnode;
                decstmt->sibling = NULL;
                nodes[node_idx++] = decstmt;
			}
			| type_specifier IDENTIFIER ASSIGN_T expression SEMICOLON
			{
			    $$ = minic_create_declaration_statement($1,$2,$4);
                            TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semi->name,";");
			    semi->child = NULL;
			    semi->sibling = NULL;
			    TreeNode *exp = nodes[--node_idx];
			    exp->sibling = semi;
			    TreeNode *asst = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(asst->name,":=");
			    asst->sibling = exp;
			    asst->child = NULL;
                TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(id->name,$2);
                id->sibling = asst;
                id->child = NULL;
                TreeNode *tsnode = nodes[--node_idx];
                tsnode->sibling = id;
                TreeNode *decstmt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(decstmt->name,"declaraton_statement");
                decstmt->child = tsnode;
                decstmt->sibling = NULL;
                nodes[node_idx++] = decstmt;
			}
			;
block			: LC
			{
			    $<block>$ = minic_open_block();
			}
			  statement_list RC
			{
			    $<block>$ = minic_close_block($<block>2,$3);
			    TreeNode *rc = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(rc->name,"}");
			    rc->child = NULL;
			    rc->sibling = NULL;
			    TreeNode *sl = nodes[--node_idx];
			    sl->sibling = rc;
			    TreeNode *lc = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lc->name,"{");
			    lc->sibling = sl;
			    lc->child = NULL;
			    TreeNode *block = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(block->name,"block");
			    block->child = lc;
			    block->sibling = NULL;
			    nodes[node_idx++] = block;
			}
			| LC RC
			{
			    Block *empty_block = minic_open_block();
			    $<block>$ = minic_close_block(empty_block,NULL);
                TreeNode *rc = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rc->name,"}");
                rc->child = NULL;
			    rc->sibling = NULL;
                TreeNode *lc = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lc->name,"{");
                lc->sibling = rc;
                lc->child = NULL;
                TreeNode *block = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(block->name,"block");
                block->child = lc;
                block->sibling = NULL;
                nodes[node_idx++] = block;
			}
			;
class_definition	: CLASS_T IDENTIFIER LC member_declaration_list RC
			{
		 	    minic_start_class_definition($2);
			    minic_class_define($4);
			    TreeNode *rc = malloc(sizeof(TreeNode));
			    strcpy(rc->name,"}");
			    rc->child = NULL;
			    rc->sibling = NULL;
			    TreeNode *mdl = nodes[--node_idx];
			    TreeNode *lc = malloc(sizeof(TreeNode));
			    strcpy(lc->name,"{");
			    lc->child = NULL;
			    TreeNode *id = malloc(sizeof(TreeNode));
			    strcpy(id->name,$2);
			    id->child = NULL;
			    TreeNode *class = malloc(sizeof(TreeNode));
			    strcpy(class->name,"structure");
			    class->child = NULL;
			    TreeNode *cd = malloc(sizeof(TreeNode));
			    strcpy(cd->name,"class_definition");
			    cd->sibling = NULL;
			    mdl->sibling = rc;
			    lc->sibling = mdl;
			    id->sibling = lc;
			    class->sibling = id;
			    cd->child = class;
			    nodes[node_idx++] = cd;
			}
			;
member_declaration_list	: member_declaration
			{
			    TreeNode *md = nodes[--node_idx];
			    TreeNode *mdl = malloc(sizeof(TreeNode));
			    strcpy(mdl->name,"member_declaration_list");
			    mdl->child = md;
			    mdl->sibling = NULL;
			    nodes[node_idx++] = mdl;
			}
			| member_declaration_list member_declaration
			{
			    $$ = minic_chain_member_declaration($1,$2);
			    TreeNode *md = nodes[--node_idx];
			    TreeNode *mdlist = nodes[--node_idx];
			    TreeNode *mdl = malloc(sizeof(TreeNode));
			    strcpy(mdl->name,"member_declaration_list");
			    mdlist->sibling = md;
			    mdl->child = mdlist;
			    mdl->sibling = NULL;
			    nodes[node_idx++] = mdl;
			}
			;
member_declaration	: type_specifier IDENTIFIER SEMICOLON
			{
			    $$ = minic_create_field_member($1,$2);
			    TreeNode *semi = malloc(sizeof(TreeNode));
			    strcpy(semi->name,";");
			    semi->child = NULL;
			    semi->sibling = NULL;
			    TreeNode *id = malloc(sizeof(TreeNode));
			    strcpy(id->name,$2);
			    id->child = NULL;
			    TreeNode *ts = nodes[--node_idx];
			    id->sibling = semi;	
			    ts->sibling = id;
			    TreeNode *md = malloc(sizeof(TreeNode));
			    strcpy(md->name,"member_declaration");
			    md->child = ts;
			    md->sibling = NULL;
			    nodes[node_idx++] = md;
			}
			/*| class_or_member_modifier_list type_specifier 
			  IDENTIFIER SEMICOLON
			{
                $$ = minic_create_field_member($1,$2,$3);
                TreeNode *semi = malloc(sizeof(TreeNode));
                strcpy(semi->name,";");
                semi->child = NULL;
			    semi->sibling = NULL;
                TreeNode *id = malloc(sizeof(TreeNode));
                strcpy(id->name,$2);
                id->child = NULL;
                TreeNode *ts = nodes[--node_idx];
                id->sibling = semi;
                ts->sibling = id;
			    TreeNode *comm = nodes[--node_idx];
			    comm->sibling = ts;
                TreeNode *md = malloc(sizeof(TreeNode));
                strcpy(md->name,"member_declaration");
                md->child = comm;
                md->sibling = NULL;
                nodes[node_idx++] = md;
			}*/
			;
%%
