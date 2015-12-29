#include "../include/MEM.h"
#include "mvm_pri.h"

static MVM_Value
nv_print_proc(MVM_VirtualMachine *mvm,
              int arg_count, MVM_Value *args)
{
    MVM_Value ret;
    MVM_Char *str;

    ret.int_value = 0;

    if (args[0].object == NULL) {
        str = NULL_STRING;
    } else {
        str = args[0].object->u.string.string;
    }
    fprintf(stdout, "%s", str);
    fflush(stdout);

    return ret;
}

static MVM_Value
nv_print_integer_proc(MVM_VirtualMachine *mvm,
              int arg_count, MVM_Value *args)
{
    MVM_Value ret;
    int i = args[0].int_value;
    ret.int_value = 0;

    fprintf(stdout, "%d", i);
    fflush(stdout);

    return ret;
}

static MVM_Value
nv_print_decimal_proc(MVM_VirtualMachine *mvm,
              int arg_count, MVM_Value *args)
{
    MVM_Value ret;
    double i = args[0].double_value;
    ret.double_value = 0;

    fprintf(stdout, "%f", i);
    fflush(stdout);

    return ret;
}


void
mvm_add_native_functions(MVM_VirtualMachine *mvm)
{
    MVM_add_native_function(mvm, "print", nv_print_proc, 1);
	MVM_add_native_function(mvm, "printInteger", nv_print_integer_proc, 1);
    MVM_add_native_function(mvm, "printDecimal", nv_print_decimal_proc, 1);
}
