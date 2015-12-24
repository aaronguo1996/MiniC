#ifndef PUBLIC_MINIC_H_INCLUDED
#define PUBLIC_MINIC_H_INCLUDED
#include <stdio.h>
#include "MVM.h"

#define CODE_SIZE (0xFFFFFF-1)

typedef struct MINIC_Compiler_tag MINIC_Compiler;
extern char source_code[CODE_SIZE];

MINIC_Compiler *MINIC_create_compiler(void);
MVM_Executable *MINIC_compile(MINIC_Compiler *compiler, FILE *fp);
void MINIC_dispose_compiler(MINIC_Compiler *compiler);

#endif /* PUBLIC_MINIC_H_INCLUDED */