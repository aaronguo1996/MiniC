#include <math.h>
#include <string.h>
#include "MEM.h"
#include "mvm_pri.h"

extern OpcodeInfo mvm_opcode_info[];

MVM_VirtualMachine *
MVM_create_virtual_machine(void)
{
    MVM_VirtualMachine *mvm;

    mvm = MEM_malloc(sizeof(MVM_VirtualMachine));
    mvm->stack.alloc_size = STACK_ALLOC_SIZE;
    mvm->stack.stack = MEM_malloc(sizeof(MVM_Value) * STACK_ALLOC_SIZE);
    mvm->stack.pointer_flags
        = MEM_malloc(sizeof(MVM_Boolean) * STACK_ALLOC_SIZE);
    mvm->stack.stack_pointer = 0;
    mvm->heap.current_heap_size = 0;
    mvm->heap.header = NULL;
    mvm->heap.current_threshold = HEAP_THRESHOLD_SIZE;
    mvm->current_executable = NULL;
    mvm->function = NULL;
    mvm->function_count = 0;
    mvm->executable = NULL;

    mvm_add_native_functions(mvm);

    return mvm;
}

void
MVM_add_native_function(MVM_VirtualMachine *mvm, char *func_name,
                        MVM_NativeFunctionProc *proc, int arg_count)
{
    mvm->function = MEM_realloc(mvm->function,
        sizeof(Function) * (mvm->function_count + 1));

    mvm->function[mvm->function_count].name = MEM_strdup(func_name);
    mvm->function[mvm->function_count].kind = NATIVE_FUNCTION;
    mvm->function[mvm->function_count].u.native_f.proc = proc;
    mvm->function[mvm->function_count].u.native_f.arg_count = arg_count;
    mvm->function_count++;
}

static void
add_functions(MVM_VirtualMachine *mvm, MVM_Executable *executable)
{
    int src_idx;
    int dest_idx;
    int func_count = 0;

    for (src_idx = 0; src_idx < executable->function_count; src_idx++) {
        if (executable->function[src_idx].is_implemented) {
            func_count++;
            for (dest_idx = 0; dest_idx < mvm->function_count; dest_idx++) {
                if (!strcmp(mvm->function[dest_idx].name,
                    executable->function[src_idx].name)) {
						/*
                    mvm_error(NULL, NULL, NO_LINE_NUMBER_PC,
                              FUNCTION_MULTIPLE_DEFINE_ERR,
                              STRING_MESSAGE_ARGUMENT, "name",
                              mvm->function[dest_idx].name,
                              MESSAGE_ARGUMENT_END); */
                }
            }
        }
    }
    mvm->function = MEM_realloc(mvm->function,
        sizeof(Function) * (mvm->function_count + func_count));

    for (src_idx = 0, dest_idx = mvm->function_count;
         src_idx < executable->function_count; src_idx++) {
        if (!executable->function[src_idx].is_implemented)
            continue;
        mvm->function[dest_idx].name
            = MEM_strdup(executable->function[src_idx].name);
        mvm->function[dest_idx].u.minic_f.executable
            = executable;
        mvm->function[dest_idx].u.minic_f.index = src_idx;
        dest_idx++;
    }
    mvm->function_count += func_count;
}

static int
search_function(MVM_VirtualMachine *mvm, char *name)
{
    int i;

    for (i = 0; i < mvm->function_count; i++) {
        if (!strcmp(mvm->function[i].name, name)) {
            return i;
        }
    }
	/*
    mvm_error(NULL, NULL, NO_LINE_NUMBER_PC, FUNCTION_NOT_FOUND_ERR,
              STRING_MESSAGE_ARGUMENT, "name", name,
              MESSAGE_ARGUMENT_END);*/
    return 0;
}

static void
convert_code(MVM_VirtualMachine *mvm, MVM_Executable *exe,
             MVM_Byte *code, int code_size, MVM_Function *func)
{
    int i;
    int j;
    OpcodeInfo *info;
    int src_idx;
    unsigned int dest_idx;

    for (i = 0; i < code_size; i++) {
        if (code[i] == MVM_PUSH_STACK_INT
            || code[i] == MVM_PUSH_STACK_DOUBLE
            || code[i] == MVM_PUSH_STACK_OBJECT
            || code[i] == MVM_POP_STACK_INT
            || code[i] == MVM_POP_STACK_DOUBLE
            || code[i] == MVM_POP_STACK_OBJECT) {

            src_idx = GET_2BYTE_INT(&code[i+1]);
            if (src_idx >= func->parameter_count) {
                dest_idx = src_idx + CALL_INFO_ALIGN_SIZE;
            } else {
                dest_idx = src_idx;
            }
            SET_2BYTE_INT(&code[i+1], dest_idx);

        } else if (code[i] == MVM_PUSH_FUNCTION) {
            int idx_in_exe;
            unsigned int func_idx;
            idx_in_exe = GET_2BYTE_INT(&code[i+1]);
            func_idx = search_function(mvm, exe->function[idx_in_exe].name);
            SET_2BYTE_INT(&code[i+1], func_idx);
        }
        info = &mvm_opcode_info[code[i]];
        for (j = 0; info->parameter[j] != '\0'; j++) {
            switch (info->parameter[j]) {
            case 'b':
                i++;
                break;
            case 's':
            case 'p':
                i += 2;
                break;
            }
        }
    }
}

static void
initialize_value(MVM_VirtualMachine *mvm,
                 MVM_TypeSpecifier *type, MVM_Value *value)
{
    if (type->derive_count > 0) {
        if (type->derive[0].tag == MVM_ARRAY_DERIVE) {
            value->object = NULL;
        }
    } else {
        switch (type->basic_type) {
        case MVM_BOOLEAN_TYPE:
        case MVM_INTEGER_TYPE:
            value->int_value = 0;
            break;
        case MVM_DECIMAL_TYPE:
            value->double_value = 0.0;
            break;
        case MVM_STRING_TYPE:
            value->object = NULL;
            break;
        case MVM_NULL_TYPE:
		case MVM_VOID_TYPE:
		case MVM_CLASS_TYPE:
		case MVM_BASE_TYPE:
		    break;
        }
    }
}
	
static void
add_static_variables(MVM_VirtualMachine *mvm, MVM_Executable *exe)
{
    int i;
    MVM_Class *pos = exe->class_definition;

    mvm->static_v.variable = MEM_malloc(sizeof(MVM_Value) * exe->global_variable_count);
    mvm->static_v.variable_count = exe->global_variable_count;

    for (i = 0; i < exe->global_variable_count; i++) {
        if (exe->global_variable[i].type->basic_type == MVM_STRING_TYPE) {
            mvm->static_v.variable[i].object = NULL;
        }else if(exe->global_variable[i].type->basic_type == MVM_CLASS_TYPE){
            mvm->static_v.variable[i].object = malloc(sizeof(MVM_Object));
            mvm->static_v.variable[i].object->type = CLASS_OBJECT;
            mvm->static_v.variable[i].object->u.class_object.field_count 
            = exe->class_definition->field_count;
            mvm->static_v.variable[i].object->u.class_object.field 
            = malloc(sizeof(MVM_Value)*exe->class_definition->field_count);
        }
    }
    for (i = 0; i < exe->global_variable_count; i++) {
        initialize_value(mvm, exe->global_variable[i].type,
            &mvm->static_v.variable[i]);
    }
}

void
MVM_add_executable(MVM_VirtualMachine *mvm, MVM_Executable *executable)
{
    int i;

    mvm->executable = executable;
    add_functions(mvm, executable);
    convert_code(mvm, executable, executable->code, 
	    executable->code_size, NULL);
    for (i = 0; i < executable->function_count; i++) {
        convert_code(mvm, executable, executable->function[i].code,
            executable->function[i].code_size, &executable->function[i]);
    }
    add_static_variables(mvm, executable);
}

//==================================================================//
// Execute part

static MVM_Object *
chain_string(MVM_VirtualMachine *mvm, MVM_Object *str1, MVM_Object *str2)
{
    int result_len;
    MVM_Char    *left;
    MVM_Char    *right;
    MVM_Char    *result;
    MVM_Object  *ret;

    if (str1 == NULL) {
        left = NULL_STRING;
    } else {
        left = str1->u.string.string;
    }
    if (str2 == NULL) {
        right = NULL_STRING;
    } else {
        right = str2->u.string.string;
    }
    result_len = strlen(left) +strlen(right);
    result = MEM_malloc(sizeof(MVM_Char) * (result_len + 1));

    strcpy(result, left);
    strcat(result, right);

	ret = mvm_create_mvm_string_i(mvm, result);
	
    return ret;
}

static void
invoke_native_function(MVM_VirtualMachine *mvm, Function *func,
                       int *sp_p)
{
    MVM_Value   *stack;
    int         sp;
    MVM_Value   ret;

    stack = mvm->stack.stack;
    sp = *sp_p;

    ret = func->u.native_f.proc(mvm, func->u.native_f.arg_count,
        &stack[sp-func->u.native_f.arg_count-1]);

    stack[sp-func->u.native_f.arg_count-1] = ret;

    *sp_p = sp - (func->u.native_f.arg_count);
}

static void
initialize_local_variables(MVM_VirtualMachine *mvm,
                           MVM_Function *func, int from_sp)
{
    int i;
    int sp_idx;

    for (i = 0, sp_idx = from_sp; i < func->local_variable_count;
         i++, sp_idx++) {
        mvm->stack.pointer_flags[i] = MVM_FALSE;
    }

    for (i = 0, sp_idx = from_sp; i < func->local_variable_count;
         i++, sp_idx++) {
        initialize_value(mvm, func->local_variable[i].type,
            &mvm->stack.stack[sp_idx]);
        if (func->local_variable[i].type->basic_type == MVM_STRING_TYPE) {
            mvm->stack.pointer_flags[i] = MVM_TRUE;
        }
    }
}

static void
expand_stack(MVM_VirtualMachine *mvm, int need_stack_size)
{
    int revalue_up;
    int rest;

    rest = mvm->stack.alloc_size - mvm->stack.stack_pointer;
    if (rest <= need_stack_size) {
        revalue_up = ((rest / STACK_ALLOC_SIZE) + 1) * STACK_ALLOC_SIZE;

        mvm->stack.alloc_size += revalue_up;
        mvm->stack.stack = MEM_realloc(mvm->stack.stack,
            mvm->stack.alloc_size * sizeof(MVM_Value));
        mvm->stack.pointer_flags = MEM_realloc(mvm->stack.pointer_flags,
            mvm->stack.alloc_size * sizeof(MVM_Boolean));
    }
}

static void
invoke_minic_function(MVM_VirtualMachine *mvm,
                       Function **caller_p, Function *callee,
                       MVM_Byte **code_p, int *code_size_p, int *pc_p,
                       int *sp_p, int *base_p, MVM_Executable **exe_p)
{
    CallInfo *callInfo;
    MVM_Function *callee_p;
    int i;

    *exe_p = callee->u.minic_f.executable;
    callee_p = &(*exe_p)->function[callee->u.minic_f.index];

    expand_stack(mvm, CALL_INFO_ALIGN_SIZE
        + callee_p->local_variable_count
        + (*exe_p)->function[callee->u.minic_f.index].need_stack_size);

    callInfo = (CallInfo*)&mvm->stack.stack[*sp_p-1];
    callInfo->caller = *caller_p;
    callInfo->caller_address = *pc_p;
    callInfo->base = *base_p;
    for (i = 0; i < CALL_INFO_ALIGN_SIZE; i++) {
        mvm->stack.pointer_flags[*sp_p-1+i] = MVM_FALSE;
    }

    *base_p = *sp_p - callee_p->parameter_count - 1;
    *caller_p = callee;

    initialize_local_variables(mvm, callee_p,
        *sp_p + CALL_INFO_ALIGN_SIZE - 1);

    *sp_p += CALL_INFO_ALIGN_SIZE + callee_p->local_variable_count - 1;
    *pc_p = 0;

    *code_p = (*exe_p)->function[callee->u.minic_f.index].code;
    *code_size_p = (*exe_p)->function[callee->u.minic_f.index].code_size;

}

static void
return_function(MVM_VirtualMachine *mvm, Function **func_p,
                MVM_Byte **code_p, int *code_size_p, int *pc_p,
                int *sp_p, int *base_p, MVM_Executable **exe_p)
{
    MVM_Value return_value;
    CallInfo *callInfo;
    MVM_Function *caller_p;
    MVM_Function *callee_p;

    return_value = mvm->stack.stack[(*sp_p)-1];

    callee_p = &(*exe_p)->function[(*func_p)->u.minic_f.index];
    callInfo = (CallInfo*)&mvm->stack.stack[*sp_p - 1
        - callee_p->local_variable_count - CALL_INFO_ALIGN_SIZE];

    if (callInfo->caller) {
        *exe_p = callInfo->caller->u.minic_f.executable;
        caller_p = &(*exe_p)->function[callInfo->caller->u.minic_f.index];
        *code_p = caller_p->code;
        *code_size_p = caller_p->code_size;
    } else {
        *exe_p = mvm->executable;
        *code_p = mvm->executable->code;
        *code_size_p = mvm->executable->code_size;
    }
    *func_p = callInfo->caller;

    *pc_p = callInfo->caller_address + 1;
    *base_p = callInfo->base;

    *sp_p -= callee_p->local_variable_count + CALL_INFO_ALIGN_SIZE
        + callee_p->parameter_count;

    mvm->stack.stack[*sp_p-1] = return_value;
}

#define STI(mvm, sp) \
  ((mvm)->stack.stack[(mvm)->stack.stack_pointer+(sp)].int_value)
#define STD(mvm, sp) \
  ((mvm)->stack.stack[(mvm)->stack.stack_pointer+(sp)].double_value)
#define STO(mvm, sp) \
  ((mvm)->stack.stack[(mvm)->stack.stack_pointer+(sp)].object)

#define STI_I(mvm, sp) \
  ((mvm)->stack.stack[(sp)].int_value)
#define STD_I(mvm, sp) \
  ((mvm)->stack.stack[(sp)].double_value)
#define STO_I(mvm, sp) \
  ((mvm)->stack.stack[(sp)].object)

#define STI_WRITE(mvm, sp, r) \
  ((mvm)->stack.stack[(mvm)->stack.stack_pointer+(sp)].int_value = r,\
   (mvm)->stack.pointer_flags[(mvm)->stack.stack_pointer+(sp)] = MVM_FALSE)
#define STD_WRITE(mvm, sp, r) \
  ((mvm)->stack.stack[(mvm)->stack.stack_pointer+(sp)].double_value = r, \
   (mvm)->stack.pointer_flags[(mvm)->stack.stack_pointer+(sp)] = MVM_FALSE)
#define STO_WRITE(mvm, sp, r) \
  ((mvm)->stack.stack[(mvm)->stack.stack_pointer+(sp)].object = r, \
   (mvm)->stack.pointer_flags[(mvm)->stack.stack_pointer+(sp)] = MVM_TRUE)

#define STI_WRITE_I(mvm, sp, r) \
  ((mvm)->stack.stack[(sp)].int_value = r,\
   (mvm)->stack.pointer_flags[(sp)] = MVM_FALSE)
#define STD_WRITE_I(mvm, sp, r) \
  ((mvm)->stack.stack[(sp)].double_value = r, \
   (mvm)->stack.pointer_flags[(sp)] = MVM_FALSE)
#define STO_WRITE_I(mvm, sp, r) \
  ((mvm)->stack.stack[(sp)].object = r, \
   (mvm)->stack.pointer_flags[(sp)] = MVM_TRUE)

MVM_Object *
create_array_sub(MVM_VirtualMachine *mvm, int dim, int dim_index,
                 MVM_TypeSpecifier *type)
{
    MVM_Object *ret;
    int size;
    int i;

    size = STI(mvm, -dim);

    if (dim_index == type->derive_count-1) {
        switch (type->basic_type) {
        case MVM_BOOLEAN_TYPE:
        case MVM_INTEGER_TYPE:
            ret = MVM_create_array_int(mvm, size);
            break;
        case MVM_DECIMAL_TYPE:
            ret = MVM_create_array_double(mvm, size);
            break;
        case MVM_STRING_TYPE:
            ret = MVM_create_array_object(mvm, size);
            break;
        case MVM_NULL_TYPE:
		case MVM_BASE_TYPE:
		case MVM_CLASS_TYPE:
		case MVM_VOID_TYPE:
        default:
            break;
        }
    } else if (type->derive[dim_index].tag == MVM_FUNCTION_DERIVE) {
        /* BUGBUG */
        ret = NULL;
    } else {
        ret = MVM_create_array_object(mvm, size);
        if (dim_index < dim - 1) {
            STO_WRITE(mvm, 0, ret);
            mvm->stack.stack_pointer++;
            for (i = 0; i < size; i++) {
                MVM_Object *child;
                child = create_array_sub(mvm, dim, dim_index+1, type);
                MVM_array_set_object(mvm, ret, i, child);
            }
            mvm->stack.stack_pointer--;
        }
    }
    return ret;
}

MVM_Object *
create_array(MVM_VirtualMachine *mvm, int dim, MVM_TypeSpecifier *type)
{
    return create_array_sub(mvm, dim, 0, type);
}

MVM_Object *
create_array_literal_int(MVM_VirtualMachine *mvm, int size)
{
    MVM_Object *array;
    int i;

    array = mvm_create_array_int_i(mvm, size);
    for (i = 0; i < size; i++) {
        array->u.array.u.int_array[i] = STI(mvm, -size+i);
    }

    return array;
}

MVM_Object *
create_array_literal_double(MVM_VirtualMachine *mvm, int size)
{
    MVM_Object *array;
    int i;

    array = mvm_create_array_double_i(mvm, size);
    for (i = 0; i < size; i++) {
        array->u.array.u.double_array[i] = STD(mvm, -size+i);
    }

    return array;
}

MVM_Object *
create_array_literal_object(MVM_VirtualMachine *mvm, int size)
{
    MVM_Object *array;
    int i;

    array = mvm_create_array_object_i(mvm, size);
    for (i = 0; i < size; i++) {
        array->u.array.u.object[i] = STO(mvm, -size+i);
    }

    return array;
}

static void
restore_pc(MVM_VirtualMachine *mvm, MVM_Executable *exe,
           Function *func, int pc)
{
    mvm->current_executable = exe;
    mvm->current_function = func;
    mvm->pc = pc;
}

static void
check_null_pointer_func(MVM_Executable *exe, Function *func, int pc,
                        MVM_Object *obj)
{
    if (obj == NULL) {
        printf("FROM CHECK_NULL_POINTER_FUNC\n NULL_POINTER_ERR!\n");
    }
}

static
char* str_alloc(char* src)
{
	int len = strlen(src) + 1;
	char* ret = MEM_malloc(sizeof(char) * (len+1));
	strcpy(ret, src);
	return ret;
}

static MVM_Value
execute(MVM_VirtualMachine *mvm, Function *func,
        MVM_Byte *code, int code_size)
{
    int         base;
    MVM_Executable *exe;
    int         pc;
    MVM_Value   ret;

    pc = mvm->pc;
    exe = mvm->current_executable;

    while (pc < code_size) {
        /*printf("%s  sp(%d)\t\n",
                mvm_opcode_info[code[pc]].mnemonic,
                                mvm->stack.stack_pointer);*/
        

        switch (code[pc]) {
        case MVM_PUSH_INT_1BYTE:
            STI_WRITE(mvm, 0, code[pc+1]);
            //printf("int byte %d\n",code[pc+1]);
            mvm->stack.stack_pointer++;
            pc += 2;
            break;
        case MVM_PUSH_INT_2BYTE:
            STI_WRITE(mvm, 0, GET_2BYTE_INT(&code[pc+1]));
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        case MVM_PUSH_INT:
            STI_WRITE(mvm, 0,
                exe->constant_pool[GET_2BYTE_INT(&code[pc+1])].u.c_integer);
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        case MVM_PUSH_DOUBLE_0:
            STD_WRITE(mvm, 0, 0.0);
            mvm->stack.stack_pointer++;
            pc++;
            break;
        case MVM_PUSH_DOUBLE_1:
            STD_WRITE(mvm, 0, 1.0);
            mvm->stack.stack_pointer++;
            pc++;
            break;
        case MVM_PUSH_DOUBLE:
            STD_WRITE(mvm, 0, 
                exe->constant_pool[GET_2BYTE_INT(&code[pc+1])].u.c_decimal);
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        case MVM_PUSH_STRING:
            STO_WRITE(mvm, 0,
                      mvm_literal_to_mvm_string_i(mvm,
                                                  exe->constant_pool
                                                  [GET_2BYTE_INT(&code
                                                                 [pc+1])]
                                                  .u.c_string));
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        case MVM_PUSH_NULL:
            STO_WRITE(mvm, 0, NULL);
            mvm->stack.stack_pointer++;
            pc++;
            break;
        case MVM_PUSH_STACK_INT:
            STI_WRITE(mvm, 0,
                      STI_I(mvm, base + GET_2BYTE_INT(&code[pc+1])));
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        case MVM_PUSH_STACK_DOUBLE:
            STD_WRITE(mvm, 0,
                      STD_I(mvm, base + GET_2BYTE_INT(&code[pc+1])));
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        case MVM_PUSH_STACK_OBJECT:
            STO_WRITE(mvm, 0,
                      STO_I(mvm, base + GET_2BYTE_INT(&code[pc+1])));
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        case MVM_POP_STACK_INT:
            STI_WRITE_I(mvm, base + GET_2BYTE_INT(&code[pc+1]),
                        STI(mvm, -1));
            mvm->stack.stack_pointer--;
            pc += 3;
            break;
        case MVM_POP_STACK_DOUBLE:
            STD_WRITE_I(mvm, base + GET_2BYTE_INT(&code[pc+1]),
                        STD(mvm, -1));
            mvm->stack.stack_pointer--;
            pc += 3;
            break;
        case MVM_POP_STACK_OBJECT:
            STO_WRITE_I(mvm, base + GET_2BYTE_INT(&code[pc+1]),
                        STO(mvm, -1));
            mvm->stack.stack_pointer--;
            pc += 3;
            break;
        case MVM_PUSH_STATIC_INT:
            STI_WRITE(mvm, 0,
                      mvm->static_v.variable[GET_2BYTE_INT(&code[pc+1])]
                      .int_value);
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        case MVM_PUSH_STATIC_DOUBLE:
            STD_WRITE(mvm, 0,
                      mvm->static_v.variable[GET_2BYTE_INT(&code[pc+1])]
                      .double_value);
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        case MVM_PUSH_STATIC_OBJECT:
            STO_WRITE(mvm, 0,mvm->static_v.variable[GET_2BYTE_INT(&code[pc+1])].object);
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        case MVM_POP_STATIC_INT:
            mvm->static_v.variable[GET_2BYTE_INT(&code[pc+1])].int_value
                = STI(mvm, -1);
            mvm->stack.stack_pointer--;
            pc += 3;
            break;
        case MVM_POP_STATIC_DOUBLE:
            mvm->static_v.variable[GET_2BYTE_INT(&code[pc+1])]
                .double_value
                = STD(mvm, -1);
            mvm->stack.stack_pointer--;
            pc += 3;
            break;
        case MVM_POP_STATIC_OBJECT:
            mvm->static_v.variable[GET_2BYTE_INT(&code[pc+1])].object
                = STO(mvm, -1);
            mvm->stack.stack_pointer--;
            pc += 3;
            break;
        case MVM_PUSH_ARRAY_INT:
        {
            MVM_Object *array = STO(mvm, -2);
            int index = STI(mvm, -1);
            int int_value;

            restore_pc(mvm, exe, func, pc);
            int_value = MVM_array_get_int(mvm, array, index);

            STI_WRITE(mvm, -2, int_value);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        }
        case MVM_PUSH_ARRAY_DOUBLE:
        {
            MVM_Object *array = STO(mvm, -2);
            int index = STI(mvm, -1);
            double double_value;

            restore_pc(mvm, exe, func, pc);
            double_value = MVM_array_get_double(mvm, array, index);

            STD_WRITE(mvm, -2, double_value);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        }
        case MVM_PUSH_ARRAY_OBJECT:
        {
            MVM_Object *array = STO(mvm, -2);
            int index = STI(mvm, -1);
            MVM_Object *object;

            restore_pc(mvm, exe, func, pc);
            object = MVM_array_get_object(mvm, array, index);

            STO_WRITE(mvm, -2, object);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        }
        case MVM_POP_ARRAY_INT:
        {
            int value = STI(mvm, -3);
            MVM_Object *array = STO(mvm, -2);
            int index = STI(mvm, -1);

            restore_pc(mvm, exe, func, pc);
            MVM_array_set_int(mvm, array, index, value);
            mvm->stack.stack_pointer -= 3;
            pc++;
            break;
        }
        case MVM_POP_ARRAY_DOUBLE:
        {
            double value = STD(mvm, -3);
            MVM_Object *array = STO(mvm, -2);
            int index = STI(mvm, -1);

            restore_pc(mvm, exe, func, pc);
            MVM_array_set_double(mvm, array, index, value);
            mvm->stack.stack_pointer -= 3;
            pc++;
            break;
        }
        case MVM_POP_ARRAY_OBJECT:
        {
            MVM_Object *value = STO(mvm, -3);
            MVM_Object *array = STO(mvm, -2);
            int index = STI(mvm, -1);

            restore_pc(mvm, exe, func, pc);
            MVM_array_set_object(mvm, array, index, value);
            mvm->stack.stack_pointer -= 3;
            pc++;
            break;
        }
        case MVM_PUSH_FIELD_INT:
        {
            MVM_Object *obj = STO(mvm, -1);
            int index = GET_2BYTE_INT(&code[pc+1]);

            //check_null_pointer(exe, func, pc, obj);
            STI_WRITE(mvm, -1,
                      obj->u.class_object.field[index].int_value);
            pc += 3;
            break;
        }
        case MVM_PUSH_FIELD_DOUBLE:
        {
            MVM_Object *obj = STO(mvm, -1);
            int index = GET_2BYTE_INT(&code[pc+1]);

            //check_null_pointer(exe, func, pc, obj);
            STD_WRITE(mvm, -1,
                      obj->u.class_object.field[index].double_value);
            pc += 3;
            break;
        }
        case MVM_PUSH_FIELD_OBJECT:
        {
            MVM_Object *obj = STO(mvm, -1);
            int index = GET_2BYTE_INT(&code[pc+1]);

            //check_null_pointer(exe, func, pc, obj);
            STO_WRITE(mvm, -1, obj->u.class_object.field[index].object);
            pc += 3;
            break;
        }
        case MVM_POP_FIELD_INT:
        {
            MVM_Object *obj = STO(mvm, -1);
            int index = GET_2BYTE_INT(&code[pc+1]);
            obj->u.class_object.field[index].int_value = STI(mvm, -2);
            mvm->stack.stack_pointer -= 2;
            pc += 3;
            break;
        }
        case MVM_POP_FIELD_DOUBLE:
        {
            MVM_Object *obj = STO(mvm, -1);
            int index = GET_2BYTE_INT(&code[pc+1]);
            obj->u.class_object.field[index].double_value = STD(mvm, -2);
            mvm->stack.stack_pointer -= 2;
            pc += 3;
            break;
        }
        case MVM_POP_FIELD_OBJECT:
        {
            MVM_Object *obj = STO(mvm, -1);
            int index = GET_2BYTE_INT(&code[pc+1]);

            //check_null_pointer(exe, func, pc, obj);
            obj->u.class_object.field[index].object = STO(mvm, -2);
            mvm->stack.stack_pointer -= 2;
            pc += 3;
            break;
        }
        case MVM_ADD_INT:
            STI(mvm, -2) = STI(mvm, -2) + STI(mvm, -1);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_ADD_DOUBLE:
            STD(mvm, -2) = STD(mvm, -2) + STD(mvm, -1);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_ADD_STRING:
            STO(mvm, -2) = chain_string(mvm,
                                        STO(mvm, -2),
                                        STO(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_SUB_INT:
            STI(mvm, -2) = STI(mvm, -2) - STI(mvm, -1);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_SUB_DOUBLE:
            STD(mvm, -2) = STD(mvm, -2) - STD(mvm, -1);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_MUL_INT:
            STI(mvm, -2) = STI(mvm, -2) * STI(mvm, -1);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_MUL_DOUBLE:
            STD(mvm, -2) = STD(mvm, -2) * STD(mvm, -1);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_DIV_INT:
            if (STI(mvm, -1) == 0) {
                //mvm_error(exe, func, pc, DIVISION_BY_ZERO_ERR,
                //          MESSAGE_ARGUMENT_END);
            }
            STI(mvm, -2) = STI(mvm, -2) / STI(mvm, -1);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_DIV_DOUBLE:
            STD(mvm, -2) = STD(mvm, -2) / STD(mvm, -1);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_MOD_INT:
            STI(mvm, -2) = STI(mvm, -2) % STI(mvm, -1);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_MOD_DOUBLE:
            STD(mvm, -2) = fmod(STD(mvm, -2), STD(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_MINUS_INT:
            STI(mvm, -1) = -STI(mvm, -1);
            pc++;
            break;
        case MVM_MINUS_DOUBLE:
            STD(mvm, -1) = -STD(mvm, -1);
            pc++;
            break;
        case MVM_INCREMENT:
            STI(mvm, -1)++;
            pc++;
            break;
        case MVM_DECREMENT:
            STI(mvm, -1)--;
            pc++;
            break;
        case MVM_CAST_INT_TO_DOUBLE:
            STD(mvm, -1) = (double)STI(mvm, -1);
            pc++;
            break;
        case MVM_CAST_DOUBLE_TO_INT:
            STI(mvm, -1) = (int)STD(mvm, -1);
            pc++;
            break;
        case MVM_CAST_BOOLEAN_TO_STRING:
            if (STI(mvm, -1)) {
                STO_WRITE(mvm, -1,
                          mvm_literal_to_mvm_string_i(mvm, TRUE_STRING));
            } else {
                STO_WRITE(mvm, -1,
                          mvm_literal_to_mvm_string_i(mvm, FALSE_STRING));
            }
            pc++;
            break;
        case MVM_CAST_INT_TO_STRING:
        {
            char buf[LINE_BUF_SIZE];
            MVM_Char *str;

            sprintf(buf, "%d", STI(mvm, -1));
            restore_pc(mvm, exe, func, pc);
            str = str_alloc(buf);
            STO_WRITE(mvm, -1,
                mvm_create_mvm_string_i(mvm, str));
            pc++;
            break;
        }
        case MVM_CAST_DOUBLE_TO_STRING:
        {
            char buf[LINE_BUF_SIZE];
            MVM_Char *str;

            sprintf(buf, "%f", STD(mvm, -1));
            restore_pc(mvm, exe, func, pc);
            str = str_alloc(buf);
            STO_WRITE(mvm, -1,
                mvm_create_mvm_string_i(mvm, str));
            pc++;
            break;
        }
        case MVM_EQ_INT:
            STI(mvm, -2) = (STI(mvm, -2) == STI(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_EQ_DOUBLE:
            STI(mvm, -2) = (STD(mvm, -2) == STD(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_EQ_OBJECT:
            STI_WRITE(mvm, -2, STO(mvm, -2) == STO(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_EQ_STRING:
            STI_WRITE(mvm, -2,
                !strcmp(STO(mvm, -2)->u.string.string, STO(mvm, -1)->u.string.string));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_GT_INT:
            STI(mvm, -2) = (STI(mvm, -2) > STI(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_GT_DOUBLE:
            STI(mvm, -2) = (STD(mvm, -2) > STD(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_GT_STRING:
            STI_WRITE(mvm, -2,
                strcmp(STO(mvm, -2)->u.string.string,
                STO(mvm, -1)->u.string.string) > 0);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_GE_INT:
            STI(mvm, -2) = (STI(mvm, -2) >= STI(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_GE_DOUBLE:
            STI(mvm, -2) = (STD(mvm, -2) >= STD(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_GE_STRING:
            STI_WRITE(mvm, -2,
                strcmp(STO(mvm, -2)->u.string.string,
                STO(mvm, -1)->u.string.string) >= 0);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_LT_INT:
            STI(mvm, -2) = (STI(mvm, -2) < STI(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_LT_DOUBLE:
            STI(mvm, -2) = (STD(mvm, -2) < STD(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_LT_STRING:
            STI_WRITE(mvm, -2,
                      strcmp(STO(mvm, -2)->u.string.string,
                                 STO(mvm, -1)->u.string.string) < 0);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_LE_INT:
            STI(mvm, -2) = (STI(mvm, -2) <= STI(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_LE_DOUBLE:
            STI(mvm, -2) = (STD(mvm, -2) <= STD(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_LE_STRING:
            STI_WRITE(mvm, -2,
                      strcmp(STO(mvm, -2)->u.string.string,
                                 STO(mvm, -1)->u.string.string) <= 0);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_NE_INT:
            STI(mvm, -2) = (STI(mvm, -2) != STI(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_NE_DOUBLE:
            STI(mvm, -2) = (STD(mvm, -2) != STD(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_NE_OBJECT:
            STI_WRITE(mvm, -2, STO(mvm, -2) != STO(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_NE_STRING:
            STI_WRITE(mvm, -2,
                      strcmp(STO(mvm, -2)->u.string.string,
                                 STO(mvm, -1)->u.string.string) != 0);
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_LOGICAL_AND:
            STI(mvm, -2) = (STI(mvm, -2) && STI(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_LOGICAL_OR:
            STI(mvm, -2) = (STI(mvm, -2) || STI(mvm, -1));
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_LOGICAL_NOT:
            STI(mvm, -1) = !STI(mvm, -1);
            pc++;
            break;
        case MVM_POP:
            mvm->stack.stack_pointer--;
            pc++;
            break;
        case MVM_DUPLICATE:
            mvm->stack.stack[mvm->stack.stack_pointer]
                = mvm->stack.stack[mvm->stack.stack_pointer-1];
            mvm->stack.stack_pointer++;
            pc++;
            break;
        case MVM_JUMP:
            pc = GET_2BYTE_INT(&code[pc+1]);
            break;
        case MVM_JUMP_IF_TRUE:
            if (STI(mvm, -1)) {
                pc = GET_2BYTE_INT(&code[pc+1]);
            } else {
                pc += 3;
            }
            mvm->stack.stack_pointer--;
            break;
        case MVM_JUMP_IF_FALSE:
            if (!STI(mvm, -1)) {
                pc = GET_2BYTE_INT(&code[pc+1]);
            } else {
                pc += 3;
            }
            mvm->stack.stack_pointer--;
            break;
        case MVM_PUSH_FUNCTION:
            STI_WRITE(mvm, 0, GET_2BYTE_INT(&code[pc+1]));
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        case MVM_INVOKE:
        {
            int func_idx = STI(mvm, -1);
            if (mvm->function[func_idx].kind == NATIVE_FUNCTION) {
                invoke_native_function(mvm, &mvm->function[func_idx],
                                       &mvm->stack.stack_pointer);
                pc++;
            } else {
                invoke_minic_function(mvm, &func, &mvm->function[func_idx],
                                       &code, &code_size, &pc,
                                       &mvm->stack.stack_pointer, &base,
                                       &exe);
            }
            break;
        }
        case MVM_RETURN:
            return_function(mvm, &func, &code, &code_size, &pc,
                            &mvm->stack.stack_pointer, &base,
                            &exe);
            break;
        case MVM_NEW_ARRAY:
        {
            int dim = code[pc+1];
            MVM_TypeSpecifier *type
                = &exe->type_specifier[GET_2BYTE_INT(&code[pc+2])];
            MVM_Object *array;

            restore_pc(mvm, exe, func, pc);
            array = create_array(mvm, dim, type);
            mvm->stack.stack_pointer -= dim;
            STO_WRITE(mvm, 0, array);
            mvm->stack.stack_pointer++;
            pc += 4;
            break;
        }
        case MVM_NEW_ARRAY_LITERAL_INT: /* FALLTHRU */
        {
            int size = GET_2BYTE_INT(&code[pc+1]);
            MVM_Object *array;

            restore_pc(mvm, exe, func, pc);
            array = create_array_literal_int(mvm, size);
            mvm->stack.stack_pointer -= size;
            STO_WRITE(mvm, 0, array);
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        }
        case MVM_NEW_ARRAY_LITERAL_DOUBLE: /* FALLTHRU */
        {
            int size = GET_2BYTE_INT(&code[pc+1]);
            MVM_Object *array;

            restore_pc(mvm, exe, func, pc);
            array = create_array_literal_double(mvm, size);
            mvm->stack.stack_pointer -= size;
            STO_WRITE(mvm, 0, array);
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        }
        case MVM_NEW_ARRAY_LITERAL_OBJECT: /* FALLTHRU */
        {
            int size = GET_2BYTE_INT(&code[pc+1]);
            MVM_Object *array;

            restore_pc(mvm, exe, func, pc);
            array = create_array_literal_object(mvm, size);
            mvm->stack.stack_pointer -= size;
            STO_WRITE(mvm, 0, array);
            mvm->stack.stack_pointer++;
            pc += 3;
            break;
        }
        default:
            break;
        }
        /* MEM_check_all_blocks(); */
    }

    return ret;
}

MVM_Value
MVM_execute(MVM_VirtualMachine *mvm)
{
    MVM_Value ret;

    mvm->current_executable = mvm->executable;
    mvm->current_function = NULL;
    mvm->pc = 0;
    expand_stack(mvm, mvm->executable->need_stack_size);
    execute(mvm, NULL, mvm->executable->code, mvm->executable->code_size);

    return ret;
}