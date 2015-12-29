#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "../include/MC.h"
#include "../include/MVM.h"
#include "../include/node.h"
#include "../include/share.h"

FILE *treefp;
int currNum = 1;

void write_header()
{
	char buf[] = "<?php\
		header('Content-type:text/html;charset:utf-8');\
	function returnArray($result){\
			$newResult = array();\
		if (!empty($result)){\
			foreach($result as $k=>$v) {\
				$arrTep = $v;\
				$arrTep['childrens'] = array();\
				if (0 == $v['pid']){\
					$newResult[] = $arrTep;\
					continue;\
				}\
				if (0 != $v['pid']){\
					if (false === updateArray($newResult, $arrTep)){\
						$arrTep = array('id' => $arrTep['id'], 'pid' =>0, 'name' =>$arrTep['name'], 'childrens' =>array($arrTep));\
						$newResult[] = $arrTep;\
					}\
				}\
			}\
		}\
		echo json_encode($newResult);\
	}\
	function updateArray(&$newResult, $arrTep){\
		if (!empty($newResult)){\
			foreach($newResult as $k => $v) {\
				if ($v['id'] == $arrTep['pid']){\
					$newResult[$k]['childrens'][] = $arrTep;\
					return true;\
				}elseif(!empty($v['childrens'])){\
					if (true === updateArray($newResult[$k]['childrens'], $arrTep)){\
						return true;\
					}\
				}\
			}\
		}\
		return false;\
	}\
	$result = Array\
		(";
	fwrite(buf, strlen(buf), 1, treefp);
}

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
    char buf[] = ");\nif('org_select' == $_POST['action']){\n \
                 returnArray($result);\n}\n?>";
    fwrite(buf,strlen(buf),1,treefp);
}

int main(int argc, char **argv)
{

    MINIC_Compiler *compiler;
	MVM_Executable *exe;
	MVM_VirtualMachine *mvm;
    FILE *fp;
    FILE *fp_disassemble;
    FILE *fp_lex;
	error_detected = 0;

    if (argc < 2) {
	    fprintf(stderr,"usage:%s filename arg1, arg2, ...\n",argv[0]);
	    exit(1);
    }
    
    fp = fopen(argv[1],"r");
    if (fp == NULL) {
	    fprintf(stderr, "%s not found.\n",argv[1]);
	    exit(1);
    }

    setlocale(LC_CTYPE, "");
    compiler = MINIC_create_compiler();
    exe = MINIC_compile(compiler, fp);
    fp_lex = fopen("lex","w+");
    source_code[strlen(source_code)-1] = '\0';
    fwrite(source_code,strlen(source_code),1,fp_lex);
    treefp = fopen("back.php","w+");
	write_header();
    update_index(tree);
    fix_file();

    //mvm_disassemble(exe);
	if (!error_detected){
		mvm = MVM_create_virtual_machine();
		MVM_add_executable(mvm, exe);
		MVM_execute(mvm);
		fp_disassemble = fopen("disassemble", "w+");
		mvm_disassemble_to_file(exe, fp_disassemble);
	}
    return 0;
}
