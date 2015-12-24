#ifndef MVM_DEV_H_INCLUDED
#define MVM_DEV_H_INCLUDED
#include "MVM.h"

typedef struct MVM_Array_tag MVM_Array;

typedef MVM_Value MVM_NativeFunctionProc(MVM_VirtualMachine *dvm,
                                         int arg_count, MVM_Value *args);
/* execute.c */
void MVM_add_native_function(MVM_VirtualMachine *dvm, char *func_name,
                             MVM_NativeFunctionProc *proc, int arg_count);
/* nativeif.c */
int MVM_array_get_int(MVM_VirtualMachine *dvm, MVM_Object *array, int index);
double MVM_array_get_double(MVM_VirtualMachine *dvm, MVM_Object *array,
                            int index);
MVM_Object *
MVM_array_get_object(MVM_VirtualMachine *dvm, MVM_Object *array, int index);
void
MVM_array_set_int(MVM_VirtualMachine *dvm, MVM_Object *array, int index,
                  int value);
void
MVM_array_set_double(MVM_VirtualMachine *dvm, MVM_Object *array, int index,
                     double value);
void
MVM_array_set_object(MVM_VirtualMachine *dvm, MVM_Object *array, int index,
                     MVM_Object *value);


/* heap.c */
MVM_Object *MVM_create_array_int(MVM_VirtualMachine *dvm, int size);
MVM_Object *MVM_create_array_double(MVM_VirtualMachine *dvm, int size);
MVM_Object *MVM_create_array_object(MVM_VirtualMachine *dvm, int size);

#endif /* MVM_DEV_H_INCLUDED */
