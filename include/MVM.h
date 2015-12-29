#ifndef PUBLIC_MVM_H_INCLUDED
#define PUBLIC_MVM_H_INCLUDED

typedef struct MVM_Executable_tag MVM_Executable;
typedef struct MVM_VirtualMachine_tag MVM_VirtualMachine;

typedef struct MVM_Object_tag MVM_Object;
typedef struct MVM_String_tag MVM_String;

typedef enum {
    MVM_FALSE = 0,
    MVM_TRUE = 1
} MVM_Boolean;
/*
typedef struct MVM_VTable_tag MVM_VTable;

typedef struct {
    MVM_VTable *v_table;
    MVM_Object *data;
} MVM_ObjectRef;
*/
typedef union {
    int                 int_value;
    double              double_value;
    MVM_Object          *object;
} MVM_Value;

MVM_VirtualMachine *MVM_create_virtual_machine(void);
void MVM_add_executable(MVM_VirtualMachine *mvm, MVM_Executable *exe);
void MVM_execute(MVM_VirtualMachine *mvm);//MVM_Value
//void MVM_dispose_executable_list(MVM_ExecutableList *list);
void MVM_dispose_virtual_machine(MVM_VirtualMachine *mvm);
void mvm_disassemble(MVM_Executable *exe);
void mvm_disassemble_to_file(MVM_Executable *exe,FILE *fp);

#endif /* PUBLIC_MVM_CODE_H_INCLUDED */
