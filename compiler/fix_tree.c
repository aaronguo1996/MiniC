#include <math.h>
#include <string.h>
#include "minic.h"
#include "node.h"

/*
static ClassDefinition *
search_class_and_add(int line_number, char *name, int *class_index_p);
*/

static int
add_class(ClassDefinition *src)
{
    //int i;
    //DVM_Class *dest;
    //char *src_package_name;
    MINIC_Compiler *compiler = minic_get_current_compiler();
    //ExtendsList *sup_pos;
    int ret;
    ClassDefinition *pos;
    for(pos= compiler->class_definition_list;pos->next;pos=pos->next){
	if(!strcmp(pos->name,src->name) || minic_search_declaration(pos->name,compiler->current_block)){
	     printf("FROM ADD_CLASS\nLine[%d]: %s\n",
		    compiler->current_line_number,
		    "class redefined error.");
	}
    }
    ret = compiler->mvm_class_count;
    compiler->mvm_class_count++;
    /*for(sup_pos=src->extends;sup_pos;sup_pos=sup_pos->next){
	int dummy;
	search_class_and_add(src->line_number, sup_pos->identifier, &dummy);
    }*/

    return ret;
}

static void fix_type_specifier(TypeSpecifier *type);

static void
fix_parameter_list(ParameterList *parameter_list)
{
    ParameterList *param;

    for(param = parameter_list; param; param=param->next){
	fix_type_specifier(param->type);
    }
}

static void
fix_type_specifier(TypeSpecifier *type)
{
    ClassDefinition *cd;
    TypeDerive *derive_pos;
    //MINIC_Compiler *compiler = minic_get_current_compiler();

    for(derive_pos = type->derive; derive_pos;derive_pos = derive_pos->next)
	{
	    if (derive_pos->tag == FUNCTION_DERIVE) {
	        fix_parameter_list(derive_pos->u.function_d.parameter_list);
	    }
    }

    if (type->basic_type == MVM_CLASS_TYPE && type->class_ref.class_definition == NULL) {
	    cd = minic_search_class(type->class_ref.identifier);
	    if (cd) {
	        type->class_ref.class_definition = cd;
	        type->class_ref.class_index = add_class(cd);
	        return;
	    }
	    printf("FROM FIX_TYPE_SPECIFIER\nLine[%d]: %s %s\n",
		    type->line_number,
		    "cannot find type name",type->class_ref.identifier);
    }
}
/*
static TypeSpecifier *
create_function_derive_type(FunctionDefinition *fd)
{
    TypeSpecifier *ret;
    ret = minic_alloc_type_specifier(fd->type->basic_type);
    *ret = *fd->type;
    ret->derive = minic_alloc_type_derive(FUNCTION_DERIVE);
    //ret->derive->u.function_d.parameter = fd->parameter_list;
    ret->derive->next = fd->type->derive;

    return ret;
}
*/

static Expression *
fix_identifier_expression(Block *current_block, Expression *expr,
			  Expression *parent)
{
    Declaration *decl;
    FunctionDefinition *fd;

    decl = minic_search_declaration(expr->u.identifier.name, current_block);
    if(decl) {
	expr->type = decl->type;
	expr->u.identifier.kind = VARIABLE_IDENTIFIER;
	expr->u.identifier.u.declaration = decl;
	return expr;
    }
    fd = minic_search_function(expr->u.identifier.name);
    if (fd == NULL) {
	printf("FROM FIX_IDENFITIER_EXPRESSION\nLine [%d]: %s %s\n",
		expr->line_number,
		"cannot find identifier",
		expr->u.identifier.name);
	exit(-1);
    }
    expr->type = fd->type;
    expr->u.identifier.kind = FUNCTION_IDENTIFIER;
 //   expr->u.identifier.u.function->function_definition = fd;
 //   expr->u.identifier.u.function->function_index = compiler->function_count-1;
//reserve_function_index(compiler,fd);
    fix_type_specifier(expr->type);

    return expr;
}

static Expression *fix_expression(Block *current_block, Expression *expr,
				  Expression *parent);

static Expression *
fix_comma_expression(Block *current_block, Expression  *expr)
{
    expr->u.comma.left
	= fix_expression(current_block, expr->u.comma.left,expr);
    expr->u.comma.right
	= fix_expression(current_block, expr->u.comma.right,expr);
    expr->type = expr->u.comma.right->type;

    return expr;
}

static Expression *
fix_assign_expression(Block *current_block, Expression *expr)
{
    Expression *operand;

    if (expr->u.assign_expression.left->kind != IDENTIFIER_EXPRESSION
        && expr->u.assign_expression.left->kind != INDEX_EXPRESSION
	&& expr->u.assign_expression.left->kind != MEMBER_EXPRESSION) {
	printf("FROM FIX_ASSIGN_EXPRESSION\nLine[%d]: %s\n",
		expr->u.assign_expression.left->line_number,
		"assign to a non-left-operand");
	exit(-1);
    }
    expr->u.assign_expression.left
	= fix_expression(current_block, expr->u.assign_expression.left,expr);
    operand = fix_expression(current_block, expr->u.assign_expression.operand,expr);
    if(operand->type->basic_type != 
       expr->u.assign_expression.left->type->basic_type)
    {
        printf("FROM FIX_ASSIGN_EXPRESSION\nLine[%d]: %s\n",
		expr->u.assign_expression.left->line_number,
		"wrong basic type in assignment");
	exit(-1);
    }

    expr->type = expr->u.assign_expression.left->type;

    return expr;
}

static Expression *
eval_math_expression_int(Expression *expr, int left, int right)
{
    if(expr->kind == ADD_EXPRESSION){
	expr->u.integer_value = left + right;
    }else if(expr->kind == SUB_EXPRESSION){
	expr->u.integer_value = left - right;
    }else if(expr->kind == MUL_EXPRESSION){
	expr->u.integer_value = left * right;
    }else if(expr->kind == DIV_EXPRESSION){
	if(right == 0){
	    printf("FROM EVAL_MATH_EXPRESSION\nLine[%d]: %s\n",
		    expr->line_number,
		    "divided by zero error.");
	    exit(-1);
	}
	expr->u.integer_value = left / right;
    }else if(expr->kind == MOD_EXPRESSION){
	expr->u.integer_value = left % right;
    }else{
	printf("FROM EVAL_MATH_EXPRESSION_INT\nLine[%d]: %s\n",
		expr->line_number,
		"unknown expression kind");
	exit(-1);
    }
    expr->kind = INTEGER_EXPRESSION;
    expr->type = minic_alloc_type_specifier(MVM_INTEGER_TYPE);

    return expr;
}

static Expression *
eval_math_expression_decimal(Expression *expr, float left, float right)
{
    if(expr->kind == ADD_EXPRESSION){
	expr->u.decimal_value = left + right;
    }else if(expr->kind == SUB_EXPRESSION){
	expr->u.decimal_value = left - right;
    }else if(expr->kind == MUL_EXPRESSION){
	expr->u.decimal_value = left * right;
    }else if(expr->kind == DIV_EXPRESSION){
	expr->u.decimal_value = left / right;
    }else if(expr->kind == MOD_EXPRESSION){
	printf("FROM EVAL_MATH_EXPRESSION_DECIMAL\nLine[%d]: %s\n",
		expr->line_number,
		"MOD cannot be calculated on decimal numbers.");
	exit(-1);
    }else{
	printf("FROM EVAL_MATH_EXPRESSION_DECIMAL\nLine[%d]: %s\n",
		expr->line_number,
		"unknown exression kind.");
	exit(-1);
    }
    expr->kind = DECIMAL_EXPRESSION;
    expr->type = minic_alloc_type_specifier(MVM_DECIMAL_TYPE);

    return expr;
}

static Expression *
chain_string(Expression *expr)
{
    char *left_str = expr->u.binary_expression.left->u.string_value;
    char *right_str;
    int len;
    char *new_str;

    right_str = minic_expression_to_string(expr->u.binary_expression.right);
    if(!right_str)	return expr;

    len = strlen(left_str) + strlen(right_str);
    new_str = malloc(len+1);
    strcpy(new_str,left_str);
    strcat(new_str,right_str);
    free(left_str);
    free(right_str);
    expr->kind = STRING_EXPRESSION;
    expr->type = minic_alloc_type_specifier(MVM_STRING_TYPE);
    expr->u.string_value = new_str;

    return expr;
}

static Expression *
eval_math_expression(Block *current_block, Expression *expr)
{
    printf("left:%d\nright:%d\n",expr->u.binary_expression.left->kind,expr->u.binary_expression.right->kind);
    if(expr->u.binary_expression.left->kind == INTEGER_EXPRESSION
	&& expr->u.binary_expression.right->kind == INTEGER_EXPRESSION){
	expr = eval_math_expression_int(expr,
					expr->u.binary_expression.left
					->u.integer_value,
					expr->u.binary_expression.right
					->u.integer_value);
    }else if(expr->u.binary_expression.left->kind == DECIMAL_EXPRESSION
	     && expr->u.binary_expression.right->kind == DECIMAL_EXPRESSION){
	expr = eval_math_expression_decimal(expr,
					    expr->u.binary_expression.left
					    ->u.decimal_value,
					    expr->u.binary_expression.right
					    ->u.decimal_value);
    }else if(expr->u.binary_expression.left->kind == STRING_EXPRESSION
	     && expr->kind == ADD_EXPRESSION){
	expr = chain_string(expr);
    }

    return expr;
}

static Expression *
fix_math_binary_expression(Block *current_block, Expression *expr)
{
    expr->u.binary_expression.left
	= fix_expression(current_block, expr->u.binary_expression.left,expr);
    expr->u.binary_expression.right
	= fix_expression(current_block, expr->u.binary_expression.right,expr);

    expr = eval_math_expression(current_block, expr);
    if(expr->kind == INTEGER_EXPRESSION || expr->kind == DECIMAL_EXPRESSION
	|| expr->kind == STRING_EXPRESSION){
	return expr;
    }

    if(minic_is_integer(expr->u.binary_expression.left->type)
	&& minic_is_integer(expr->u.binary_expression.right->type)){
	expr->type = minic_alloc_type_specifier(MVM_INTEGER_TYPE);
    }else if(minic_is_decimal(expr->u.binary_expression.left->type)
	     && minic_is_decimal(expr->u.binary_expression.right->type)){
	expr->type = minic_alloc_type_specifier(MVM_DECIMAL_TYPE);
    }else if(minic_is_string(expr->u.binary_expression.left->type)
	     && minic_is_string(expr->u.binary_expression.right->type)){
	expr->type = minic_alloc_type_specifier(MVM_STRING_TYPE);
    } else if (expr->kind == ADD_EXPRESSION
               && ((minic_is_string(expr->u.binary_expression.left->type)
                    && minic_is_string(expr->u.binary_expression.right->type))
                   || (minic_is_string(expr->u.binary_expression.left->type)
                       && expr->u.binary_expression.right->kind
                       == NULL_EXPRESSION))) {
        expr->type =  minic_alloc_type_specifier(MVM_STRING_TYPE);
    } else{
	printf("FROM FIX_MATH_BINARY_EXPRESSION\nLine[%d]: %s\n",
		expr->line_number,
		"math type mismatch.");
	exit(-1);
    }

    return expr;
}

static Expression *
eval_compare_expression_boolean(Expression *expr, 
				MVM_Boolean left, MVM_Boolean right)
{
    if(expr->kind == EQ_EXPRESSION){
	expr->u.boolean_value = (left == right);
    }else if(expr->kind == NE_EXPRESSION){
	expr->u.boolean_value = (left != right);
    }else{
	printf("FROM EVAL_COMPARE_EXPRESSION_BOOLEAN\nLine[%d]: %s\n",
		expr->line_number,
		"unknown expression kind.");
	exit(-1);
    }

    expr->kind = BOOLEAN_EXPRESSION;
    expr->type = minic_alloc_type_specifier(MVM_BOOLEAN_TYPE);

    return expr;
}

static Expression *
eval_compare_expression_int(Expression *expr, int left, int right)
{
    if(expr->kind == EQ_EXPRESSION){
	expr->u.boolean_value = (left == right);
    }else if(expr->kind == NE_EXPRESSION){
	expr->u.boolean_value = (left != right);
    }else if(expr->kind == GT_EXPRESSION){
	expr->u.boolean_value = (left > right);
    }else if(expr->kind == GE_EXPRESSION){
	expr->u.boolean_value = (left >= right);
    }else if(expr->kind == LT_EXPRESSION){
	expr->u.boolean_value = (left < right);
    }else if(expr->kind == LE_EXPRESSION){
	expr->u.boolean_value = (left <= right);
    }else{
	printf("FROM EVAL_COMPARE_EXPRESSION_INT\nLine[%d]: %s\n",
		expr->line_number,
		"unknown compare expression.");
	exit(-1);
    }

    expr->type = minic_alloc_type_specifier(MVM_BOOLEAN_TYPE);
    expr->kind = BOOLEAN_EXPRESSION;

    return expr;
}

static Expression *
eval_compare_expression_decimal(Expression *expr, float left, float right)
{
    if(expr->kind == EQ_EXPRESSION){
        expr->u.boolean_value = (left == right);
    }else if(expr->kind == NE_EXPRESSION){
        expr->u.boolean_value = (left != right);
    }else if(expr->kind == GT_EXPRESSION){
        expr->u.boolean_value = (left > right);
    }else if(expr->kind == GE_EXPRESSION){
        expr->u.boolean_value = (left >= right);
    }else if(expr->kind == LT_EXPRESSION){
        expr->u.boolean_value = (left < right);
    }else if(expr->kind == LE_EXPRESSION){
        expr->u.boolean_value = (left <= right);
    }else{
        printf("FROM EVAL_COMPARE_EXPRESSION_DECIMAL\nLine[%d]: %s\n",
                expr->line_number,
                "unknown compare expression.");
	exit(-1);
    }

    expr->type = minic_alloc_type_specifier(MVM_BOOLEAN_TYPE);
    expr->kind = BOOLEAN_EXPRESSION;

    return expr;
}

static Expression *
eval_compare_expression_string(Expression *expr, char *left, char *right)
{
    int cmp;
    cmp = strcmp(left,right);

    if(expr->kind == EQ_EXPRESSION){
        expr->u.boolean_value = (cmp == 0);
    }else if(expr->kind == NE_EXPRESSION){
        expr->u.boolean_value = (cmp != 0);
    }else if(expr->kind == GT_EXPRESSION){
        expr->u.boolean_value = (cmp > 0);
    }else if(expr->kind == GE_EXPRESSION){
        expr->u.boolean_value = (cmp >= 0);
    }else if(expr->kind == LT_EXPRESSION){
        expr->u.boolean_value = (cmp < 0);
    }else if(expr->kind == LE_EXPRESSION){
        expr->u.boolean_value = (cmp <= 0);
    }else{
        printf("FROM EVAL_COMPARE_EXPRESSION_STRING\nLine[%d]: %s\n",
                expr->line_number,
                "unknown compare expression.");
	exit(-1);
    }

    expr->type = minic_alloc_type_specifier(MVM_BOOLEAN_TYPE);
    expr->kind = BOOLEAN_EXPRESSION;

    return expr;
}

static Expression *
eval_compare_expression(Expression *expr)
{
    if (expr->u.binary_expression.left->kind == BOOLEAN_EXPRESSION
        && expr->u.binary_expression.right->kind == BOOLEAN_EXPRESSION) {
        expr = eval_compare_expression_boolean(expr,
                                               expr->u.binary_expression.left
                                               ->u.boolean_value,
                                               expr->u.binary_expression.right
                                               ->u.boolean_value);

    } else if (expr->u.binary_expression.left->kind == INTEGER_EXPRESSION
        && expr->u.binary_expression.right->kind == INTEGER_EXPRESSION) {
        expr = eval_compare_expression_int(expr,
                                           expr->u.binary_expression.left
                                           ->u.integer_value,
                                           expr->u.binary_expression.right
                                           ->u.integer_value);

    } else if (expr->u.binary_expression.left->kind == DECIMAL_EXPRESSION
               && expr->u.binary_expression.right->kind == DECIMAL_EXPRESSION) {
        expr = eval_compare_expression_decimal(expr,
                                              expr->u.binary_expression.left
                                              ->u.decimal_value,
                                              expr->u.binary_expression.right
					      ->u.decimal_value);
    } else if (expr->u.binary_expression.left->kind == INTEGER_EXPRESSION
               && expr->u.binary_expression.right->kind == DECIMAL_EXPRESSION) {
        expr = eval_compare_expression_decimal(expr,
                                              expr->u.binary_expression.left
                                              ->u.integer_value,
                                              expr->u.binary_expression.right
                                              ->u.decimal_value);

    } else if (expr->u.binary_expression.left->kind == DECIMAL_EXPRESSION
               && expr->u.binary_expression.right->kind == INTEGER_EXPRESSION) {
        expr = eval_compare_expression_decimal(expr,
                                              expr->u.binary_expression.left
                                              ->u.decimal_value,
                                              expr->u.binary_expression.right
                                              ->u.integer_value);

    } else if (expr->u.binary_expression.left->kind == STRING_EXPRESSION
               && expr->u.binary_expression.right->kind == STRING_EXPRESSION) {
        expr = eval_compare_expression_string(expr,
                                              expr->u.binary_expression.left
                                              ->u.string_value,
                                              expr->u.binary_expression.right
					      ->u.string_value);
    } else if (expr->u.binary_expression.left->kind == NULL_EXPRESSION
               && expr->u.binary_expression.right->kind == NULL_EXPRESSION) {
        expr->kind = BOOLEAN_EXPRESSION;
        expr->type = minic_alloc_type_specifier(MVM_BOOLEAN_TYPE);
        expr->u.boolean_value = MVM_TRUE;
    }

    return expr;
}

static Expression *
fix_compare_expression(Block *current_block, Expression *expr)
{
    expr->u.binary_expression.left
	= fix_expression(current_block, expr->u.binary_expression.left, expr);
    expr->u.binary_expression.right
	= fix_expression(current_block, expr->u.binary_expression.right, expr);
    expr = eval_compare_expression(expr);
    if(expr->kind == BOOLEAN_EXPRESSION){
	return expr;
    }

    if (expr->u.binary_expression.left->type->basic_type !=
        expr->u.binary_expression.right->type->basic_type) {
        printf("FROM FIX_COMPARE_EXPRESSION\nLine[%d]: %s\n",
		expr->line_number,
		"wrong compare expression.");
	exit(-1);
    }
    expr->type = minic_alloc_type_specifier(MVM_BOOLEAN_TYPE);

    return expr;
}

static Expression *
fix_logical_and_or_expression(Block *current_block, Expression *expr)
{
    expr->u.binary_expression.left
	= fix_expression(current_block, expr->u.binary_expression.left, expr);
    expr->u.binary_expression.right
	= fix_expression(current_block, expr->u.binary_expression.right, expr);

    if(minic_is_boolean(expr->u.binary_expression.left->type)
	&& minic_is_boolean(expr->u.binary_expression.right->type)){
	expr->type = minic_alloc_type_specifier(MVM_BOOLEAN_TYPE);
    }else{
	printf("FROM FIX_LOGICAL_AND_OR_EXPRESSION\nLine[%d]: %s\n",
		expr->line_number,
		"logical type mismatch error.");
	exit(-1);
    }

    return expr;
}

static Expression *
fix_minus_expression(Block *current_block, Expression *expr)
{
    expr->u.minus_expression
	= fix_expression(current_block, expr->u.minus_expression, expr);

    if(!minic_is_integer(expr->u.minus_expression->type)
	&& !minic_is_decimal(expr->u.minus_expression->type)){
	printf("FROM FIX_MINUS_EXPRESSION\nLine[%d]: %s\n",
		expr->line_number,
		"minus type mismatch error.");
	exit(-1);
    }
    expr->type = expr->u.minus_expression->type;

    if (expr->u.minus_expression->kind == INTEGER_EXPRESSION) {
        expr->kind = INTEGER_EXPRESSION;
        expr->u.integer_value = -expr->u.minus_expression->u.integer_value;

    } else if (expr->u.minus_expression->kind == DECIMAL_EXPRESSION) {
        expr->kind = DECIMAL_EXPRESSION;
        expr->u.decimal_value = -expr->u.minus_expression->u.decimal_value;
    }


    return expr;
}

static Expression *
fix_logical_not_expression(Block *current_block, Expression *expr)
{
    expr->u.logical_not
        = fix_expression(current_block, expr->u.logical_not, expr);

    if (expr->u.logical_not->kind == BOOLEAN_EXPRESSION) {
        expr->kind = BOOLEAN_EXPRESSION;
        expr->u.boolean_value = !expr->u.logical_not->u.boolean_value;
        return expr;
    }

    if (!minic_is_boolean(expr->u.logical_not->type)) {
	printf("FROM FIX_LOGICAL_NOT_EXPRESSION\nLine[%d]: %s\n",
		expr->line_number,
                "logical not type mismatch error.");
	exit(-1);
    }
    expr->type = expr->u.logical_not->type;

    return expr;
}

static void
check_argument(Block *current_block, FunctionDefinition *fd, Expression *expr)
{
    ParameterList *param;
    ArgumentList *arg;

    for (param = fd->parameter,
             arg = expr->u.function_call_expression.argument;
         param && arg;
         param = param->next, arg = arg->next) {
        arg->expression
            = fix_expression(current_block, arg->expression, expr);
        if(param->type->basic_type != arg->expression->type->basic_type){
	    printf("FROM CHECK_ARGUMENT\nLine[%d]: %s\n",
		    expr->line_number,
		    "type of parameters and arguments mismatch error.");
	    exit(-1);
	}
    }

    if (param || arg) {
	printf("FROM CHECK_ARGUMENT\nLine[%d]: %s\n",
		expr->line_number,
		"count of parameters and arguments mismatch error.");
	exit(-1);
    }
}
/*
static ClassDefinition *
search_class_and_add(int line_number, char *name, int *class_index_p)
{
    ClassDefinition *cd;

    cd = minic_search_class(name);
    if(cd == NULL){
	printf("FROM SEARCH_CLASS_AND_ADD\nLine[%d]: %s %s",
	        line_number,
		"cannot find class", name);
    }
    *class_index_p = add_class(cd);

    return cd;
}
*/
static Expression *
fix_function_call_expression(Block *current_block, Expression *expr)
{
    printf("this is function\n");
    Expression *func_expr;
    FunctionDefinition *fd;

    func_expr = fix_expression(current_block,
                               expr->u.function_call_expression.function,
                               expr);

    if (func_expr->kind != IDENTIFIER_EXPRESSION) {
	printf("FROM FIX_FUNCTION_CALL\nLine[%d]: %s\n",
		expr->line_number,
		"function not identifier error.");
	exit(-1);
    }

    fd = minic_search_function(func_expr->u.identifier.name);
    if (fd == NULL) {
 	printf("FROM FIX_FUNCTION_CALL\nLine[%d]: %s %s\n",
		expr->line_number,
		"function not found error.",
		func_expr->u.identifier.name);
	exit(-1);
     }
    check_argument(current_block, fd, expr);

    expr->type = minic_alloc_type_specifier(fd->type->basic_type);
    expr->type->derive = fd->type->derive;

    return expr;
}

static Expression *
fix_array_literal_expression(Block *current_block, Expression *expr)
{
    ExpressionList *literal = expr->u.array_literal;
    TypeSpecifier *elem_type;
    ExpressionList *epos;

    if(literal == NULL){
	printf("FROM_FIX_ARRAY_LITERAL_EXPRESSION\nLine[%d]: %s\n",
		expr->line_number,
		"array expression cannot be null.");
    }
    literal->expression = fix_expression(current_block,literal->expression, expr);
    elem_type = literal->expression->type;
    for (epos = literal->next; epos; epos = epos->next) {
        epos->expression
            = fix_expression(current_block, epos->expression, expr);
	epos->expression->type = elem_type;
    }

    expr->type = minic_alloc_type_specifier(elem_type->basic_type);
    expr->type->derive = minic_alloc_type_derive(ARRAY_DERIVE);
    expr->type->derive->next = elem_type->derive;

    return expr;
}
/*
static void
check_member_accessibility(int line_number, ClassDefinition *target_class,
			   MemberDeclaration *member, char *member_name)
{
    MINIC_Compiler *compiler = minic_get_current_compiler();
    if(compiler->current_class_definition == NULL
	|| compiler->current_class_definition != target_class){
	if(member->access_modifier == PRIVATE_MODIfIER){
	    printf("FROM CHEKC_MEMBER_ACCESSIBILITY\nLine[%d]: %s %s",
		    line_number, "cannot access the private member", member_name);
	}
    }
}*/

static Expression *
fix_index_expression(Block *current_block, Expression *expr)
{
    IndexExpression *ie = &expr->u.index_expression;

    ie->array = fix_expression(current_block, ie->array, expr);
    ie->index = fix_expression(current_block, ie->index, expr);

    if(ie->array->type->derive == NULL
	|| ie->array->type->derive->tag != ARRAY_DERIVE){
	printf("FROM FIX_INDEX_EXPRESSION\nLine[%d]: %s\n",
		expr->line_number,
		"index left operand is not array.");
	exit(-1);
    }
    if(!minic_is_integer(ie->index->type)){
	printf("FROM FIX_INDEX_EXPRESSION\nLine[%d]: %s\n",
		expr->line_number,
		"index is not integer.");
	exit(-1);
    }
    expr->type = minic_alloc_type_specifier(ie->array->type->basic_type);
    expr->type->derive = ie->array->type->derive->next;

    return expr;
}

static Expression *
fix_inc_dec_expression(Block *current_block, Expression *expr)
{
    expr->u.inc_dec.operand
        = fix_expression(current_block, expr->u.inc_dec.operand, expr);

    if (!minic_is_integer(expr->u.inc_dec.operand->type)) {
	printf("FROM FIX_INC_DEC_EXPRESSION\nLine[%d]: %s\n",
		expr->line_number,
		"increment or decrement type mismatch error.");
	exit(-1);
    }
    expr->type = expr->u.inc_dec.operand->type;

    return expr;
}

static Expression *
fix_array_creation_expression(Block *current_block, Expression *expr)
{
    ArrayDimension *dim_pos;
    TypeDerive *derive = NULL;
    TypeDerive *tmp_derive;

    for(dim_pos = expr->u.array_creation.dimension; dim_pos; dim_pos = dim_pos->next){
	if(dim_pos->expression){
	    dim_pos->expression = fix_expression(current_block, 
						 dim_pos->expression,
						 expr);
	    if(!minic_is_integer(dim_pos->expression->type)){
		printf("FROM FIX_ARRAY_CREATION_EXPRESSION\nLine [%d]: %s\n",
			expr->line_number,
			"array size is not interger.");
		exit(-1);
	    }
	}
	tmp_derive = minic_alloc_type_derive(ARRAY_DERIVE);
	tmp_derive->next = derive;
	derive = tmp_derive;
    }
    expr->type = minic_alloc_type_specifier(expr->u.array_creation.type->basic_type);
    expr->type->derive = derive;

    return expr;
}

static Expression *
fix_member_expression(Block *current_block, Expression *expr)
{
    ClassDefinition *cd;
    
    Expression *exp = fix_expression(current_block,expr->u.member_expression.expression,expr);
    cd = minic_search_class(expr->u.member_expression.expression->type->class_ref.identifier);
    if(cd == NULL){
	printf("FROM FIX_MEMBER_EXPRESSION\nLine[%d]: %s %s\n",
		expr->line_number, "cannot find class",exp->type->class_ref.identifier );
	exit(-1);
    }

    MemberDeclaration *member = minic_search_member(cd, expr->u.member_expression.member_name);
    if(member == NULL){
	 printf("FROM FIX_MEMBER_EXPRESSION\nLine[%d]: %s %s in class %s\n",
		expr->line_number, "cannot find member",
		expr->u.member_expression.member_name,
		exp->type->class_ref.identifier);
	exit(-1);
    }
    expr->type = member->type;
    return expr;
}

static Expression *
fix_expression(Block *current_block, Expression *expr, 
	       Expression *parent)
{
    if (expr == NULL)
        return NULL;

    switch (expr->kind) {
    case BOOLEAN_EXPRESSION:
        expr->type = minic_alloc_type_specifier(MVM_BOOLEAN_TYPE);
        break;
    case INTEGER_EXPRESSION:
        expr->type = minic_alloc_type_specifier(MVM_INTEGER_TYPE);
        break;
    case DECIMAL_EXPRESSION:
        expr->type = minic_alloc_type_specifier(MVM_DECIMAL_TYPE);
        break;
    case STRING_EXPRESSION:
        expr->type = minic_alloc_type_specifier(MVM_STRING_TYPE);
        break;
    case IDENTIFIER_EXPRESSION:
        expr = fix_identifier_expression(current_block, expr, parent);
        break;
    case COMMA_EXPRESSION:
        expr = fix_comma_expression(current_block, expr);
        break;
    case ASSIGN_EXPRESSION:
        expr = fix_assign_expression(current_block, expr);
        break;
    case ADD_EXPRESSION:        /* FALLTHRU */
    case SUB_EXPRESSION:        /* FALLTHRU */
    case MUL_EXPRESSION:        /* FALLTHRU */
    case DIV_EXPRESSION:        /* FALLTHRU */
    case MOD_EXPRESSION:        /* FALLTHRU */
        expr = fix_math_binary_expression(current_block, expr);
        break;
    case EQ_EXPRESSION: /* FALLTHRU */
    case NE_EXPRESSION: /* FALLTHRU */
    case GT_EXPRESSION: /* FALLTHRU */
    case GE_EXPRESSION: /* FALLTHRU */
    case LT_EXPRESSION: /* FALLTHRU */
    case LE_EXPRESSION: /* FALLTHRU */
        expr = fix_compare_expression(current_block, expr);
        break;
    case LOGICAL_AND_EXPRESSION:        /* FALLTHRU */
    case LOGICAL_OR_EXPRESSION:         /* FALLTHRU */
        expr = fix_logical_and_or_expression(current_block, expr);
        break;
    case MINUS_EXPRESSION:
        expr = fix_minus_expression(current_block, expr);
        break;
    case LOGICAL_NOT_EXPRESSION:
        expr = fix_logical_not_expression(current_block, expr);
        break;
    case FUNCTION_CALL_EXPRESSION:
        expr = fix_function_call_expression(current_block, expr);
        break;
    case ARRAY_LITERAL_EXPRESSION:
        expr = fix_array_literal_expression(current_block, expr);
        break;
    case MEMBER_EXPRESSION:
	    expr = fix_member_expression(current_block, expr);
	    break;
    case NULL_EXPRESSION:
	expr->type = minic_alloc_type_specifier(MVM_NULL_TYPE);
	break;
    case INDEX_EXPRESSION:
	expr = fix_index_expression(current_block,expr);
	break;
    case INCREMENT_EXPRESSION:  /* FALLTHRU */
    case DECREMENT_EXPRESSION:
        expr = fix_inc_dec_expression(current_block, expr);
        break;
    /*case CAST_EXPRESSION:
        break;*/
    case ARRAY_CREATION_EXPRESSION:
        expr = fix_array_creation_expression(current_block, expr);
        break;
    case EXPRESSION_KIND_COUNT_PLUS_1:
        break;
    default:
	break;
        //DBG_assert(0, ("bad case. kind..%d\n", expr->kind));
    }

    return expr;
}

static void add_local_variable(FunctionDefinition *fd, Declaration *decl)
{
    fd->local_variable
        = realloc(fd->local_variable,
                  sizeof(Declaration) * (fd->local_variable_count+1));

    fd->local_variable[fd->local_variable_count] = decl;
    decl->variable_index = fd->local_variable_count;
    fd->local_variable_count++;
}

static void fix_statement_list(Block *current_block, StatementList *list,
                               FunctionDefinition *fd);

static void
fix_if_statement(Block *current_block, IfStatement *if_s,
                 FunctionDefinition *fd)
{
    Elseif *pos;

    fix_expression(current_block, if_s->condition, NULL);
    fix_statement_list(if_s->then_block, if_s->then_block->statement_list,
                       fd);
    for (pos = if_s->elseif_list; pos; pos = pos->next) {
        fix_expression(current_block, pos->condition, NULL);
        if (pos->block) {
            fix_statement_list(pos->block, pos->block->statement_list,
                               fd);
        }
    }
    if (if_s->else_block) {
        fix_statement_list(if_s->else_block, if_s->else_block->statement_list,
                           fd);
    }
}

static void
fix_return_statement(Block *current_block, ReturnStatement *return_s,
                     FunctionDefinition *fd)
{
    Expression *return_value;
    return_value
        = fix_expression(current_block, return_s->return_value, NULL);
    if (return_value == NULL) {
        if (fd->type->derive) {
            if (fd->type->derive->tag == ARRAY_DERIVE) {
                return_value = minic_alloc_expression(NULL_EXPRESSION);
            }
        } else {
            switch (fd->type->basic_type) {
            case MVM_BOOLEAN_TYPE:
                return_value = minic_alloc_expression(BOOLEAN_EXPRESSION);
                return_value->u.boolean_value = MVM_FALSE;
                break;
            case MVM_INTEGER_TYPE:
                return_value = minic_alloc_expression(INTEGER_EXPRESSION);
                return_value->u.integer_value = 0;
                break;
            case MVM_DECIMAL_TYPE:
                return_value = minic_alloc_expression(DECIMAL_EXPRESSION);
                return_value->u.decimal_value = 0.0;
                break;
            case MVM_STRING_TYPE:
                return_value = minic_alloc_expression(STRING_EXPRESSION);
                return_value->u.string_value = "";
                break;
            case MVM_NULL_TYPE: /* FALLTHRU */
                return_value = minic_alloc_expression(NULL_EXPRESSION);
                printf("oops4\n");
            default:
                break;
            }
        }
        return_s->return_value = return_value;
        return;
    }
    if(return_s->return_value->type->basic_type != fd->type->basic_type){
    	printf("FROM FIX_RETURN_STATEMENT\nLine[%d]: %s\n",
    		return_s->return_value->line_number,
    		"wrong return value type.");
    	exit(-1);
    }
}

static void
add_declaration(Block *current_block, Declaration *decl,
                FunctionDefinition *fd, int line_number)
{
    if (minic_search_declaration(decl->name, current_block) || minic_search_class(decl->name)) {
    	printf("FROM ADD_DECLARATION\nLine[%d]: %s %s\n",
    		line_number,
    		"variable multiple define error:",
    		decl->name);        
    	exit(-1);
    }

    if (current_block) {
        current_block->declaration_list
            = minic_chain_declaration(current_block->declaration_list, decl);
        add_local_variable(fd, decl);
        decl->is_local = MVM_TRUE;
    } else {
        MINIC_Compiler *compiler = minic_get_current_compiler();
        compiler->declaration_list
            = minic_chain_declaration(compiler->declaration_list, decl);
        decl->is_local = MVM_FALSE;
    }
}

static Expression *
create_assign_cast(Expression *src, TypeSpecifier *dst)
{
    if (src->type->basic_type == dst->basic_type) 
		return src;
    else{
	    printf("FROM CREATE_ASSIGN_CAST\nLine[%d]: %s\n",
		src->line_number,
		"wrong expression type.");
    }
	return NULL;
}

static void
fix_statement(Block *current_block, Statement *statement,
              FunctionDefinition *fd)
{
    printf("%d\n",statement->type);
    switch (statement->type) {
    case EXPRESSION_STATEMENT:
        fix_expression(current_block, statement->u.expression_s, NULL);
        break;
    case IF_STATEMENT:
        fix_if_statement(current_block, &statement->u.if_s, fd);
        break;
    case WHILE_STATEMENT: //statement->while_statement
	fix_expression(current_block, statement->u.while_s.condition, 
		       NULL);
        fix_statement_list(statement->u.while_s.block,
                           statement->u.while_s.block->statement_list, 
			   fd);
	break;
    case FOR_STATEMENT: //statement->for_statement
	fix_expression(current_block, statement->u.for_s.init,
		       	NULL);
        fix_expression(current_block, statement->u.for_s.condition, 
			NULL);
        fix_expression(current_block, statement->u.for_s.post, 
			NULL);
        fix_statement_list(statement->u.for_s.block,
                           statement->u.for_s.block->statement_list, 
			   fd);
        break;
    case DO_WHILE_STATEMENT:
	fix_expression(current_block, statement->u.do_while_s.condition,
			NULL);
	fix_statement_list(statement->u.do_while_s.block,
			   statement->u.do_while_s.block->statement_list,
			   fd);
	break;
    case FOREACH_STATEMENT://statement->foreach_statement
        fix_expression(current_block, statement->u.foreach_s.collection, 
			NULL);
        fix_statement_list(statement->u.foreach_s.block,
                           statement->u.foreach_s.block->statement_list, 
			   fd);
        break;
    case RETURN_STATEMENT:
    printf("Oops\n");
        fix_return_statement(current_block,
                             &statement->u.return_s, fd);
        break;
    case BREAK_STATEMENT:
        break;
    case CONTINUE_STATEMENT:
        break;
    case DECLARATION_STATEMENT:
	add_declaration(current_block, statement->u.declaration_s, fd,
                        statement->line_number);
	fix_expression(current_block, statement->u.declaration_s->initializer,
                       NULL);
        if (statement->u.declaration_s->initializer) {
            statement->u.declaration_s->initializer
                = create_assign_cast(statement->u.declaration_s->initializer,
                                     statement->u.declaration_s->type);
        }
        break;
    case STATEMENT_TYPE_COUNT_PLUS_1: /* FALLTHRU */
    default:
    	break;
    }
}

static void
fix_statement_list(Block *current_block, StatementList *list,
                   FunctionDefinition *fd)
{
    StatementList *pos;
    for (pos = list; pos; pos = pos->next) {
        fix_statement(current_block, pos->statement,
                      fd);
    }
}

static void
add_parameter_as_declaration(FunctionDefinition *fd)
{
    Declaration *decl;
    ParameterList *param;

    for (param = fd->parameter; param; param = param->next) {
        if (minic_search_declaration(param->name, fd->block)) {
            printf("FROM ADD_PARAMETER_AS_DECLARATION\nLine[%d]: %s",
		   param->line_number,
		   "parameter multiple define error");
	    exit(-1);
	}
	decl = minic_alloc_declaration(param->type, param->name);
	add_declaration(fd->block, decl, fd, param->line_number);
    }
}

static void
add_return_function(FunctionDefinition *fd)
{
    StatementList *last;
    StatementList **last_p;
    Statement *ret;

    if (fd->block->statement_list == NULL) {
        last_p = &fd->block->statement_list;
    } else {
        for (last = fd->block->statement_list; last->next; last = last->next)
            ;
        if (last->statement->type == RETURN_STATEMENT) {
            return;
        }
        last_p = &last->next;
    }

    ret = minic_create_return_statement(NULL);
    ret->line_number = fd->end_line_number;
    if (ret->u.return_s.return_value) {
        ret->u.return_s.return_value->line_number = fd->end_line_number;
    }
    fix_return_statement(fd->block, &ret->u.return_s, fd);
    *last_p = minic_create_statement_list(ret);
}

void
minic_fix_tree(MINIC_Compiler *compiler)
{
    FunctionDefinition *func_pos;
    DeclarationList *dl;
    int var_count = 0;

    fix_statement_list(NULL, compiler->statement_list, 0);

    for (func_pos = compiler->function_list; func_pos;
         func_pos = func_pos->next) {
	    if (func_pos->block == NULL)
            continue;
        add_parameter_as_declaration(func_pos);
        fix_statement_list(func_pos->block,
            func_pos->block->statement_list, func_pos);
        add_return_function(func_pos);
    }

    for (dl = compiler->declaration_list; dl; dl = dl->next) {
        dl->declaration->variable_index = var_count;
	    var_count++;
    }
}
