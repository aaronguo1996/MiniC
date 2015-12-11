#include "minic.h"
#include "y.tab.h"
#include <string.h>

MINIC_Compiler *
MINIC_create_compiler(void)
{
	//MEM_Storage storage;
	MINIC_Compiler *compiler;

	//storage = MEM_open_storage(0);
	//compiler = MEM_storage_malloc(storage,
	//			      sizeof(struct MINIC_Compiler_tag));
	compiler = (MINIC_Compiler *)malloc(sizeof(struct MINIC_Compiler_tag));
	compiler->function_list = NULL;
	compiler->function_count = 0;
	compiler->declaration_list = NULL;
	compiler->statement_list = NULL;
	compiler->current_block = NULL;
	compiler->current_line_number = 1;
	compiler->input_mode = MINIC_FILE_INPUT_MODE;
#ifdef EUC_SOURCE
	compiler->source_encoding = EUC_ENCODING;
#else
#ifdef SHIFT_JIS_SOURCE
	compiler->source_encoding = SHIFT_JIS_ENCODING;
#else
#ifdef UTF_8_SOURCE
	compiler->source_encoding = UTF_8_ENCODING;
#endif
#endif
#endif
	minic_set_current_compiler(compiler);
	return compiler;
}

void
do_compile(MINIC_Compiler *compiler, FILE *fp)
{
	extern int yyparse(void);
	extern FILE *yyin;

	compiler->current_line_number = 1;
	compiler->input_mode = MINIC_FILE_INPUT_MODE;
        yyin = fp;
	minic_set_current_compiler(compiler);
	if(yyparse()){
		fprintf(stderr,"Error!\n");
		exit(1);
	}
}
/*
void
MINIC_dispose_compiler(MINIC_Compiler *compiler)
{
	FunctionDefinition *fd_pos;
	for(fd_pos = compiler->function_list; fd_pos;fd_pos = fd_pos->next){
		MEM_free(fd_pos->local_variable);
	}
	MEM_dispose_storage(compiler->compile_storage);
}*/

