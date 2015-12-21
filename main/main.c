#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "MC.h"
#include "MVM.h"
//#include "node.h"
#include "share.h"

FILE *treefp;
int currNum = 1;
/*
void update_index(TreeNode *root)
{
    if(root == NULL) return;
    root->id = currNum;
    char buf[1024];
    sprintf(buf,"%d => Array\n('id' => %d,\n'pid' => %d,\n \
	     'name' => \"%s\"\n),\n",currNum,root->id,root->pid,root->name);
    fwrite(buf,strlen(buf),1,treefp);
    currNum++;
    if(root->child){
	TreeNode *tmp = root->child;
	while(tmp){
	    tmp->pid = root->id;
	    update_index(tmp);
	    //currNum++;
	    tmp = tmp->sibling;
	}
    }
}

void fix_file()
{
    lseek(treefp,0,SEEK_END);
    char buf[] = ");\nif('org_select' == $_POST['action']){\n \
                 returnArray($result);\n}\n?>";
    fwrite(buf,strlen(buf),1,treefp);
}
*/
int main(int argc, char **argv)
{

    MINIC_Compiler *compiler;
	MVM_Executable *exe;
    FILE *fp;

    if (argc < 2) {
	    fprintf(stderr,"usage:%s filename arg1, arg2, ...\n",argv[0]);
	    exit(1);
    }
    //printf("    \n");
    fp = fopen(argv[1],"r");
    if (fp == NULL) {
	    fprintf(stderr, "%s not found.\n",argv[1]);
	    exit(1);
    }

    setlocale(LC_CTYPE, "");
    compiler = MINIC_create_compiler();
    exe = MINIC_compile(compiler, fp);
    mvm_disassemble(exe);
	/*  Generate a graph
    treefp = fopen("back.php","at");
    update_index(tree);
    fix_file();
	*/
	
	
    return 0;
}
