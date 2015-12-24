#ifndef MVM_PRI_H_INCLUDED
#define MVM_PRI_H_INCLUDED
#include "MVM_code.h"
#include "MVM_dev.h"
#include "share.h"

#define STACK_ALLOC_SIZE (4096)
#define HEAP_THRESHOLD_SIZE     (1024 * 256)
#define NULL_STRING "null"
#define TRUE_STRING "true"
#define FALSE_STRING "false"

#define NO_LINE_NUMBER_PC (-1)

#define MESSAGE_ARGUMENT_MAX    (256)
#define LINE_BUF_SIZE (1024)


#define GET_2BYTE_INT(p) (((p)[0] << 8) + (p)[1])
#define SET_2BYTE_INT(p, value) \
  (((p)[0] = (value) >> 8), ((p)[1] = value & 0xff))

typedef enum {
    INT_MESSAGE_ARGUMENT = 1,
    DOUBLE_MESSAGE_ARGUMENT,
    STRING_MESSAGE_ARGUMENT,
    CHARACTER_MESSAGE_ARGUMENT,
    POINTER_MESSAGE_ARGUMENT,
    MESSAGE_ARGUMENT_END
} MessageArgumentType;

typedef struct {
    char *format;
} ErrorDefinition;

typedef enum {
    BAD_MULTIBYTE_CHARACTER_ERR = 1,
    FUNCTION_NOT_FOUND_ERR,
    FUNCTION_MULTIPLE_DEFINE_ERR,
    INDEX_OUT_OF_BOUNDS_ERR,
    DIVISION_BY_ZERO_ERR,
    NULL_POINTER_ERR,
    RUNTIME_ERROR_COUNT_PLUS_1
} RuntimeError;

typedef struct {
    MVM_Char    *string;
} VString;

typedef enum {
    NATIVE_FUNCTION,
    DIKSAM_FUNCTION
} FunctionKind;

typedef struct {
    MVM_NativeFunctionProc *proc;
    int arg_count;
} NativeFunction;

typedef struct {
    MVM_Executable      *executable;
    int                 index;
} MinicFunction;

typedef struct {
    char                *name;
    FunctionKind        kind;
    union {
        NativeFunction native_f;
        MinicFunction minic_f;
    } u;
} Function;

typedef struct {
    Function    *caller;
    int         caller_address;
    int         base;
} CallInfo;

#define revalue_up_align(val)   ((val) ? (((val) - 1) / sizeof(MVM_Value) + 1)\
                                 : 0)
#define CALL_INFO_ALIGN_SIZE    (revalue_up_align(sizeof(CallInfo)))

typedef union {
    CallInfo    s;
    MVM_Value   u[CALL_INFO_ALIGN_SIZE];
} CallInfoUnion;

typedef struct {
    int         alloc_size;
    int         stack_pointer;
    MVM_Value   *stack;
    MVM_Boolean *pointer_flags;
} Stack;

typedef enum {
    STRING_OBJECT = 1,
    ARRAY_OBJECT,
    CLASS_OBJECT,
    OBJECT_TYPE_COUNT_PLUS_1
} ObjectType;

struct MVM_String_tag {
    MVM_Boolean is_literal;
    MVM_Char    *string;
};

typedef enum {
    INT_ARRAY = 1,
    DOUBLE_ARRAY,
    OBJECT_ARRAY
} ArrayType;

struct MVM_Array_tag {
    ArrayType   type;
    int         size;
    int         alloc_size;
    union {
        int             *int_array;
        double          *double_array;
        MVM_Object      **object;
    } u;
};

typedef struct {
    int         field_count;
    MVM_Value   *field;
} MVM_ClassObject;

struct MVM_Object_tag {
    ObjectType  type;
    unsigned int        marked:1;
    union {
        MVM_String      string;
        MVM_Array       array;
        MVM_ClassObject class_object;
    } u;
    struct MVM_Object_tag *prev;
    struct MVM_Object_tag *next;
};

typedef struct {
    int         current_heap_size;
    int         current_threshold;
    MVM_Object  *header;
} Heap;

typedef struct {
    int         variable_count;
    MVM_Value   *variable;
} Static;

struct MVM_VirtualMachine_tag {
    Stack       stack;
    Heap        heap;
    Static      static_v;
    MVM_Executable      *current_executable;
    Function    *current_function;
    int         pc;
    Function    *function;
    int         function_count;
    MVM_Executable      *executable;
};

/* heap.c */
MVM_Object *
mvm_literal_to_mvm_string_i(MVM_VirtualMachine *inter, MVM_Char *str);
MVM_Object *
mvm_create_mvm_string_i(MVM_VirtualMachine *mvm, MVM_Char *str);
MVM_Object *mvm_create_array_int_i(MVM_VirtualMachine *mvm, int size);
MVM_Object *mvm_create_array_double_i(MVM_VirtualMachine *mvm, int size);
MVM_Object *mvm_create_array_object_i(MVM_VirtualMachine *mvm, int size);
void mvm_garbage_collect(MVM_VirtualMachine *mvm);
/* native.c */
void mvm_add_native_functions(MVM_VirtualMachine *mvm);
/* util.c */
void mvm_vstr_clear(VString *v);
void mvm_vstr_append_string(VString *v, MVM_Char *str);
void mvm_vstr_append_character(VString *v, MVM_Char ch);
/* error.c */
void mvm_error(MVM_Executable *exe, Function *func,
               int pc, RuntimeError id, ...);

#endif /* MVM_PRI_H_INCLUDED */
