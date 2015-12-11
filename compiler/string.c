#include "minic.h"

#define STRING_ALLOC_SIZE       (256)

static char *st_string_literal_buffer = NULL;
static int st_string_literal_buffer_size = 0;
static int st_string_literal_buffer_alloc_size = 0;

void
minic_open_string_literal(void)
{
    st_string_literal_buffer_size = 0;
}

void
minic_add_string_literal(int letter)
{
    if (st_string_literal_buffer_size == st_string_literal_buffer_alloc_size) {
        st_string_literal_buffer_alloc_size += STRING_ALLOC_SIZE;
        st_string_literal_buffer
            = realloc(st_string_literal_buffer,
                         st_string_literal_buffer_alloc_size);
    }
    st_string_literal_buffer[st_string_literal_buffer_size] = letter;
    st_string_literal_buffer_size++;
}

void
minic_reset_string_literal_buffer(void)
{
    free(st_string_literal_buffer);
    st_string_literal_buffer = NULL;
    st_string_literal_buffer_size = 0;

    st_string_literal_buffer_alloc_size = 0;
}

char *
minic_close_string_literal(void)
{
    char *new_str;
    int new_str_len;

    minic_add_string_literal('\0');
    new_str = malloc(new_str_len+1);
    strcpy(new_str,st_string_literal_buffer);
    //mbstowcs(new_str, st_string_literal_buffer,strlen(new_str));
    new_str_len = strlen(new_str);
    if (new_str_len < 0) {
       //minic_compile_error(minic_get_current_compiler()->current_line_number,
         //                 BAD_MULTIBYTE_CHARACTER_ERR,
          //                MESSAGE_ARGUMENT_END);
   	printf("[%d]: %s",minic_get_current_compiler()->current_line_number, "bad close string");
	exit(-1); 
   }

    return new_str;
}

char *
minic_create_identifier(char *str)
{
    char *new_str;

    new_str = malloc(strlen(str) + 1);
    strcpy(new_str, str);
    return new_str;
}
