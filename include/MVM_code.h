#ifndef PUBLIC_MVM_CODE_H_INCLUDED
#define PUBLIC_MVM_CODE_H_INCLUDED
#include <stdio.h>
#include <wchar.h>
#include "MVM.h"

typedef enum {
    MVM_VOID_TYPE,
    MVM_BOOLEAN_TYPE,
    MVM_INTEGER_TYPE,
    MVM_DECIMAL_TYPE,
    MVM_STRING_TYPE,
    MVM_CLASS_TYPE,
    MVM_NULL_TYPE,
    MVM_BASE_TYPE
} MVM_BasicType;

typedef struct MVM_TypeSpecifier_tag MVM_TypeSpecifier;

typedef struct {
    char                *name;
    MVM_TypeSpecifier   *type;
} MVM_LocalVariable;

typedef enum {
    MVM_FUNCTION_DERIVE,
    MVM_ARRAY_DERIVE
} MVM_DeriveTag;

typedef struct {
    int                 parameter_count;
    MVM_LocalVariable   *parameter;
} MVM_FunctionDerive;

typedef struct {
    int dummy; /* make compiler happy */
} MVM_ArrayDerive;

typedef struct MVM_TypeDerive_tag {
    MVM_DeriveTag       tag;
    union {
        MVM_FunctionDerive      function_d;
    } u;
} MVM_TypeDerive;

struct MVM_TypeSpecifier_tag {
    MVM_BasicType       basic_type;
    int                 class_index;
    int                 derive_count;
    MVM_TypeDerive      *derive;
};

typedef char MVM_Char;
typedef unsigned char MVM_Byte;

typedef enum {
    MVM_PUSH_INT_1BYTE = 1,
    MVM_PUSH_INT_2BYTE,
    MVM_PUSH_INT,
    MVM_PUSH_DOUBLE_0,
    MVM_PUSH_DOUBLE_1,
    MVM_PUSH_DOUBLE,
    MVM_PUSH_STRING,
    MVM_PUSH_NULL,
    /**********/
    MVM_PUSH_STACK_INT,
    MVM_PUSH_STACK_DOUBLE,
    MVM_PUSH_STACK_OBJECT,
    MVM_POP_STACK_INT,
    MVM_POP_STACK_DOUBLE,
    MVM_POP_STACK_OBJECT,
    /**********/
    MVM_PUSH_STATIC_INT,
    MVM_PUSH_STATIC_DOUBLE,
    MVM_PUSH_STATIC_OBJECT,
    MVM_POP_STATIC_INT,
    MVM_POP_STATIC_DOUBLE,
    MVM_POP_STATIC_OBJECT,
    /**********/
    MVM_PUSH_ARRAY_INT,
    MVM_PUSH_ARRAY_DOUBLE,
    MVM_PUSH_ARRAY_OBJECT,
    MVM_POP_ARRAY_INT,
    MVM_POP_ARRAY_DOUBLE,
    MVM_POP_ARRAY_OBJECT,
    /**********/
    MVM_PUSH_FIELD_INT,
    MVM_PUSH_FIELD_DOUBLE,
    MVM_PUSH_FIELD_OBJECT,
    MVM_POP_FIELD_INT,
    MVM_POP_FIELD_DOUBLE,
    MVM_POP_FIELD_OBJECT,
    /**********/
    MVM_ADD_INT,
    MVM_ADD_DOUBLE,
    MVM_ADD_STRING,
    MVM_SUB_INT,
    MVM_SUB_DOUBLE,
    MVM_MUL_INT,
    MVM_MUL_DOUBLE,
    MVM_DIV_INT,
    MVM_DIV_DOUBLE,
    MVM_MOD_INT,
    MVM_MOD_DOUBLE,
    MVM_MINUS_INT,
    MVM_MINUS_DOUBLE,
    MVM_INCREMENT,
    MVM_DECREMENT,
    MVM_CAST_INT_TO_DOUBLE,
    MVM_CAST_DOUBLE_TO_INT,
    MVM_CAST_BOOLEAN_TO_STRING,
    MVM_CAST_INT_TO_STRING,
    MVM_CAST_DOUBLE_TO_STRING,
    MVM_UP_CAST,
    MVM_DOWN_CAST,
    MVM_EQ_INT,
    MVM_EQ_DOUBLE,
    MVM_EQ_OBJECT,
    MVM_EQ_STRING,
    MVM_GT_INT,
    MVM_GT_DOUBLE,
    MVM_GT_STRING,
    MVM_GE_INT,
    MVM_GE_DOUBLE,
    MVM_GE_STRING,
    MVM_LT_INT,
    MVM_LT_DOUBLE,
    MVM_LT_STRING,
    MVM_LE_INT,
    MVM_LE_DOUBLE,
    MVM_LE_STRING,
    MVM_NE_INT,
    MVM_NE_DOUBLE,
    MVM_NE_OBJECT,
    MVM_NE_STRING,
    MVM_LOGICAL_AND,
    MVM_LOGICAL_OR,
    MVM_LOGICAL_NOT,
    MVM_POP,
    MVM_DUPLICATE,
    MVM_DUPLICATE_OFFSET,
    MVM_JUMP,
    MVM_JUMP_IF_TRUE,
    MVM_JUMP_IF_FALSE,
    /**********/
    MVM_PUSH_FUNCTION,
    MVM_PUSH_METHOD,
    MVM_INVOKE,
    MVM_RETURN,
    /**********/
    MVM_NEW,
    MVM_NEW_ARRAY,
    MVM_NEW_ARRAY_LITERAL_INT,
    MVM_NEW_ARRAY_LITERAL_DOUBLE,
    MVM_NEW_ARRAY_LITERAL_OBJECT,
    MVM_SUPER,
    MVM_INSTANCEOF
} MVM_Opcode;

typedef enum {
    MVM_CONSTANT_INT,
    MVM_CONSTANT_DOUBLE,
    MVM_CONSTANT_STRING
} MVM_ConstantPoolTag;

typedef struct {
    MVM_ConstantPoolTag tag;
    union {
        int     c_integer;
        double  c_decimal;
        char    *c_string;
    } u;
} MVM_ConstantPool;

typedef struct {
    char                *name;
    MVM_TypeSpecifier   *type;
} MVM_Variable;

typedef struct {
    int line_number;
    int start_pc;
    int pc_count;
} MVM_LineNumber;

typedef struct {
    MVM_TypeSpecifier   *type;
    char                *name;
    int                 parameter_count;
    MVM_LocalVariable   *parameter;
    MVM_Boolean         is_implemented;
    MVM_Boolean         is_method;
    int                 local_variable_count;
    MVM_LocalVariable   *local_variable;
    int                 code_size;
    MVM_Byte            *code;
    int                 line_number_size;
    MVM_LineNumber      *line_number;
    int                 need_stack_size;
} MVM_Function;

typedef enum {
    MVM_FILE_ACCESS,
    MVM_PUBLIC_ACCESS,
    MVM_PRIVATE_ACCESS
} MVM_AccessModifier;

typedef struct {
    //MVM_AccessModifier  access_modifier;
    char                *name;
    MVM_TypeSpecifier   *type;
} MVM_Field;

typedef struct {
    MVM_AccessModifier  access_modifier;
    MVM_Boolean         is_abstract;
    MVM_Boolean         is_virtual;
    MVM_Boolean         is_override;
    char                *name;
} MVM_Method;

typedef enum {
    MVM_CLASS_DEFINITION,
    MVM_INTERFACE_DEFINITION
} MVM_ClassOrInterface;

typedef struct {
    char *package_name;
    char *name;
} MVM_ClassIdentifier;

typedef struct {
    //MVM_Boolean                 is_abstract;
    //MVM_AccessModifier          access_modifier;
    //MVM_ClassOrInterface        class_or_interface;
    char                        *package_name;
    char                        *name;
    //MVM_Boolean                 is_implemented;
    //MVM_ClassIdentifier         *super_class;
    //int                         interface_count;
    //MVM_ClassIdentifier         *interface_;
    int                         field_count;
    MVM_Field                   *field;
    //int                         method_count;
    //MVM_Method                  *method;
} MVM_Class;


struct MVM_Executable_tag {
    char                *package_name;
    MVM_Boolean         is_required;
    char                *path;
    int                 constant_pool_count;
    MVM_ConstantPool    *constant_pool;
    int                 global_variable_count;
    MVM_Variable        *global_variable;
    int                 function_count;
    MVM_Function        *function;
    int                 type_specifier_count;
    MVM_TypeSpecifier   *type_specifier;
    int                 code_size;
    MVM_Byte            *code;
    int                 class_count;
    MVM_Class           *class_definition;
    int                 line_number_size;
    MVM_LineNumber      *line_number;
    int                 need_stack_size;
};

typedef struct MVM_ExecutableItem_tag {
    MVM_Executable *executable;
    struct MVM_ExecutableItem_tag *next;
} MVM_ExecutableItem;

struct MVM_ExecutableList_tag {
    MVM_Executable      *top_level;
    MVM_ExecutableItem  *list;
};

#endif /* PUBLIC_MVM_CODE_H_INCLUDED */
