#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "MEM.h"
#include "minic.h"

extern OpcodeInfo mvm_opcode_info[];

#define OPCODE_ALLOC_SIZE (256)
#define LABEL_TABLE_ALLOC_SIZE (256)

typedef struct {
    int label_address;
} LabelTable;

typedef struct {
    int         size;
    int         alloc_size;
    MVM_Byte    *code;
    int         label_table_size;
    int         label_table_alloc_size;
    LabelTable  *label_table;
    int         line_number_size;
    MVM_LineNumber      *line_number;
} OpcodeBuf;

static MVM_Executable *
alloc_executable()
{
    MVM_Executable      *exe;
    exe = MEM_malloc(sizeof(MVM_Executable));
    exe->is_required = MVM_FALSE;
    exe->constant_pool_count = 0;
    exe->constant_pool = NULL;
    exe->global_variable_count = 0;
    exe->global_variable = NULL;
    exe->function_count = 0;
    exe->function = NULL;
    exe->type_specifier_count = 0;
    exe->type_specifier = NULL;
    exe->code_size = 0;
    exe->code = NULL;
    return exe;
}

static MVM_TypeSpecifier *copy_type_specifier(TypeSpecifier *src);

static int
count_parameter(ParameterList *src)
{
    ParameterList *param;
    int param_count = 0;

    for (param = src; param; param = param->next) {
        param_count++;
    }

    return param_count;
}


static MVM_LocalVariable *
copy_parameter_list(ParameterList *src, int *param_count_p)
{
    ParameterList *param;
    MVM_LocalVariable *dest;
    int param_count;
    int i;

    param_count = count_parameter(src);
    *param_count_p = param_count;

    dest = MEM_malloc(sizeof(MVM_LocalVariable) * param_count);
    
    for (param = src, i = 0; param; param = param->next, i++) {
        dest[i].name = MEM_strdup(param->name);
        dest[i].type = copy_type_specifier(param->type);
    }

    return dest;
}

static MVM_LocalVariable *
copy_local_variables(FunctionDefinition *fd, int param_count)
{
    int i;
    int local_variable_count;
    MVM_LocalVariable *dest;

    local_variable_count = fd->local_variable_count - param_count;

    dest = MEM_malloc(sizeof(MVM_LocalVariable) * local_variable_count);

    for (i = 0; i < local_variable_count; i++) {
        dest[i].name
            = MEM_strdup(fd->local_variable[i+param_count]->name);
        dest[i].type
            = copy_type_specifier(fd->local_variable[i+param_count]->type);
    }

    return dest;
}


static void
copy_type_specifier_no_alloc(TypeSpecifier *src, MVM_TypeSpecifier *dest)
{
    int derive_count = 0;
    TypeDerive *derive;
    int i;

    dest->basic_type = src->basic_type;
    if (src->basic_type == MVM_CLASS_TYPE) {
        dest->class_index = src->class_ref.class_index;
    } else {
        dest->class_index = -1;
    }

    for (derive = src->derive; derive; derive = derive->next) {
        derive_count++;
    }
    dest->derive_count = derive_count;
    dest->derive = MEM_malloc(sizeof(MVM_TypeDerive) * derive_count);
    for (i = 0, derive = src->derive; derive;
         derive = derive->next, i++) {
        switch (derive->tag) {
        case ARRAY_DERIVE:
            dest->derive[i].tag = MVM_ARRAY_DERIVE;
            break;
	    case FUNCTION_DERIVE:
		    break;
        }
    }

}

MVM_TypeSpecifier *
copy_type_specifier(TypeSpecifier *src)
{
    MVM_TypeSpecifier *dest;

    dest = MEM_malloc(sizeof(MVM_TypeSpecifier));

    copy_type_specifier_no_alloc(src, dest);

    return dest;
}

static int
add_type_specifier(TypeSpecifier *src, MVM_Executable *exe)
{
    int ret;

    exe->type_specifier = MEM_realloc(exe->type_specifier,
        sizeof(MVM_TypeSpecifier) * (exe->type_specifier_count + 1));
    copy_type_specifier_no_alloc(src, 
	    &exe->type_specifier[exe->type_specifier_count]);

    ret = exe->type_specifier_count;
    exe->type_specifier_count++;

    return ret;
}

static void
add_global_variable(MINIC_Compiler *compiler, MVM_Executable *exe)
{
    DeclarationList *dl;
    int i;
    int var_count = 0;

    for (dl = compiler->declaration_list; dl; dl = dl->next) {
        var_count++;
    }
    exe->global_variable_count = var_count;
    exe->global_variable = MEM_malloc(sizeof(MVM_Variable) * var_count);

    for (dl = compiler->declaration_list, i = 0; dl; dl = dl->next, i++) {
        exe->global_variable[i].name = MEM_strdup(dl->declaration->name);
        exe->global_variable[i].type
            = copy_type_specifier(dl->declaration->type);
    }
}

static void
add_field(MemberDeclaration *member, MVM_Field *dest)
{
    dest->type = copy_type_specifier(member->type);
}

/*
static mvm_class *
search_class(MINIC_Compiler *compiler, ClassDefinition *src)
{
    int i;
    for (i = 0; i < compiler->MVM_class_count; i++) {
        if (!strcmp(src->name, compiler->MVM_class[i].name)) {
            return &compiler->MVM_class[i];
        }
    }

    return NULL;
}
*/

static void
add_class(MVM_Executable *exe, ClassDefinition *cd, MVM_Class *dest)
{
	int field_count = 0;
    MemberDeclaration *pos;

    for (pos = cd->member; pos; pos = pos->next) {
         field_count++;
    }
    dest->field_count = field_count;
    dest->field = MEM_malloc(sizeof(MVM_Field) * field_count);

    field_count = 0;
    for (pos = cd->member; pos; pos = pos->next) {
         add_field(pos, &dest->field[field_count]);
         field_count++;
    }
}

static void
add_classes(MINIC_Compiler *compiler, MVM_Executable *exe)
{
    int i;
    ClassDefinition *cd;

    for (i = 0; i < compiler->mvm_class_count; i++) {
        cd = minic_search_class(compiler->mvm_class[i].name);
        add_class(exe, cd, &compiler->mvm_class[i]);
    }
}
/*
static void generate_expression(MVM_Executable *exe, Block *current_block,
                                Expression *expr, OpcodeBuf *ob);
*/								

static void
init_opcode_buf(OpcodeBuf *ob)
{
    ob->size = 0;
    ob->alloc_size = 0;
    ob->code = NULL;
    ob->label_table_size = 0;
    ob->label_table_alloc_size = 0;
    ob->label_table = NULL;
    ob->line_number_size = 0;
    ob->line_number = NULL;
}

static void
fix_labels(OpcodeBuf *ob)
{
    int i;
    int j;
    OpcodeInfo *info;
    int label;
    int address;

    for (i = 0; i < ob->size; i++) {
        if (ob->code[i] == MVM_JUMP
            || ob->code[i] == MVM_JUMP_IF_TRUE
            || ob->code[i] == MVM_JUMP_IF_FALSE) {
            label = (ob->code[i+1] << 8) + (ob->code[i+2]);
            address = ob->label_table[label].label_address;
            ob->code[i+1] = (MVM_Byte)(address >> 8);
            ob->code[i+2] = (MVM_Byte)(address &0xff);
        }
        info = &mvm_opcode_info[ob->code[i]];
        for (j = 0; info->parameter[j] != '\0'; j++) {
            switch (info->parameter[j]) {
            case 'b':
                i++;
                break;
            case 's': /* FALLTHRU */
            case 'p':
                i += 2;
                break;
            }
        }
    }
}

static int
get_opcode_type_offset(TypeSpecifier *type)
{
    switch (type->basic_type) {
    case MVM_VOID_TYPE:
        break;
    case MVM_BOOLEAN_TYPE:
    case MVM_INTEGER_TYPE:
        return 0;
        break;
    case MVM_DECIMAL_TYPE:
        return 1;
        break;
    case MVM_STRING_TYPE:
    case MVM_CLASS_TYPE:
        return 2;
        break;
    case MVM_NULL_TYPE:
    case MVM_BASE_TYPE:
        break;
    }

    return 0;
}

static MVM_Byte *
fix_opcode_buf(OpcodeBuf *ob)
{
    MVM_Byte *ret;

    fix_labels(ob);
    ret = MEM_realloc(ob->code, ob->size);
    MEM_free(ob->label_table);

    return ret;
}

static int
calc_need_stack_size(MVM_Byte *code, int code_size)
{
    int i, j;
    int stack_size = 0;
    OpcodeInfo  *info;

    for (i = 0; i < code_size; i++) {
        info = &mvm_opcode_info[code[i]];
        if (info->stack_increment > 0) {
            stack_size += info->stack_increment;
        }
        for (j = 0; info->parameter[j] != '\0'; j++) {
            switch (info->parameter[j]) {
            case 'b':
                i++;
                break;
            case 's': /* FALLTHRU */
            case 'p':
                i += 2;
                break;
            }
        }
    }

    return stack_size;
}

//==================================================================//
// Get and set label
// Return current label_table_size as a label
static int
get_label(OpcodeBuf *ob)
{
    int ret;

    if (ob->label_table_alloc_size < ob->label_table_size + 1) {
        ob->label_table = MEM_realloc(ob->label_table,    // realloc label table
             (ob->label_table_alloc_size + LABEL_TABLE_ALLOC_SIZE) * sizeof(LabelTable));
        ob->label_table_alloc_size += LABEL_TABLE_ALLOC_SIZE;
    }
    ret = ob->label_table_size;
    ob->label_table_size++;

    return ret;
}
// Set the label to its position
static void
set_label(OpcodeBuf *ob, int label)
{
    ob->label_table[label].label_address = ob->size;
}

//==================================================================//
// Generate code

static void
add_line_number(OpcodeBuf *ob, int line_number, int start_pc)
{
    if (ob->line_number == NULL
        || (ob->line_number[ob->line_number_size-1].line_number
            != line_number)) {
        ob->line_number = MEM_realloc(ob->line_number,
                                      sizeof(MVM_LineNumber)
                                      * (ob->line_number_size + 1));

        ob->line_number[ob->line_number_size].line_number = line_number;
        ob->line_number[ob->line_number_size].start_pc = start_pc;
        ob->line_number[ob->line_number_size].pc_count
            = ob->size - start_pc;
        ob->line_number_size++;

    } else {
        ob->line_number[ob->line_number_size-1].pc_count
            += ob->size - start_pc;
    }
}

static void
generate_code(OpcodeBuf *ob, int line_number, MVM_Opcode code,  ...)
{
    va_list     ap;
    int         i;
    char        *param;
    int         param_count;
    int         start_pc;

    va_start(ap, code);

    param = mvm_opcode_info[(int)code].parameter;
    param_count = strlen(param);
    if (ob->alloc_size < ob->size + 1 + (param_count * 2)) {
        ob->code = MEM_realloc(ob->code, ob->alloc_size + OPCODE_ALLOC_SIZE);
        ob->alloc_size += OPCODE_ALLOC_SIZE;
    }

    start_pc = ob->size;
    ob->code[ob->size] = code;
    ob->size++;
    for (i = 0; param[i] != '\0'; i++) {
        unsigned int value = va_arg(ap, int);
        switch (param[i]) {
        case 'b': /* byte */
            ob->code[ob->size] = (MVM_Byte)value;
            ob->size++;
            break;
        case 's': /* short(2byte int) */
            ob->code[ob->size] = (MVM_Byte)(value >> 8);
            ob->code[ob->size+1] = (MVM_Byte)(value & 0xff);
            ob->size += 2;
            break;
        case 'p': /* constant pool index */
            ob->code[ob->size] = (MVM_Byte)(value >> 8);
            ob->code[ob->size+1] = (MVM_Byte)(value & 0xff);
            ob->size += 2;
            break;
        //default:
        //    DBG_assert(0, ("param..%s, i..%d", param, i));
        }
    }
    add_line_number(ob, line_number, start_pc);

    va_end(ap);
}

static void generate_statement_list(MVM_Executable *exe, Block *current_block,
                                    StatementList *statement_list,
                                    OpcodeBuf *ob);

//==================================================================//
// Generate various kinds of expressions

static void
generate_expression(MVM_Executable *exe, Block *current_block,
                    Expression *expr, OpcodeBuf *ob);

static void
generate_assign_expression(MVM_Executable *exe, Block *block,
                           Expression *expr, OpcodeBuf *ob,
                           MVM_Boolean is_toplevel);
						   
static void
generate_boolean_expression(MVM_Executable *cf, Expression *expr,
                            OpcodeBuf *ob)
{
    if (expr->u.boolean_value) {
        generate_code(ob, expr->line_number, MVM_PUSH_INT_1BYTE, 1);
    } else {
        generate_code(ob, expr->line_number, MVM_PUSH_INT_1BYTE, 0);
    }
}

//   add_constant_pool() is called by generate_integer, generate_decimal
// and generate_string. It returns the index of the newly added constant
// in the pool.
static int
add_constant_pool(MVM_Executable *exe, MVM_ConstantPool *cp)
{
    int ret;

    exe->constant_pool = MEM_realloc(exe->constant_pool,    // realloc the constant_pool
        sizeof(MVM_ConstantPool) * (exe->constant_pool_count + 1));
    exe->constant_pool[exe->constant_pool_count] = *cp;     // set the last element of the constant_pool to the new constant

    ret = exe->constant_pool_count;
    exe->constant_pool_count++;                             // add constant_pool_count

    return ret;
}

static void
generate_integer_expression(MVM_Executable *cf, int line_number, 
                            int value, OpcodeBuf *ob)
{
    MVM_ConstantPool cp;
    int cp_idx;

    if (value >= 0 && value < 256) {
        generate_code(ob, line_number, MVM_PUSH_INT_1BYTE, value);
    } else if (value >= 0 && value < 65536) {
        generate_code(ob, line_number, MVM_PUSH_INT_2BYTE, value);
    } else {
        cp.tag = MVM_CONSTANT_INT;
        cp.u.c_integer = value;
        cp_idx = add_constant_pool(cf, &cp);

        generate_code(ob, line_number, MVM_PUSH_INT, cp_idx);
    }
}

static void
generate_decimal_expression(MVM_Executable *cf, Expression *expr,
                           OpcodeBuf *ob)
{
    MVM_ConstantPool cp;
    int cp_idx;

    if (expr->u.decimal_value == 0.0) {
        generate_code(ob, expr->line_number, MVM_PUSH_DOUBLE_0);
    } else if (expr->u.decimal_value == 1.0) {
        generate_code(ob, expr->line_number, MVM_PUSH_DOUBLE_1);
    } else {
        cp.tag = MVM_CONSTANT_DOUBLE;
        cp.u.c_decimal = expr->u.decimal_value;
        cp_idx = add_constant_pool(cf, &cp);

        generate_code(ob, expr->line_number, MVM_PUSH_DOUBLE, cp_idx);
    }
}

static void
generate_string_expression(MVM_Executable *cf, Expression *expr,
                           OpcodeBuf *ob)
{
    MVM_ConstantPool cp;
    int cp_idx;

    cp.tag = MVM_CONSTANT_STRING;
    cp.u.c_string = expr->u.string_value;
    cp_idx = add_constant_pool(cf, &cp);
    generate_code(ob, expr->line_number, MVM_PUSH_STRING, cp_idx);
}

static void
generate_identifier(Declaration *decl, OpcodeBuf *ob, int line_number)
{
    if (decl->is_local) { // local identifier
        generate_code(ob, line_number, 
		    MVM_PUSH_STACK_INT + get_opcode_type_offset(decl->type),
            decl->variable_index);
    } else {              // global identifier
        generate_code(ob, line_number,
            MVM_PUSH_STATIC_INT + get_opcode_type_offset(decl->type),
            decl->variable_index);
    }
}

static void
generate_identifier_expression(MVM_Executable *exe, Block *block,
                               Expression *expr, OpcodeBuf *ob)
{
    switch (expr->u.identifier.kind) {
    case VARIABLE_IDENTIFIER:
        generate_identifier(expr->u.identifier.u.declaration, ob,
            expr->line_number);
        break;
    case FUNCTION_IDENTIFIER:
        generate_code(ob, expr->line_number,
            MVM_PUSH_FUNCTION, expr->u.identifier.u.function->index);
        break;
    }
}

static int
get_binary_expression_offset(Expression *left, Expression *right,
                             MVM_Opcode code)
{
    int offset;

    if ((left->kind == NULL_EXPRESSION && right->kind != NULL_EXPRESSION)
        || (left->kind != NULL_EXPRESSION && right->kind == NULL_EXPRESSION)) {
        offset = 2; /* object type */
    } else if ((code == MVM_EQ_INT || code == MVM_NE_INT)
               && minic_is_string(left->type)) {
        offset = 3; /* string type */
    } else {
        offset = get_opcode_type_offset(left->type);
    }

    return offset;
}

static void
generate_binary_expression(MVM_Executable *exe, Block *block,
                           Expression *expr, MVM_Opcode code,
                           OpcodeBuf *ob)
{
    int offset;
    Expression *left = expr->u.binary_expression.left;
    Expression *right = expr->u.binary_expression.right;

    generate_expression(exe, block, left, ob);
    generate_expression(exe, block, right, ob);

    offset = get_binary_expression_offset(left, right, code);
    // (code + offset) is a opcode
    generate_code(ob, expr->line_number, code + offset);
}

static void
generate_logical_and_expression(MVM_Executable *exe, Block *block,
    Expression *expr, OpcodeBuf *ob)
{
    int false_label;

    false_label = get_label(ob);    // Get label
    generate_expression(exe, block, expr->u.binary_expression.left, ob);
    generate_code(ob, expr->line_number, MVM_DUPLICATE);
    generate_code(ob, expr->line_number, MVM_JUMP_IF_FALSE, false_label);
    generate_expression(exe, block, expr->u.binary_expression.right, ob);
    generate_code(ob, expr->line_number, MVM_LOGICAL_AND);
    set_label(ob, false_label);     // Set label
}

static void
generate_logical_or_expression(MVM_Executable *exe, Block *block,
                               Expression *expr,
                               OpcodeBuf *ob)
{
    int true_label;

    true_label = get_label(ob);    // Get label
    generate_expression(exe, block, expr->u.binary_expression.left, ob);
    generate_code(ob, expr->line_number, MVM_DUPLICATE);
    generate_code(ob, expr->line_number, MVM_JUMP_IF_TRUE, true_label);
    generate_expression(exe, block, expr->u.binary_expression.right, ob);
    generate_code(ob, expr->line_number, MVM_LOGICAL_OR);
    set_label(ob, true_label);     // Set label
}

static void
generate_push_argument(MVM_Executable *exe, Block *block,
                       ArgumentList *arg_list, OpcodeBuf *ob)
{
    ArgumentList *arg_pos;

    for (arg_pos = arg_list; arg_pos; arg_pos = arg_pos->next) {
        generate_expression(exe, block, arg_pos->expression, ob);
    }
}

static void
generate_function_call_expression(MVM_Executable *exe, Block *block,
                                  Expression *expr, OpcodeBuf *ob)
{
    FunctionCallExpression *fce = &expr->u.function_call_expression;

    generate_push_argument(exe, block, fce->argument, ob);
    generate_expression(exe, block, fce->function, ob);
    generate_code(ob, expr->line_number, MVM_INVOKE);
}

static void
generate_member_expression(MVM_Executable *exe, Block *block,
                           Expression *expr, OpcodeBuf *ob)
{
    MemberDeclaration *member;
    
    member = expr->u.member_expression.declaration;
    generate_expression(exe, block,
        expr->u.member_expression.expression, ob);
    generate_code(ob, expr->line_number,
        MVM_PUSH_FIELD_INT + get_opcode_type_offset(expr->type),
        member->index);
}

static void
generate_null_expression(MVM_Executable *exe, Expression *expr,
                         OpcodeBuf *ob)
{
    generate_code(ob, expr->line_number, MVM_PUSH_NULL);
}
/*
static void
generate_new_expression(MVM_Executable *exe, Block *block,
                        Expression *expr, OpcodeBuf *ob)
{

    generate_code(ob, expr->line_number, MVM_NEW,
        expr->u.new_e.class_index);
    generate_push_argument(exe, block, expr->u.new_e.argument, ob);

    generate_code(ob, expr->line_number, MVM_PUSH_METHOD,
                  expr->u.new_e.method_declaration->u.method.method_index);
    generate_code(ob, expr->line_number, MVM_INVOKE);
    generate_code(ob, expr->line_number, MVM_POP);
}
*/

static void
generate_array_literal_expression(MVM_Executable *exe, Block *block,
                                  Expression *expr, OpcodeBuf *ob)
{
    ExpressionList *pos;
    int count;

    count = 0;
    for (pos = expr->u.array_literal; pos; pos = pos->next) {
        generate_expression(exe, block, pos->expression, ob);
        count++;
    }
    
    generate_code(ob, expr->line_number,
        MVM_NEW_ARRAY_LITERAL_INT + 
		get_opcode_type_offset(expr->u.array_literal->expression->type),
        count);
}

static void
generate_index_expression(MVM_Executable *exe, Block *block,
                          Expression *expr, OpcodeBuf *ob)
{
    generate_expression(exe, block, expr->u.index_expression.array, ob);
    generate_expression(exe, block, expr->u.index_expression.index, ob);

    generate_code(ob, expr->line_number, MVM_PUSH_ARRAY_INT
        + get_opcode_type_offset(expr->type));
}

static void
generate_pop_to_identifier(Declaration *decl, int line_number,
                           OpcodeBuf *ob)
{
    if (decl->is_local) {
        generate_code(ob, line_number,
            MVM_POP_STACK_INT + get_opcode_type_offset(decl->type),
            decl->variable_index);
    } else {
        generate_code(ob, line_number,
            MVM_POP_STATIC_INT + get_opcode_type_offset(decl->type),
            decl->variable_index);
    }
}

static void
generate_pop_to_member(MVM_Executable *exe, Block *block,
                       Expression *expr, OpcodeBuf *ob)
{
    MemberDeclaration *member;

    member = expr->u.member_expression.declaration;
    generate_expression(exe, block, expr->u.member_expression.expression, ob);
    generate_code(ob, expr->line_number, MVM_POP_FIELD_INT
        + get_opcode_type_offset(member->type),
        member->index);
}

static void
generate_pop_to_lvalue(MVM_Executable *exe, Block *block,
                       Expression *expr, OpcodeBuf *ob)
{
    if (expr->kind == IDENTIFIER_EXPRESSION) {
        generate_pop_to_identifier(expr->u.identifier.u.declaration,
             expr->line_number, ob);
    } else if (expr->kind == INDEX_EXPRESSION) {
        generate_expression(exe, block, expr->u.index_expression.array, ob);
        generate_expression(exe, block, expr->u.index_expression.index, ob);
        generate_code(ob, expr->line_number, MVM_POP_ARRAY_INT
            + get_opcode_type_offset(expr->type));
    } else {
        generate_pop_to_member(exe, block, expr, ob);
    }
}

static void
generate_inc_dec_expression(MVM_Executable *exe, Block *block,
                            Expression *expr, ExpressionKind kind,
                            OpcodeBuf *ob, MVM_Boolean is_toplevel)
{
    generate_expression(exe, block, expr->u.inc_dec.operand, ob);

    if (kind == INCREMENT_EXPRESSION) {
        generate_code(ob, expr->line_number, MVM_INCREMENT);
    } else {
        generate_code(ob, expr->line_number, MVM_DECREMENT);
    }
    if (!is_toplevel) {
        generate_code(ob, expr->line_number, MVM_DUPLICATE);
    }
    generate_pop_to_lvalue(exe, block,
        expr->u.inc_dec.operand, ob);
}

static void
generate_cast_expression(MVM_Executable *exe, Block *block,
                         Expression *expr, OpcodeBuf *ob)
{
    switch (expr->u.cast.type) {
    case INTEGER_TO_DECIMAL_CAST:
        generate_expression(exe, block, expr->u.cast.operand, ob);
        generate_code(ob, expr->line_number, MVM_CAST_INT_TO_DOUBLE);
        break;
    case DECIMAL_TO_INTEGER_CAST:
        generate_expression(exe, block, expr->u.cast.operand, ob);
        generate_code(ob, expr->line_number, MVM_CAST_DOUBLE_TO_INT);
        break;
    case BOOLEAN_TO_STRING_CAST:
        generate_expression(exe, block, expr->u.cast.operand, ob);
        generate_code(ob, expr->line_number, MVM_CAST_BOOLEAN_TO_STRING);
        break;
    case INTEGER_TO_STRING_CAST:
        generate_expression(exe, block, expr->u.cast.operand, ob);
        generate_code(ob, expr->line_number, MVM_CAST_INT_TO_STRING);
        break;
    case DECIMAL_TO_STRING_CAST:
        generate_expression(exe, block, expr->u.cast.operand, ob);
        generate_code(ob, expr->line_number, MVM_CAST_DOUBLE_TO_STRING);
        break;
    }
}

static void
generate_array_creation_expression(MVM_Executable *exe, Block *block,
                                   Expression *expr, OpcodeBuf *ob)
{
    int index;
    //TypeSpecifier type;
    ArrayDimension *dim_pos;
    int dim_count;

    index = add_type_specifier(expr->type, exe);

    //type.basic_type = expr->type->basic_type;
    //type.derive = expr->type->derive;

    dim_count = 0;
    for (dim_pos = expr->u.array_creation.dimension;
         dim_pos; dim_pos = dim_pos->next) {
        if (dim_pos->expression == NULL)
            break;

        generate_expression(exe, block, dim_pos->expression, ob);
        dim_count++;
    }

    generate_code(ob, expr->line_number, MVM_NEW_ARRAY, dim_count, index);
}

static void
generate_expression(MVM_Executable *exe, Block *current_block,
                    Expression *expr, OpcodeBuf *ob)
{
    switch (expr->kind) {
    case BOOLEAN_EXPRESSION:
        generate_boolean_expression(exe, expr, ob);
        break;
    case INTEGER_EXPRESSION:
        generate_integer_expression(exe, expr->line_number, 
		    expr->u.integer_value, ob);
        break;
    case DECIMAL_EXPRESSION:
        generate_decimal_expression(exe, expr, ob);
        break;
    case STRING_EXPRESSION:
        generate_string_expression(exe, expr, ob);
        break;
    case IDENTIFIER_EXPRESSION:
        generate_identifier_expression(exe, current_block, expr, ob);
        break;
    case COMMA_EXPRESSION:
        generate_expression(exe, current_block, expr->u.comma.left, ob);
        generate_expression(exe, current_block, expr->u.comma.right, ob);
        break;
    case ASSIGN_EXPRESSION:
        generate_assign_expression(exe, current_block, expr, ob, MVM_FALSE);
        break;
    case ADD_EXPRESSION:
        generate_binary_expression(exe, current_block, expr,
            MVM_ADD_INT, ob);
        break;
    case SUB_EXPRESSION:
        generate_binary_expression(exe, current_block, expr,
            MVM_SUB_INT, ob);
        break;
    case MUL_EXPRESSION:
        generate_binary_expression(exe, current_block, expr,
            MVM_MUL_INT, ob);
        break;
    case DIV_EXPRESSION:
        generate_binary_expression(exe, current_block, expr,
            MVM_DIV_INT, ob);
        break;
    case MOD_EXPRESSION:
        generate_binary_expression(exe, current_block, expr,
            MVM_MOD_INT, ob);
        break;
    case EQ_EXPRESSION:
        generate_binary_expression(exe, current_block, expr,
            MVM_EQ_INT, ob);
        break;
    case NE_EXPRESSION:
        generate_binary_expression(exe, current_block, expr,
            MVM_NE_INT, ob);
        break;
    case GT_EXPRESSION:
        generate_binary_expression(exe, current_block, expr,
            MVM_GT_INT, ob);
        break;
    case GE_EXPRESSION:
        generate_binary_expression(exe, current_block, expr,
            MVM_GE_INT, ob);
        break;
    case LT_EXPRESSION:
        generate_binary_expression(exe, current_block, expr,
            MVM_LT_INT, ob);
        break;
    case LE_EXPRESSION:
        generate_binary_expression(exe, current_block, expr,
            MVM_LE_INT, ob);
        break;
    case LOGICAL_AND_EXPRESSION:
        generate_logical_and_expression(exe, current_block, expr, ob);
        break;
    case LOGICAL_OR_EXPRESSION:
        generate_logical_or_expression(exe, current_block, expr, ob);
        break;
    case MINUS_EXPRESSION:
        generate_expression(exe, current_block, expr->u.minus_expression, ob);
        generate_code(ob, expr->line_number,
            MVM_MINUS_INT + get_opcode_type_offset(expr->type));
        break;
    case LOGICAL_NOT_EXPRESSION:
        generate_expression(exe, current_block, expr->u.logical_not, ob);
        generate_code(ob, expr->line_number, MVM_LOGICAL_NOT);
        break;
    case FUNCTION_CALL_EXPRESSION:
        generate_function_call_expression(exe, current_block, expr, ob);
        break;
    case MEMBER_EXPRESSION:
        generate_member_expression(exe, current_block, expr, ob);
        break;
    case NULL_EXPRESSION:
        generate_null_expression(exe, expr, ob);
        break;
    case NEW_EXPRESSION:
        //generate_new_expression(exe, current_block, expr, ob);
        break;
    case ARRAY_LITERAL_EXPRESSION:
        generate_array_literal_expression(exe, current_block, expr, ob);
        break;
    case INDEX_EXPRESSION:
        generate_index_expression(exe, current_block, expr, ob);
        break;
    case INCREMENT_EXPRESSION:
    case DECREMENT_EXPRESSION:
        generate_inc_dec_expression(exe, current_block, expr, expr->kind,
            ob, MVM_FALSE);
        break;
    case CAST_EXPRESSION:
        generate_cast_expression(exe, current_block, expr, ob);
        break;
    case ARRAY_CREATION_EXPRESSION:
        generate_array_creation_expression(exe, current_block, expr, ob);
        break;
	case SHORT_EXPRESSION:
	case LONG_EXPRESSION:
	case CHARACTER_EXPRESSION:
	case EXPRESSION_KIND_COUNT_PLUS_1:
	    break;
    }
}
									
static void
generate_assign_expression(MVM_Executable *exe, Block *block,
                           Expression *expr, OpcodeBuf *ob,
                           MVM_Boolean is_toplevel)
{
    if (expr->u.assign_expression.operator != NORMAL_ASSIGN) {
        generate_expression(exe, block, expr->u.assign_expression.left, ob);
    }
    generate_expression(exe, block, expr->u.assign_expression.operand, ob);

    switch (expr->u.assign_expression.operator) {
    case NORMAL_ASSIGN :
        break;
    case ADD_ASSIGN:
        generate_code(ob, expr->line_number,
            MVM_ADD_INT + get_opcode_type_offset(expr->type));
        break;
    case SUB_ASSIGN:
        generate_code(ob, expr->line_number,
            MVM_SUB_INT + get_opcode_type_offset(expr->type));
        break;
    case MUL_ASSIGN:
        generate_code(ob, expr->line_number,
            MVM_MUL_INT + get_opcode_type_offset(expr->type));
        break;
    case DIV_ASSIGN:
        generate_code(ob, expr->line_number,
            MVM_DIV_INT + get_opcode_type_offset(expr->type));
        break;
    case MOD_ASSIGN:
        generate_code(ob, expr->line_number,
            MVM_MOD_INT + get_opcode_type_offset(expr->type));
        break;
    }

    if (!is_toplevel) {
        generate_code(ob, expr->line_number, MVM_DUPLICATE);
    }
    generate_pop_to_lvalue(exe, block,
        expr->u.assign_expression.left, ob);
}

static void
generate_initializer(MVM_Executable *exe, Block *block,
                     Statement *statement, OpcodeBuf *ob)
{
    Declaration *decl = statement->u.declaration_s;
    if (decl->initializer == NULL)
        return;

    generate_expression(exe, block, decl->initializer, ob);
    generate_pop_to_identifier(decl, statement->line_number, ob);
}

//==================================================================//
// Generate statements
									
static void
generate_expression_statement(MVM_Executable *exe, Block *block,
                              Expression *expr, OpcodeBuf *ob)
{
    if (expr->kind == ASSIGN_EXPRESSION) {
        generate_assign_expression(exe, block, expr, ob, MVM_TRUE);
    } else if (expr->kind == INCREMENT_EXPRESSION
               || expr->kind == DECREMENT_EXPRESSION) {
        generate_inc_dec_expression(exe, block, expr, expr->kind, ob, MVM_TRUE);
    } else {
        generate_expression(exe, block, expr, ob);
        generate_code(ob, expr->line_number, MVM_POP);
    }
}

static void
generate_if_statement(MVM_Executable *exe, Block *block,
                      Statement *statement, OpcodeBuf *ob)
{
    int if_false_label;
    int end_label;
    IfStatement *if_s = &statement->u.if_s;
    Elseif *elseif;

    generate_expression(exe, block, if_s->condition, ob);
    if_false_label = get_label(ob);
    generate_code(ob, statement->line_number,
        MVM_JUMP_IF_FALSE, if_false_label);
    generate_statement_list(exe, if_s->then_block,
        if_s->then_block->statement_list, ob);
    end_label = get_label(ob);
    generate_code(ob, statement->line_number, MVM_JUMP, end_label);
    set_label(ob, if_false_label);

    for (elseif = if_s->elseif_list; elseif; elseif = elseif->next) {
        generate_expression(exe, block, elseif->condition, ob);
        if_false_label = get_label(ob);
        generate_code(ob, statement->line_number,
            MVM_JUMP_IF_FALSE, if_false_label);
        generate_statement_list(exe, elseif->block,
            elseif->block->statement_list, ob);
        generate_code(ob, statement->line_number, MVM_JUMP, end_label);
        set_label(ob, if_false_label);
    }
    if (if_s->else_block) {
        generate_statement_list(exe, if_s->else_block,
            if_s->else_block->statement_list, ob);
    }
    set_label(ob, end_label);
}

static void
generate_while_statement(MVM_Executable *exe, Block *block,
                         Statement *statement, OpcodeBuf *ob)
{
    int loop_label;
    WhileStatement *while_s = &statement->u.while_s;

    loop_label = get_label(ob);
    set_label(ob, loop_label);

    generate_expression(exe, block, while_s->condition, ob);

    while_s->block->parent.statement.break_label = get_label(ob);
    while_s->block->parent.statement.continue_label = get_label(ob);

    generate_code(ob, statement->line_number,
                  MVM_JUMP_IF_FALSE,
                  while_s->block->parent.statement.break_label);
    generate_statement_list(exe, while_s->block,
                            while_s->block->statement_list, ob);

    set_label(ob, while_s->block->parent.statement.continue_label);
    generate_code(ob, statement->line_number, MVM_JUMP, loop_label);
    set_label(ob, while_s->block->parent.statement.break_label);
}

static void
generate_return_statement(MVM_Executable *exe, Block *block,
                          Statement *statement, OpcodeBuf *ob)
{
    generate_expression(exe, block, statement->u.return_s.return_value, ob);
    generate_code(ob, statement->line_number, MVM_RETURN);
}

static void
generate_statement_list(MVM_Executable *exe, Block *current_block,
                        StatementList *statement_list,
                        OpcodeBuf *ob)
{
    StatementList *pos;

    for (pos = statement_list; pos; pos = pos->next) {
        switch (pos->statement->type) {
        case EXPRESSION_STATEMENT:
            generate_expression_statement(exe, current_block,
                pos->statement->u.expression_s, ob);
            break;
        case IF_STATEMENT:
            generate_if_statement(exe, current_block, pos->statement, ob);
            break;
        case WHILE_STATEMENT:
            generate_while_statement(exe, current_block, pos->statement, ob);
            break;
        case FOR_STATEMENT:
            //generate_for_statement(exe, current_block, pos->statement, ob);
            break;
        case DO_WHILE_STATEMENT:
            //generate_do_while_statement(exe, current_block,
              //                          pos->statement, ob);
            break;
        case FOREACH_STATEMENT:
            break;
        case RETURN_STATEMENT:
            generate_return_statement(exe, current_block, pos->statement, ob);
            break;
        case BREAK_STATEMENT:
            //generate_break_statement(exe, current_block, pos->statement, ob);
            break;
        case CONTINUE_STATEMENT:
            //generate_continue_statement(exe, current_block,
            //                            pos->statement, ob);
            break;
        case DECLARATION_STATEMENT:
            generate_initializer(exe, current_block, pos->statement, ob);
            break;
        case STATEMENT_TYPE_COUNT_PLUS_1:
		    break;
        //default:
        //    DBG_assert(0, ("pos->statement->type..", pos->statement->type));
        }
    }
}

static void
copy_function(FunctionDefinition *src, MVM_Function *dest)
{
    dest->type = copy_type_specifier(src->type);
    dest->name = MEM_strdup(src->name);
    dest->parameter = copy_parameter_list(src->parameter,
                                          &dest->parameter_count);
    if (src->block) {
        dest->local_variable
            = copy_local_variables(src, dest->parameter_count);
        dest->local_variable_count
            = src->local_variable_count - dest->parameter_count;
    } else {
        dest->local_variable = NULL;
        dest->local_variable_count = 0;
    }
}

static void
add_functions(MINIC_Compiler *compiler, MVM_Executable *exe)
{
    FunctionDefinition  *fd;
    int                 i;
    int                 func_count = 0;
    OpcodeBuf           ob;

    for (fd = compiler->function_list; fd; fd = fd->next) {
        func_count++;
    }
    exe->function_count = func_count;
    exe->function = MEM_malloc(sizeof(MVM_Function) * func_count);
printf("a\n");
    for (fd = compiler->function_list, i = 0; fd; fd = fd->next, i++) {
printf("b\n");
        copy_function(fd, &exe->function[i]);
printf("c\n");
        if (fd->block) {
printf("d\n");
            init_opcode_buf(&ob);
printf("g\n");
            generate_statement_list(exe, fd->block, fd->block->statement_list,
                                    &ob);
printf("h\n");
            exe->function[i].is_implemented = MVM_TRUE;
            exe->function[i].code_size = ob.size;
            exe->function[i].code = fix_opcode_buf(&ob);
            exe->function[i].line_number_size = ob.line_number_size;
            exe->function[i].line_number = ob.line_number;
            exe->function[i].need_stack_size
                = calc_need_stack_size(exe->function[i].code,
                                       exe->function[i].code_size);
printf("i\n");
        } else {
printf("e\n");
            exe->function[i].is_implemented = MVM_FALSE;
        }
printf("f\n");
    }
}
									
static void
add_top_level(MINIC_Compiler *compiler, MVM_Executable *exe)
{
    OpcodeBuf           ob;

    init_opcode_buf(&ob);
	
    generate_statement_list(exe, NULL, compiler->statement_list,
                            &ob);
    
    exe->code_size = ob.size;
    exe->code = fix_opcode_buf(&ob);
    exe->line_number_size = ob.line_number_size;
    exe->line_number = ob.line_number;
    exe->need_stack_size = calc_need_stack_size(exe->code, exe->code_size);
}

MVM_Executable *
minic_generate(MINIC_Compiler *compiler)
{
    MVM_Executable      *exe;
    exe = alloc_executable();
printf("a\n");
    exe->function_count = compiler->mvm_function_count;
    exe->function = compiler->mvm_function;
    exe->class_count = compiler->mvm_class_count;
    exe->class_definition = compiler->mvm_class;
printf("b\n");
    add_global_variable(compiler, exe);
printf("c\n");
    add_classes(compiler, exe);
printf("d\n");
    add_functions(compiler, exe);
printf("e\n");
    add_top_level(compiler, exe);
printf("f\n");	
    return exe;
}