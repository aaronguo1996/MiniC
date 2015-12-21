#include "minic.h"
#include "node.h"

DeclarationList *
minic_chain_declaration(DeclarationList *list, Declaration *decl)
{
	DeclarationList *new_item;
	DeclarationList	*pos;
	
	new_item = malloc(sizeof(DeclarationList));
	new_item->declaration = decl;
	new_item->next = NULL;

	if(list == NULL)	return new_item;
	
	for(pos=list;pos->next!=NULL;pos = pos->next)
		;
	pos->next = new_item;

	return list;
}

Declaration *
minic_alloc_declaration(TypeSpecifier *type, char *identifier)
{
	Declaration *decl;

	decl = malloc(sizeof(Declaration));
	decl->name = identifier;
	decl->type = type;
	decl->variable_index = -1;

	return decl;
}
/*
ReferenceName *
minic_create_reference_name(char *identifier)
{
	ReferenceName *rn;

	rn = malloc(sizeof(ReferenceName));
	rn->name = identifier;
	rn->next = NULL;

	return pn;
}

ReferenceName *
minic_chain_reference_name(ReferenceName *list, char *identifier)
{
	ReferenceName *pos;

	for(pos = list;pos->next;pos=pos->next)
		;
	pos->next = minic_create_reference_name(identifier);
	return list;
}

ReferenceList *
minic_create_reference_list(ReferenceName *reference_name)
{
	ReferenceList *rl;
	MINIC_Compiler *compiler;
	char *current_reference_name;
	char *ref_reference_name;

	compiler = minic_get_current_compiler();
	current_reference_name = compiler->reference_name->name;
	ref_reference_name = reference_name->name;
	if(strcmp(current_reference_name,ref_reference_name)){
		printf("FROM MINIC_CREATE_REFERENCE_LIST\nLine[%d]: %s\n",
			compiler->current_line_number,
			"Require the file itself error.");
	}
	free(current_reference_name);
	free(ref_reference_name);

	rl = malloc(sizeof(ReferenceList));
	rl->reference_name = reference_name;
	rl->line_number = compiler->current_line_number;
	rl->next = NULL;

	return rl;
}

ReferenceList *
minic_chain_reference_list(ReferenceList *list, ReferenceList *add)
{
	ReferenceList *pos;
	char buf[LINE_BUF_SIZE];

 	for( pos =list; pos->next; pos =pos->next){
		if(!strcmp(pos->reference_name,add->reference_name)){
			char *reference_name;
			reference_name = add->reference_name;
			strcpy(buf,referene_name,LINE_BUF_SIZE);
			printf("error!\n");
		}
	}
	pos->next = add;

	return list;
}

void
minic_set_reference_list(ReferenceList *reference_list)
{
	MINIC_Compiler *compiler;
	//char *current_reference_name;

	compiler = minic_get_current_compiler();
	//current_reference_name = compiler->reference_name->name;
	//free(current_reference_name);
	compiler->reference_list = reference_list;
}

static void
add_function_to_compiler(FunctionDefinition *fd)
{
	MINIC_Compiler *compiler;
	FunctionDefinition *pos;

	compiler = minic_get_current_compiler();
	if(compiler->function_list){
		for(pos = compiler->function_list;pos->next;pos=pos->next)
			;
		pos->next = fd;
	}else{
		compiler->function_list = fd;
	}
}
*/
FunctionDefinition *
minic_create_function_definition(TypeSpecifier *type, char *identifier,
			   ParameterList *parameter_list, Block *block)
{
	FunctionDefinition *fd;
	MINIC_Compiler *compiler;

	compiler = minic_get_current_compiler();

	fd = malloc(sizeof(FunctionDefinition));
	fd->type = type;
	fd->name = identifier;
	fd->parameter = parameter_list;
	fd->block = block;
	fd->index = compiler->mvm_function_count;
	//compiler->function_count++;//add the count of functions
	fd->local_variable_count = 0;
	fd->local_variable = NULL;//initialize the variables of the function
	fd->end_line_number = compiler->current_line_number;
	fd->next = NULL;
	//if (block) {
        //	block->type = FUNCTION_BLOCK;
        //	block->parent.function.function = fd;
    	//}
    	//add_function_to_compiler(fd);

	return fd;
}
	
void
minic_function_define(TypeSpecifier *type, char *identifier,
		      ParameterList *parameter_list, Block *block)
{
	FunctionDefinition *fd;
	FunctionDefinition *pos;
	MINIC_Compiler *compiler;

	if(minic_search_function(identifier)
	   || minic_search_declaration(identifier,NULL)) {
	    	printf("[%d]: %s\n",minic_get_current_compiler()->current_line_number, "redefined name");
	    	return;
	}
	//get the function
	fd = minic_create_function_definition(type, identifier, parameter_list, block);
	//set the block
	if(block){
		block->type = FUNCTION_BLOCK;
		block->parent.function.function = fd;
	}

	//add the function to the tail of the function list
	compiler = minic_get_current_compiler();
	if(compiler->function_list) {
		for( pos = compiler->function_list; pos->next; pos = pos->next)
			;
		pos->next = fd;
	} else {
		compiler->function_list = fd;
	}
}

ParameterList *
minic_create_parameter(TypeSpecifier *type, char *identifier)
{
	ParameterList *p;

	p = malloc(sizeof(ParameterList));
	p->name = identifier;
	p->type = type;
	p->line_number = minic_get_current_compiler()->current_line_number;
	p->next = NULL;

	return p;
}

ParameterList *
minic_chain_parameter(ParameterList *list, TypeSpecifier *type, char *identifier)
{
	ParameterList *pos;
	ParameterList *pl;

	pl = minic_create_parameter(type, identifier);

	for(pos = list;pos->next;pos = pos->next)
		;
	pos->next = pl;

	return list;
}

ArgumentList *
minic_create_argument_list(Expression *expression)
{
	ArgumentList *al;

	al = malloc(sizeof(ArgumentList));
	al->expression = expression;
	al->next = NULL;

	return al;
}

ArgumentList *
minic_chain_argument_list(ArgumentList *list, Expression *expression)
{
	ArgumentList *pos;
	
	if(list == NULL)
		return minic_create_argument_list(expression);

	for(pos = list; pos->next;pos = pos->next)
		;
	pos->next = minic_create_argument_list(expression);

	return list;
}

ExpressionList *
minic_create_expression_list(Expression *expression)
{
    	ExpressionList *el;

	el = malloc(sizeof(ExpressionList));
    	el->expression = expression;
    	el->next = NULL;

    	return el;
}

ExpressionList *
minic_chain_expression_list(ExpressionList *list, Expression *expression)
{
    	ExpressionList *pos;
    
    	for(pos = list; pos->next;pos = pos->next)
        	;
    	pos->next = minic_create_expression_list(expression);

    	return list;
}

StatementList *
minic_create_statement_list(Statement *statement)
{
	StatementList *sl;

	sl = malloc(sizeof(StatementList));
	sl->statement = statement;
	sl->next = NULL;

	return sl;
}

StatementList *
minic_chain_statement_list(StatementList *list, Statement *statement)
{
	StatementList *pos;
	
	if(list == NULL)
		return minic_create_statement_list(statement);

	for(pos = list;pos->next;pos = pos->next)
		;
	pos->next = minic_create_statement_list(statement);

	return list;
}

TypeSpecifier *
minic_create_type_specifier(MVM_BasicType basic_type)
{
	TypeSpecifier *type;
	type = malloc(sizeof(TypeSpecifier));
	type->basic_type = basic_type;
	type->line_number = minic_get_current_compiler()->current_line_number;
	type->derive = NULL;

	return type;
}

TypeSpecifier *
minic_create_class_type_specifier(char *identifier)
{
	TypeSpecifier *type;

	type = minic_alloc_type_specifier(MVM_CLASS_TYPE);
	type->class_ref.identifier = identifier;
	type->class_ref.class_definition = NULL;
	type->line_number = minic_get_current_compiler()->current_line_number;

	return type;
}

TypeSpecifier *
minic_create_array_type_specifier(TypeSpecifier *base)
{
	TypeDerive *new_derive;

	new_derive = malloc(sizeof(TypeDerive));
	new_derive->tag = ARRAY_DERIVE;
	new_derive->next = NULL;

	if(base->derive == NULL) {
		base->derive = new_derive;
	} else {
		TypeDerive *derive_p;
		for(derive_p = base->derive; derive_p->next != NULL;
		    derive_p = derive_p->next)
			;
		derive_p->next = new_derive;
	}

	return base;
}

Expression *
minic_alloc_expression(ExpressionKind kind)
{
	Expression *exp;

	exp = malloc(sizeof(Expression));
	exp->type = NULL;
	exp->kind = kind;
	exp->line_number = minic_get_current_compiler()->current_line_number;

	return exp;
}

Expression *
minic_create_comma_expression(Expression *left, Expression *right)
{
	Expression *exp;

	exp = minic_alloc_expression(COMMA_EXPRESSION);
	exp->u.comma.left = left;
	exp->u.comma.right = right;

	return exp;
}

Expression *
minic_create_assign_expression(Expression *left, AssignmentOperator operator, Expression *operand)
{
	Expression *exp;

	exp = minic_alloc_expression(ASSIGN_EXPRESSION);
	exp->u.assign_expression.left = left;
	exp->u.assign_expression.operator = operator;
	exp->u.assign_expression.operand = operand;

	return exp;
}

Expression *
minic_create_binary_expression(ExpressionKind operator, Expression *left, Expression *right)
{
	Expression *exp;
	exp = minic_alloc_expression(operator);
	exp->u.binary_expression.left = left;
	exp->u.binary_expression.right = right;
	return exp;
}

Expression *
minic_create_minus_expression(Expression *operand)
{
	Expression *exp;
	exp = minic_alloc_expression(MINUS_EXPRESSION);
	exp->u.minus_expression = operand;
	return exp;
}

Expression *
minic_create_logical_not_expression(Expression *operand)
{
	Expression *exp;
	exp = minic_alloc_expression(LOGICAL_NOT_EXPRESSION);
	exp->u.logical_not = operand;

	return exp;
}

Expression *
minic_create_index_expression(Expression *array, Expression *index)
{
	Expression *exp;
	exp = minic_alloc_expression(INDEX_EXPRESSION);
	exp->u.index_expression.array = array;
	exp->u.index_expression.index = index;

	return exp;
}

Expression *
minic_create_incdec_expression(Expression *operand, ExpressionKind inc_or_dec)
{
	Expression *exp;

	exp = minic_alloc_expression(inc_or_dec);
	exp->u.inc_dec.operand = operand;

	return exp;
}

Expression *
minic_create_identifier_expression(char *identifier)
{
	Expression *exp;

	exp = minic_alloc_expression(IDENTIFIER_EXPRESSION);
	exp->u.identifier.name = identifier;

	return exp;
}

Expression *
minic_create_function_call_expression(Expression *function, ArgumentList *argument)
{
	Expression *exp;

	exp = minic_alloc_expression(FUNCTION_CALL_EXPRESSION);
	exp->u.function_call_expression.function = function;
	exp->u.function_call_expression.argument = argument;

	return exp;
}

Expression *
minic_create_boolean_expression(MVM_Boolean value)
{
	Expression *exp;

	exp = minic_alloc_expression(BOOLEAN_EXPRESSION);
	exp->u.boolean_value = value;

	return exp;
}

Expression *
minic_create_member_expression(Expression *expression, char *member_name)
{
	Expression *exp;

	exp = minic_alloc_expression(MEMBER_EXPRESSION);
	exp->u.member_expression.expression = expression;
	exp->u.member_expression.member_name = member_name;

	return exp;
}

Expression *
minic_create_null_expression(void)
{
	Expression *exp;

	exp = minic_alloc_expression(NULL_EXPRESSION);

	return exp;
}

Expression *
minic_create_array_literal_expression(ExpressionList *list)
{
	Expression *exp;

	exp = minic_alloc_expression(ARRAY_LITERAL_EXPRESSION);
	exp->u.array_literal = list;

	return exp;
}

Expression *
minic_create_new_expression(char *class_name, char *method_name)
{
    Expression *exp;

    exp = minic_alloc_expression(NEW_EXPRESSION);
    exp->u.new_e.class_name = class_name;
    exp->u.new_e.class_definition = NULL;
    //exp->u.new_e.method_name = method_name;
    //exp->u.new_e.method_declaration = NULL;

    return exp;
}

Expression *
minic_create_basic_array_creation(MVM_BasicType basic_type,
				       ArrayDimension *dim_expr_list,
                                      ArrayDimension *dim_list)
{
	Expression  *exp;
	TypeSpecifier *type;
	type = minic_create_type_specifier(basic_type);
    	exp = minic_create_class_array_creation(type, dim_expr_list,dim_list);
    	/*exp->u.array_creation.type = minic_create_type_specifier(basic_type);
    	exp->u.array_creation.dimension
        	= minic_chain_array_dimension(dim_expr_list,dim_list);*/
    	return exp;
}

Expression *
minic_create_class_array_creation(TypeSpecifier *type,
                                ArrayDimension *dim_expr_list,
                                ArrayDimension *dim_list)
{
    Expression  *exp;

    exp = minic_alloc_expression(ARRAY_CREATION_EXPRESSION);
    exp->u.array_creation.type = type;
    exp->u.array_creation.dimension
        = minic_chain_array_dimension(dim_expr_list, dim_list);

    return exp;
}

ArrayDimension *
minic_create_array_dimension(Expression *expr)
{
    	ArrayDimension *dim;

    	dim = malloc(sizeof(ArrayDimension));
    	dim->expression = expr;
    	dim->next = NULL;

	return dim;
}

ArrayDimension *
minic_chain_array_dimension(ArrayDimension *list, ArrayDimension *dim)
{
    	ArrayDimension *pos;

    	for (pos = list; pos->next != NULL; pos = pos->next)
        	;
    	pos->next = dim;

    	return list;
}

Statement *
minic_alloc_statement(StatementType type)
{
	Statement *st;

	st = malloc(sizeof(Statement));
	st->type = type;
	st->line_number = minic_get_current_compiler()->current_line_number;

	return st;
}

Statement *
minic_create_if_statement(Expression *condition, Block *then_block, 
			  Elseif *elseif_list, Block *else_block)
{
	Statement *st;

	st = minic_alloc_statement(IF_STATEMENT);
	st->u.if_s.condition = condition;
	st->u.if_s.then_block = then_block;
	st->u.if_s.elseif_list = elseif_list;
	st->u.if_s.else_block = else_block;

	return st;
}

Elseif *
minic_chain_elseif_list(Elseif *list, Elseif *add)
{
	Elseif *pos;
	for(pos = list; pos->next;pos = pos->next)
		;
	pos->next = add;

	return pos;
}

Elseif *
minic_create_elseif(Expression *exp, Block *block)
{
	Elseif *ei;

	ei = malloc(sizeof(Elseif));
	ei->condition = exp;
	ei->block = block;
	ei->next = NULL;

	return ei;
}

Statement *
minic_create_while_statement(char *label, Expression *condition, Block *block)
{
	Statement *st;

	st = minic_alloc_statement(WHILE_STATEMENT);
	st->u.while_s.label = label;
	st->u.while_s.condition = condition;
	st->u.while_s.block = block;
	block->type = WHILE_STATEMENT_BLOCK;
	block->parent.statement.statement = st;

	return st;
}

Statement *
minic_create_for_statement(char *label, Expression *init, Expression *condition, 
			   Expression *post, Block *block)
{
	Statement *st;

	st = minic_alloc_statement(FOR_STATEMENT);
	st->u.for_s.label = label;
	st->u.for_s.init = init;
	st->u.for_s.condition = condition;
	st->u.for_s.post = post;
	st->u.for_s.block = block;
	block->type = FOR_STATEMENT_BLOCK;
	block->parent.statement.statement = st;

	return st;
}

Statement *
minic_create_do_while_statement(char *label, Block *block,
                              Expression *condition)
{
    Statement *st;

    st = minic_alloc_statement(DO_WHILE_STATEMENT);
    st->u.do_while_s.label = label;
    st->u.do_while_s.block = block;
    st->u.do_while_s.condition = condition;
    block->type = DO_WHILE_STATEMENT_BLOCK;
    block->parent.statement.statement = st;

    return st;
}

Statement *
minic_create_foreach_statement(char *label, char *variable, Expression *collection, Block *block)
{
	Statement *st;

	st = minic_alloc_statement(FOREACH_STATEMENT);
	st->u.foreach_s.label = label;
	st->u.foreach_s.variable = variable;
	st->u.foreach_s.collection = collection;
	st->u.foreach_s.block = block;

	return st;
}

Block *
minic_alloc_block(void)
{
	Block *new_block;

	new_block = malloc(sizeof(Block));
	new_block->type = UNDEFINED_BLOCK;
	new_block->outer_block = NULL;
	new_block->statement_list = NULL;
	new_block->declaration_list = NULL;

	return new_block;
}

//go into a new block
Block *
minic_open_block(void)
{
	Block *new_block;
	MINIC_Compiler *compiler = minic_get_current_compiler();
	new_block = minic_alloc_block();
	new_block->outer_block = compiler->current_block;
	compiler->current_block = new_block;

	return new_block;
}

Block *
minic_close_block(Block *block, StatementList *statement_list)
{
	MINIC_Compiler *compiler = minic_get_current_compiler();
	//DEBUG ASSERTION
	block->statement_list = statement_list;
	compiler->current_block = block->outer_block;

	return block;
}

Statement *
minic_create_expression_statement(Expression *expression)
{
	Statement *st;

	st = minic_alloc_statement(EXPRESSION_STATEMENT);
	st->u.expression_s = expression;

	return st;
}

Statement *
minic_create_return_statement(Expression *expression)
{
	Statement *st;

	st = minic_alloc_statement(RETURN_STATEMENT);
	st->u.return_s.return_value = expression;

	return st;
}

Statement *
minic_create_break_statement(char *label)
{
	Statement *st;

	st = minic_alloc_statement(BREAK_STATEMENT);
	st->u.break_s.label = label;

	return st;
}

Statement *
minic_create_continue_statement(char *label)
{
	Statement *st;

	st = minic_alloc_statement(CONTINUE_STATEMENT);
	st->u.continue_s.label = label;

	return st;
}

Statement *
minic_create_declaration_statement(TypeSpecifier *type, char *identifier, Expression *initializer)
{
	Statement *st;
	Declaration *decl;

	st = minic_alloc_statement(DECLARATION_STATEMENT);

	decl = minic_alloc_declaration(type,identifier);

	decl->initializer = initializer;

	st->u.declaration_s = decl;

	return st;
}

void
minic_start_class_definition(/*ClassOrMemberModifierList *modifier,*/
                           char *identifier
                           /*ExtendsList *extends*/)
{
    ClassDefinition *cd;
    MINIC_Compiler *compiler = minic_get_current_compiler();

    cd = malloc(sizeof(ClassDefinition));

    //cd->is_abstract = (class_or_interface == DVM_INTERFACE_DEFINITION);
    /*cd->access_modifier = DVM_FILE_ACCESS;
    if (modifier) {
        if (modifier->is_abstract == ABSTRACT_MODIFIER) {
            cd->is_abstract = DVM_TRUE;
        }
        cd->access_modifier = conv_access_modifier(modifier->access_modifier);
    }*/
    //cd->access_modifier = modifier->access_modifier;
    //cd->class_or_interface = class_or_interface;
    //cd->reference_name = compiler->reference_name;
    cd->name = identifier;
    //cd->extends = extends;
    cd->member = NULL;
    cd->next = NULL;
    cd->line_number = compiler->current_line_number;

//    DBG_assert(compiler->current_class_definition == NULL,
  //             ("current_class_definition is not NULL."));
    compiler->current_class_definition = cd;
}

void minic_class_define(MemberDeclaration *member_list)
{
    MINIC_Compiler *compiler;
    ClassDefinition *cd;
    ClassDefinition *pos;

    compiler = minic_get_current_compiler();
    cd = compiler->current_class_definition;
    //DBG_assert(cd != NULL, ("current_class_definition is NULL."));

    if (compiler->class_definition_list == NULL) {
        compiler->class_definition_list = cd;
    } else {
        for (pos = compiler->class_definition_list; pos->next;
             pos = pos->next)
            ;
        pos->next = cd;
    }
    cd->member = member_list;
    compiler->current_class_definition = NULL;
}
/*
ExtendsList *
minic_create_extends_list(char *identifier)
{
    ExtendsList *list;

    list = malloc(sizeof(ExtendsList));
    list->identifier = identifier;
    list->class_definition = NULL;
    list->next = NULL;

    return list;
}

ExtendsList *
minic_chain_extends_list(ExtendsList *list, char *add)
{
    ExtendsList *pos;

    for (pos = list; pos->next; pos = pos->next)
        ;
    pos->next = minic_create_extends_list(add);

    return list;
}

ClassOrMemberModifierList
minic_create_class_or_member_modifier(ModifierKind modifier)
{
    ClassOrMemberModifierList ret;

    ret.access_modifier = NOT_SPECIFIED_MODIFIER;

    switch (modifier) {
    case PUBLIC_MODIFIER:
        ret.access_modifier = PUBLIC_MODIFIER;
        break;
    case PRIVATE_MODIFIER:
        ret.access_modifier = PRIVATE_MODIFIER;
        break;
    default:
	break;
    }
    return ret;
}*/

MemberDeclaration *
minic_chain_member_declaration(MemberDeclaration *list, MemberDeclaration *add)
{
    MemberDeclaration *pos;

    for (pos = list; pos->next; pos = pos->next)
        ;
    pos->next = add;

    return list;
}
/*
static MemberDeclaration *
alloc_member_declaration(ClassOrMemberModifierList *modifier)
{
    MemberDeclaration *ret;

    ret = malloc(sizeof(MemberDeclaration));
    if (modifier) {
        ret->access_modifier = modifier->access_modifier;
    } else {
        ret->access_modifier = NOT_SPECIFIED;
    }
    ret->line_number = minic_get_current_compiler()->current_line_number;
    ret->next = NULL;

    return ret;
}*/

MemberDeclaration *
minic_create_field_member(/*ClassOrMemberModifierList *modifier,*/
                        TypeSpecifier *type, char *name)
{
    MemberDeclaration *ret;

    ret = malloc(sizeof(MemberDeclaration));//alloc_member_declaration(modifier);
    ret->name = name;
    ret->type = type;

    return ret;
}

