#include <stdio.h>
#include <string.h>
#include "share.h"

extern OpcodeInfo mvm_opcode_info[];

static void
dump_constant_pool(int constant_pool_count, MVM_ConstantPool *constant_pool)
{
    int i;

    printf("** constant pool section ***********************************\n");
    for (i = 0; i < constant_pool_count; i++) {
        printf("%05d:", i);
        switch (constant_pool[i].tag) {
        case MVM_CONSTANT_INT:
            printf("int %d\n", constant_pool[i].u.c_integer);
            break;
        case MVM_CONSTANT_DOUBLE:
            printf("double %f\n", constant_pool[i].u.c_decimal);
            break;
        case MVM_CONSTANT_STRING:
            printf("string %s\n", constant_pool[i].u.c_string);
            break;
        }
    }
}

static void dump_type(MVM_Executable *exe, MVM_TypeSpecifier *type);

static void
dump_parameter_list(MVM_Executable *exe,
                    int parameter_count, MVM_LocalVariable *parameter_list)
{
    int i;

    printf("(");
    for (i = 0; i < parameter_count; i++) {
        dump_type(exe, parameter_list[i].type);
        printf(" %s", parameter_list[i].name);
        if (i < parameter_count-1) {
            printf(", ");
        }
    }
    printf(")");
}

static void
dump_type(MVM_Executable *exe, MVM_TypeSpecifier *type)
{
    int i;

    switch (type->basic_type) {
    case MVM_VOID_TYPE:
        printf("void ");
        break;
    case MVM_BOOLEAN_TYPE:
        printf("boolean ");
        break;
    case MVM_INTEGER_TYPE:
        printf("int ");
        break;
    case MVM_DECIMAL_TYPE:
        printf("double ");
        break;
    case MVM_STRING_TYPE:
        printf("string ");
        break;
    case MVM_CLASS_TYPE:
        printf("<%s> ", exe->class_definition[type->class_index].name);
        break;
    case MVM_NULL_TYPE:
        printf("null ");
        break;
    case MVM_BASE_TYPE:
        break;
    }

    for (i = 0; i < type->derive_count; i++) {
        switch (type->derive[i].tag) {
        case MVM_FUNCTION_DERIVE:
            dump_parameter_list(exe,
                                type->derive[i].u.function_d.parameter_count,
                                type->derive[i].u.function_d.parameter);
            break;
        case MVM_ARRAY_DERIVE:
            printf("[]");
            break;
        }
    }
}

static void
dump_variable(MVM_Executable *exe, int global_variable_count,
              MVM_Variable *global_variable)
{
    int i;

    printf("** global variable section *********************************\n");
    for (i = 0; i < global_variable_count; i++) {
        printf("%5d:", i);
        dump_type(exe, global_variable[i].type);
        printf(" %s\n", global_variable[i].name);
    }
}

int
mvm_dump_instruction(FILE *fp, MVM_Byte *code, int index)
{
    OpcodeInfo *info;
    int value;
    int i;

    info = &mvm_opcode_info[code[index]];
    fprintf(fp, "%4d %s ", index, info->mnemonic);
    for (i = 0; info->parameter[i] != '\0'; i++) {
        switch (info->parameter[i]) {
        case 'b':
            value = code[index+1];
            fprintf(fp, " %d", value);
            index++;
            break;
        case 's': /* FALLTHRU */
        case 'p':
            value = (code[index+1] << 8) + code[index+2];
            fprintf(fp, " %d", value);
            index += 2;
            break;
        }
    }
    index++;

    return index;
}

static void
dump_opcode(int code_size, MVM_Byte *code)
{
    int index;

    for (index = 0; index < code_size; ) {
        index = mvm_dump_instruction(stdout, code, index);
        printf("\n");
    }
}

static void
dump_line_number(int line_number_size, MVM_LineNumber *line_number)
{
    int i;

    printf("*** line number ***\n");
    for (i = 0; i < line_number_size; i++) {
        printf("%5d: from %5d size %5d\n",
               line_number[i].line_number,
               line_number[i].start_pc,
               line_number[i].pc_count);
    }
}

static void
dump_function(MVM_Executable *exe, int function_count, MVM_Function *function)
{
    int i;

    printf("** function section ****************************************\n");
    for (i = 0; i < function_count; i++) {
        printf("*** [%d] %s ***\n", i, function[i].name);

        dump_type(exe, function[i].type);
        printf(" %s ", function[i].name);
        dump_parameter_list(exe,
                            function[i].parameter_count,
                            function[i].parameter);
        printf("\n");
        if (function[i].is_implemented) {
            if (function[i].code_size > 0) {
                dump_opcode(function[i].code_size, function[i].code);
                dump_line_number(function[i].line_number_size,
                                 function[i].line_number);
            }
        }
        printf("*** end of %s ***\n", function[i].name);
    }
}

static void
dump_types(MVM_Executable *exe, int type_count, MVM_TypeSpecifier *types)
{
    int i;

    printf("** type section ********************************************\n");
    for (i = 0; i < type_count; i++) {
        printf("%5d:", i);
        dump_type(exe, &types[i]);
        printf("\n");
    }
}

void
mvm_disassemble(MVM_Executable *exe)
{
    dump_constant_pool(exe->constant_pool_count, exe->constant_pool);
    dump_variable(exe, exe->global_variable_count, exe->global_variable);
    dump_function(exe, exe->function_count, exe->function);
    dump_types(exe, exe->type_specifier_count, exe->type_specifier);
    printf("** toplevel ********************\n");
    dump_opcode(exe->code_size, exe->code);
    dump_line_number(exe->line_number_size, exe->line_number);
}
