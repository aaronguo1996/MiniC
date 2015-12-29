#include <string.h>
#include "../include/MEM.h"
#include "mvm_pri.h"

static void
check_array(MVM_Object *array, int index,
            MVM_Executable *exe, Function *func, int pc)
{
    if (array == NULL) {
		/*
        mvm_error(exe, func, pc, NULL_POINTER_ERR,
                  MESSAGE_ARGUMENT_END);
				  */
    }
    if (index < 0 || index >= array->u.array.size) {
		/*
        mvm_error(exe, func, pc, INDEX_OUT_OF_BOUNDS_ERR,
                  INT_MESSAGE_ARGUMENT, "index", index,
                  INT_MESSAGE_ARGUMENT, "size", array->u.array.size,
                  MESSAGE_ARGUMENT_END);
				  */
    }
}

int
MVM_array_get_int(MVM_VirtualMachine *mvm, MVM_Object *array, int index)
{
    check_array(array, index,
                mvm->current_executable, mvm->current_function, mvm->pc);

    return array->u.array.u.int_array[index];
}

double
MVM_array_get_double(MVM_VirtualMachine *mvm, MVM_Object *array, int index)
{
    check_array(array, index,
                mvm->current_executable, mvm->current_function, mvm->pc);


    return array->u.array.u.double_array[index];
}

MVM_Object *
MVM_array_get_object(MVM_VirtualMachine *mvm, MVM_Object *array, int index)
{
    check_array(array, index,
                mvm->current_executable, mvm->current_function, mvm->pc);

    return array->u.array.u.object[index];
}

void
MVM_array_set_int(MVM_VirtualMachine *mvm, MVM_Object *array, int index,
                  int value)
{
    check_array(array, index,
                mvm->current_executable, mvm->current_function, mvm->pc);

    array->u.array.u.int_array[index] = value;
}

void
MVM_array_set_double(MVM_VirtualMachine *mvm, MVM_Object *array, int index,
                     double value)
{
    check_array(array, index,
                mvm->current_executable, mvm->current_function, mvm->pc);

    array->u.array.u.double_array[index] = value;
}

void
MVM_array_set_object(MVM_VirtualMachine *mvm, MVM_Object *array, int index,
                     MVM_Object *value)
{
    check_array(array, index,
                mvm->current_executable, mvm->current_function, mvm->pc);

    array->u.array.u.object[index] = value;
}
