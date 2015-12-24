#include <stdio.h>
#include <string.h>
#include "MEM.h"
#include "minic.h"

static MINIC_Compiler *st_current_compiler;

MINIC_Compiler *
minic_get_current_compiler(void)
{
    return st_current_compiler;
}

void minic_set_current_compiler(MINIC_Compiler *compiler)
{
    st_current_compiler = compiler;
}

TypeSpecifier *
minic_alloc_type_specifier(MVM_BasicType type)
{
    TypeSpecifier *ts = malloc(sizeof(TypeSpecifier));

    ts->basic_type = type;
    ts->derive = NULL;

    return ts;
}

TypeDerive *
minic_alloc_type_derive(DeriveTag derive_tag)
{
    TypeDerive *td = malloc(sizeof(TypeDerive));
    td->tag = derive_tag;
    td->next= NULL;

    return td;
}

FunctionDefinition *
minic_search_function(char *name)
{
    MINIC_Compiler *compiler;
    FunctionDefinition *pos;

    compiler = minic_get_current_compiler();

    for(pos = compiler->function_list; pos ; pos = pos->next){
    	if(!strcmp(pos->name,name))
    	    break;
    }
    return pos;
}

Declaration *
minic_search_declaration(char *identifier, Block *block)
{
    Block *b_pos;
    DeclarationList *d_pos;
    MINIC_Compiler *compiler;

    for(b_pos = block; b_pos; b_pos = b_pos->outer_block){
	for(d_pos = b_pos->declaration_list; d_pos; d_pos = d_pos->next){
	    if(!strcmp(identifier, d_pos->declaration->name)){
		return d_pos->declaration;
	    }
	}
    }

    compiler = minic_get_current_compiler();

    for(d_pos = compiler->declaration_list; d_pos; d_pos = d_pos->next){
	if(!strcmp(identifier, d_pos->declaration->name)){
	    return d_pos->declaration;
	}
    }

    return NULL;
}

ClassDefinition *
minic_search_class(char *identifier)
{
    MINIC_Compiler *compiler;
    ClassDefinition *class_def;

    compiler = minic_get_current_compiler();
    for (class_def = compiler->class_definition_list;
         class_def; class_def = class_def->next) {
        if (!strcmp(class_def->name, identifier)) {
            return class_def;
        }
    }

    return NULL;
}

MemberDeclaration *
minic_search_member(ClassDefinition *class_def, char *member_name)
{
    MemberDeclaration *member;
    //ExtendsList *extends_p;

    for(member = class_def->member; member; member = member->next){
	if(!strcmp(member->name,member_name))
	    break;
    }
    if(member) return member;
    return NULL;
}


void
minic_vstr_clear(VString *v)
{
    v->string = NULL;
}
/*
static int
my_strlen(char *str)
{
     if(str == NULL) return 0;
     else	     return minic_wcslen(str);
}

void
minic_vstr_append_string(VString *v, char *str)
{
    int new_size;
    int old_len;

    old_len = strlen(v->string);
    new_size = sizeof(char) * (old_len+strlen(str)+1);
}
*/

char *
minic_get_basic_type_name(MVM_BasicType type)
{
    switch (type){
    case MVM_BOOLEAN_TYPE:
	return "boolean";
	break;
    case MVM_INTEGER_TYPE:
	return "integer";
	break;
    case MVM_DECIMAL_TYPE:
	return "decimal";
	break;
    case MVM_STRING_TYPE:
	return "string";
	break;
    default:
	//assert(0,("bad case. type..%d\n",type);
	break;
    }
    return NULL;
}

char *
minic_expression_to_string(Expression *expr)
{
    char *wc_buf = (char *)malloc(LINE_BUF_SIZE);

    if(expr->kind == BOOLEAN_EXPRESSION) {
	if(expr->u.boolean_value){
	    strcpy(wc_buf,"true");
	}else{
	    strcpy(wc_buf,"false");
	}
    }else if(expr->kind == INTEGER_EXPRESSION){
	sprintf(wc_buf, "%d", expr->u.integer_value);
    }else if(expr->kind == DECIMAL_EXPRESSION){
	sprintf(wc_buf, "%f", expr->u.decimal_value);
    }else if(expr->kind == STRING_EXPRESSION){
	return expr->u.string_value;
    }else{
	return NULL;
    }
    return wc_buf;
}

char *
minic_package_name_to_string(PackageName *src)
{
    int len = 0;
    PackageName *pos;
    char *dest;

    if (src == NULL) {
        return NULL;
    }
    for (pos = src; pos; pos = pos->next) {
        len += strlen(pos->name) + 1;
    }


    dest = (char *)MEM_malloc(len);
    dest[0] = '\0';
    for (pos = src; pos; pos = pos->next) {
        strcat(dest, pos->name);
        if (pos->next) {
            strcat(dest, ".");
        }
    }

    return dest;
}