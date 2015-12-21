#include <stdlib.h>
#include <string.h>
#include "MEM.h"
#include "share.h"

/*
MVM_Boolean
mvm_compare_package_name(char *p1, char *p2)
{
    return mvm_compare_string(p1, p2);
}
*/

char *
mvm_create_method_function_name(char *class_name, char *method_name)
{
    int class_name_len;
    int method_name_len;
    char *ret;

    class_name_len = strlen(class_name);
    method_name_len = strlen(method_name);
    ret = MEM_malloc(class_name_len + method_name_len + 2);
    sprintf(ret, "%s#%s", class_name, method_name);

    return ret;
}