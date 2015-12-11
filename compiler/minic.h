#ifndef MINIC_H
#define MINIC_H
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

#define smaller(a,b) ((a) < (b) ? (a) : (b))
#define larger(a,b)  ((a) > (b) ? (a) : (b))

#define LINE_BUF_SIZE (1024)
#define MESSAGE_ARGUMENT_MAX (256)
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))
#define UNDEFINED_LABEL (-1)

typedef enum {
    MINIC_BOOLEAN_TYPE,
    MINIC_INTEGER_TYPE,
    MINIC_DECIMAL_TYPE,
    MINIC_STRING_TYPE,
    MINIC_VOID_TYPE,
    MINIC_CLASS_TYPE,
    MINIC_NULL_TYPE
} MINIC_BasicType;

typedef enum {
    MINIC_FILE_INPUT_MODE = 1,
    MINIC_STRING_INPUT_MODE
} MINIC_InputMode;

typedef enum {
    MINIC_FALSE = 0,
    MINIC_TRUE
} MINIC_Boolean;

typedef struct {
    char *format;
} ErrorDefinition;

typedef enum {
    INT_MESSAGE_ARGUMENT = 1,
    DECIMAL_MESSAGE_ARGUMENT,
    STRING_MESSAGE_ARGUMENT,
    CHARACTER_MESSAGE_ARGUMENT,
    POINTER_MESSAGE_ARGUMENT,
    MESSAGE_ARGUMENT_END
} MessageArgumentType;

typedef struct Expression_tag Expression;

typedef enum {
    BOOLEAN_EXPRESSION = 1,
    INTEGER_EXPRESSION,
    SHORT_EXPRESSION,
    LONG_EXPRESSION,    
    DECIMAL_EXPRESSION,
    CHARACTER_EXPRESSION,
    STRING_EXPRESSION,
    IDENTIFIER_EXPRESSION,
    COMMA_EXPRESSION,
    ASSIGN_EXPRESSION,
    ADD_EXPRESSION,
    SUB_EXPRESSION,
    MUL_EXPRESSION,
    DIV_EXPRESSION,
    MOD_EXPRESSION,
    EQ_EXPRESSION,
    NE_EXPRESSION,
    GT_EXPRESSION,
    GE_EXPRESSION,
    LT_EXPRESSION,
    LE_EXPRESSION,
    LOGICAL_AND_EXPRESSION,
    LOGICAL_OR_EXPRESSION,
    MINUS_EXPRESSION,
    LOGICAL_NOT_EXPRESSION,
    FUNCTION_CALL_EXPRESSION,
    MEMBER_EXPRESSION,
    NULL_EXPRESSION,
    ARRAY_LITERAL_EXPRESSION,
    INDEX_EXPRESSION,
    NEW_EXPRESSION,
    ARRAY_CREATION_EXPRESSION,
    INCREMENT_EXPRESSION,
    DECREMENT_EXPRESSION,
    CAST_EXPRESSION,
    EXPRESSION_KIND_COUNT_PLUS_1
} ExpressionKind;

#define minic_is_numeric_type(type) ((type) == MINIC_INTEGER_VALUE || (type) == MINIC_DECIMAL_VALUE)

#define minic_is_math_operator(operator) \
  ((operator) == ADD_EXPRESSION || (operator) == SUB_EXPRESSION\
  || (operator) == MUL_EXPRESSION || (OPERATOR) == DIV_EXPRESSION \
  || (operator) == MOD_EXPRESSION)

#define minic_is_compare_operator(operator) \
  ((operator) == EQ_EXPRESSION || (operator) == NE_EXPRESSION\
  || (operator) == GT_EXPRESSION || (operator) == GE_EXPRESSION\
  || (operator) == LT_EXPRESSION || (operator) == LE_EXPRESSION)

#define minic_is_integer(type) ((type)->basic_type == MINIC_INTEGER_TYPE && (type)->derive == NULL)

#define minic_is_decimal(type) ((type)->basic_type == MINIC_DECIMAL_TYPE && (type)->derive == NULL)

#define minic_is_boolean(type) ((type)->basic_type == MINIC_BOOLEAN_TYPE && (type)->derive == NULL)

#define minic_is_string(type) ((type)->basic_type == MINIC_STRING_TYPE && (type)->derive == NULL)

#define minic_is_array(type) ((type)->derive && ((type)->derive->tag==ARRAY_DERIVE))

#define minic_is_logical_operator(operator) ((operator) == LOGICAL_AND_EXPRESSION || (operator) == LOGICAL_OR_EXPRESSION)

typedef struct ArgumentList_tag {
    Expression *expression;
    struct ArgumentList_tag *next;
} ArgumentList;

typedef struct TypeSpecifier_tag TypeSpecifier;

typedef struct ParameterList_tag {
    char		*name;
    TypeSpecifier	*type;
    int			line_number;
    struct ParameterList_tag *next;
} ParameterList;

typedef enum {
    FUNCTION_DERIVE,
    ARRAY_DERIVE
} DeriveTag;

typedef struct ClassDefinition_tag ClassDefinition;

typedef struct {
    ParameterList	*parameter_list;
} FunctionDerive;

typedef struct {
    int dummy;
}ArrayDerive;

typedef struct TypeDerive_tag{
    DeriveTag tag;
    union {
        FunctionDerive function_d;
        ArrayDerive array_d;
    } u;
    struct TypeDerive_tag *next;
} TypeDerive;

struct TypeSpecifier_tag {
    MINIC_BasicType	basic_type;
    struct {
        char *identifier;
        int class_index;
        ClassDefinition *class_definition;
    }class_ref;
    int line_number;
    TypeDerive *derive;
};

typedef struct FunctionDefinition_tag FunctionDefinition;

typedef struct {
    char		*name;
    TypeSpecifier	*type;
    Expression		*initializer;
    int			variable_index;
    MINIC_Boolean	is_local;
} Declaration;

typedef struct DeclarationList_tag{
    Declaration *declaration;
    struct DeclarationList_tag *next;
} DeclarationList;

typedef enum{
    VARIABLE_IDENTIFIER,
    FUNCTION_IDENTIFIER
} IdentifierKind;

typedef struct {
    char		*name;
    IdentifierKind kind;
    union {
	FunctionDefinition *function;
	Declaration	*declaration;
    } u;
} IdentifierExpression;

typedef struct {
    Expression *left;
    Expression *right;
} CommaExpression;

typedef enum {
    NORMAL_ASSIGN = 1,
    ADD_ASSIGN,
    SUB_ASSIGN,
    MUL_ASSIGN,
    DIV_ASSIGN,
    MOD_ASSIGN
} AssignmentOperator;

typedef struct {
    AssignmentOperator operator;
    Expression *left;
    Expression *operand;
} AssignExpression;

typedef struct {
    Expression *left;
    Expression *right;
} BinaryExpression;

typedef struct {
    Expression *function;
    ArgumentList *argument;
} FunctionCallExpression;

typedef struct ExpressionList_tag{
    Expression *expression;
    struct ExpressionList_tag *next;
} ExpressionList;

typedef struct {
    Expression *array;
    Expression *index;
}IndexExpression;

typedef struct MemberDeclaration_tag MemberDeclaration;

typedef struct {
    Expression *expression;
    char *member_name;
    MemberDeclaration *declaration;
    int method_index;
}MemberExpression;

typedef struct {
    Expression *operand;
} IncrementOrDecrement;

typedef struct {
    char *class_name;
    ClassDefinition *class_definition;
    int class_index;
    ArgumentList *argumnet;
}NewExpression;

typedef struct ArrayDimension_tag{
    Expression *expression;
    struct ArrayDimension_tag *next;
}ArrayDimension;

typedef struct {
    TypeSpecifier *type;
    ArrayDimension *dimension;
}ArrayCreation;

struct Expression_tag {
    TypeSpecifier *type;
    ExpressionKind kind;
    int line_number;
    union {
        MINIC_Boolean		boolean_value;
	int			integer_value;
	float			decimal_value;
	char			*string_value;
	CommaExpression		comma;
	AssignExpression	assign_expression;
	IdentifierExpression	identifier;
	BinaryExpression	binary_expression;
	Expression		*minus_expression;
	Expression		*logical_not;
    MemberExpression member_expression;
    ExpressionList *array_literal;
	FunctionCallExpression	function_call_expression;
	IncrementOrDecrement	inc_dec;
    IndexExpression index_expression;
    NewExpression    new_e;
    ArrayCreation    array_creation;
    } u;
};

typedef struct Statement_tag Statement;

typedef struct StatementList_tag {
    Statement *statement;
    struct StatementList_tag *next;
} StatementList;

typedef enum {
    UNDEFINED_BLOCK = 1,
    FUNCTION_BLOCK,
    WHILE_STATEMENT_BLOCK,
    FOR_STATEMENT_BLOCK,
    DO_WHILE_STATEMENT_BLOCK
} BlockType;

typedef struct {
    Statement	*statement;
    int		continue_label;
    int		break_label;
} StatementBlockInfo;

typedef struct {
    FunctionDefinition *function;
    int 		end_label;
} FunctionBlockInfo;

typedef struct Block_tag {
    BlockType		type;
    struct Block_tag	*outer_block;
    StatementList	*statement_list;
    DeclarationList	*declaration_list;
    union {
        StatementBlockInfo	statement;
	FunctionBlockInfo	function;
    } parent;
} Block;

typedef struct Elseif_tag {
    Expression 	*condition;
    Block 	*block;
    struct Elseif_tag *next;
} Elseif;

typedef struct {
    Expression 	*condition;
    Block	*then_block;
    Elseif	*elseif_list;
    Block	*else_block;
} IfStatement;

typedef struct {
    char 	*label;
    Expression 	*condition;
    Block	*block;
} WhileStatement;

typedef struct {
    char	*label;
    Expression	*init;
    Expression	*condition;
    Expression  *post;
    Block	*block;
} ForStatement;

typedef struct {
    char *label;
    Block *block;
    Expression *condition;
}DoWhileStatement;

typedef struct {
    char 	*label;
    char 	*variable;
    Expression	*collection;
    Block	*block;
} ForeachStatement;

typedef struct {
    Expression 	*return_value;
} ReturnStatement;

typedef struct {
    char 	*label;
} BreakStatement;

typedef struct {
    char 	*label;
} ContinueStatement;

typedef enum {
    EXPRESSION_STATEMENT = 1,
    IF_STATEMENT,
    WHILE_STATEMENT,
    DO_WHILE_STATEMENT,
    FOR_STATEMENT,
    FOREACH_STATEMENT,
    RETURN_STATEMENT,
    BREAK_STATEMENT,
    CONTINUE_STATEMENT,
    DECLARATION_STATEMENT,
    STATEMENT_TYPE_COUNT_PLUS_1
} StatementType;

struct Statement_tag {
    StatementType	type;
    int			line_number;
    union {
	Expression	*expression_s;
	IfStatement	if_s;
	WhileStatement	while_s;
	ForStatement	for_s;
    DoWhileStatement do_while_s;
	ForeachStatement	foreach_s;
	BreakStatement	break_s;
	ContinueStatement	continue_s;
	ReturnStatement	return_s;
	Declaration	*declaration_s;
    } u;
};

struct FunctionDefinition_tag {
    TypeSpecifier	*type;
    char		*name;
    ParameterList	*parameter;
    Block		*block;
    int			local_variable_count;
    Declaration		**local_variable;
    int			index;
    ClassDefinition *class_definition;
    int			end_line_number;
    struct FunctionDefinition_tag	*next;
};

struct MemberDeclaration_tag {
    TypeSpecifier *type;
    int line_number;
    int index;
    char *name;
    struct MemberDeclaration_tag *next;
};

struct ClassDefinition_tag {
    char *name;
    MemberDeclaration *member;
    int line_number;
    struct ClassDefinition_tag *next;
};

typedef enum {
    EUC_ENCODING = 1,
    SHIFT_JIS_ENCODING,
    UTF_8_ENCODING
} Encoding;

typedef struct MINIC_Compiler_tag {
    /*Mem_Storage		compile_storage;*/
    FunctionDefinition	*function_list;
    int			function_count;
    int         class_count;
    DeclarationList	*declaration_list;
    StatementList	*statement_list;
    ClassDefinition *class_definition_list;
    int			current_line_number;
    Block		*current_block;
    ClassDefinition *current_class_definition;
    MINIC_InputMode	input_mode;
    Encoding		source_encoding;
} MINIC_Compiler;


typedef struct {
    char		*string;
} VString;

/* minic.l */
void minic_set_source_string(char **source);

/* create.c */
DeclarationList *minic_chain_declaration(DeclarationList *list,
					 Declaration *decl);
Declaration *minic_alloc_declaration(TypeSpecifier *type, char *identifier);
void minic_function_define(TypeSpecifier *type, char *identifier,
			   ParameterList *parameter_list, Block *block);
ParameterList *minic_create_parameter(TypeSpecifier *type, char *identifier);
ParameterList *minic_chain_parameter(ParameterList *list, TypeSpecifier *type, char *identifier);
ArgumentList *minic_create_argument_list(Expression *expression);
ArgumentList *minic_chain_argument_list(ArgumentList *list, Expression *expr);
StatementList *minic_create_statement_list(Statement *statement);
StatementList *minic_chain_statement_list(StatementList *list, Statement *statement);
ExpressionList *minic_create_expression_list(Expression *expression);
ExpressionList *minic_chain_expression_list(ExpressionList *list, Expression *expr);
TypeSpecifier *minic_create_type_specifier(MINIC_BasicType basic_type);
TypeSpecifier *minic_create_class_type_specifier(char *identifier);
TypeSpecifier *minic_create_array_type_specifier(TypeSpecifier *base);
Expression *minic_alloc_expression(ExpressionKind type);
Expression *minic_create_comma_expression(Expression *left, Expression *right);
Expression *minic_create_assign_expression(Expression *left, AssignmentOperator operator, Expression *operand);
Expression *minic_create_binary_expression(ExpressionKind operator, Expression *left, Expression *right);
Expression *minic_create_minus_expression(Expression *operand);
Expression *minic_create_logical_not_expression(Expression *operand);
Expression *minic_create_index_expression(Expression *array,Expression *index);
Expression *minic_create_incdec_expression(Expression *operand, ExpressionKind inc_or_dec);
Expression *minic_create_boolean_expression(MINIC_Boolean boolean_value);
Expression *minic_create_identifier_expression(char *identifier);
Expression *minic_create_function_call_expression(Expression *function, ArgumentList *argument);
Expression *minic_create_member_expression(Expression *expression, char *member_name);
Expression *minic_create_boolean_expression(MINIC_Boolean value);
Expression *minic_create_null_expression(void);
Expression *minic_create_new_expression(char *class_name, char *name);
Expression *minic_create_basic_array_creation(MINIC_BasicType basic_type, ArrayDimension *dim_expr, ArrayDimension *dim_ilst);
Expression *minic_create_class_array_creation(TypeSpecifier *type, ArrayDimension *dim_expr, ArrayDimension *dim_ilst);
Expression *minic_create_array_literal_expression(ExpressionList *list);
Expression *minic_create_array_creation(MINIC_BasicType basic_type, ArrayDimension *dim_expr_list, ArrayDimension *dim_ilst);
ArrayDimension *minic_create_array_dimension(Expression *expr);
ArrayDimension *minic_chain_array_dimension(ArrayDimension *list, ArrayDimension *dim_ilst);
Statement *minic_create_if_statement(Expression *condition, Block* then_block, Elseif *elseif_list, Block *else_block);
Elseif *minic_chain_elseif_list(Elseif *list, Elseif *add);
Elseif *minic_create_elseif(Expression *expr, Block *block);
Statement *minic_create_while_statement(char *label, Expression *condition, Block *block);
Statement *minic_create_do_while_statement(char *label, Block *block, Expression *condition);
Statement *minic_create_foreach_statement(char *label, char *variable, Expression *collection, Block *block);
Statement *minic_create_for_statement(char *label, Expression *init, Expression *cond, Expression *post, Block *block);
Block *minic_alloc_block(void);
Block *minic_open_block(void);
Block *minic_close_block(Block *block, StatementList *statement_list);
Statement *minic_create_expression_statement(Expression *expression);
Statement *minic_create_return_statement(Expression *expression);
Statement *minic_create_break_statement(char *label);
Statement *minic_create_continue_statement(char *label);
Statement *minic_create_declaration_statement(TypeSpecifier *type, char *identifier, Expression *initializer);
void minic_start_class_definition(char *identifier);
void minic_class_define(MemberDeclaration *member_list);
MemberDeclaration *minic_chain_member_declaration(MemberDeclaration *list, MemberDeclaration *add);
MemberDeclaration *minic_create_field_member(TypeSpecifier *type, char *name);
/* string.c */
char *minic_create_identifier(char *str);
void minic_open_string_literal(void);
void minic_add_string_literal(int letter);
void minic_reset_string_literal_buffer(void);
char *minic_close_string_literal(void);

/* fix_tree.c */
void minic_fix_tree(MINIC_Compiler *compiler);

/* generate.c */
//MINIC_Executable *minic_generate(MINIC_Compiler *compiler);

/* util.c */
MINIC_Compiler *MINIC_create_compiler(void);
MINIC_Compiler *minic_get_current_compiler(void);
void do_compile(MINIC_Compiler *compiler, FILE *fd);
void minic_set_current_compiler(MINIC_Compiler *compiler);
void *minic_malloc(size_t size);
TypeSpecifier *minic_alloc_type_specifier(MINIC_BasicType type);
TypeDerive *minic_alloc_type_derive(DeriveTag derive_tag);
FunctionDefinition *minic_search_function(char *name);
Declaration *minic_search_declaration(char *identifier, Block *block);
ClassDefinition *minic_search_class(char *identifier);
MemberDeclaration *minic_search_member(ClassDefinition *class_def, char *member_name);
void minic_vstr_clear(VString *v);
void minic_vstr_append_string(VString *v, char *str);
void minic_vstr_append_character(VString *v, char ch);
char *minic_get_basic_type_name(MINIC_BasicType type);
char *minic_expression_to_string(Expression *expr);

/* main.c */
int display_program();

#endif//MINIC_H
