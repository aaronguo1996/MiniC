#ifndef PRIVATE_SHARE_H_INCLUDED
#define PRIVATE_SHARE_H_INCLUDED
#include <stdio.h>
#include "MVM_code.h"

typedef struct {
    char        *mnemonic;
    char        *parameter;
    int         stack_increment;
} OpcodeInfo;

/* util.c */
MVM_Boolean mvm_compare_package_name(char *p1, char *p2);
char *mvm_create_method_function_name(char *class_name, char *method_name);

/* disassemble.c */
int mvm_dump_instruction(FILE *fp, MVM_Byte *code, int index);
void mvm_disassemble(MVM_Executable *exe);

#endif  /* PRIVATE_SHARE_H_INCLUDED */