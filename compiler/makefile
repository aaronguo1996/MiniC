TARGET = compiler.o
CC=gcc
ENCODING_FLAG = -DSHIFT_JIS_SOURCE
CFLAGS = -c -g -Wall $(ENCODING_FLAG)
OBJS = \
  lex.yy.o\
  y.tab.o\
  interface.o\
  create.o\
  fix_tree.o\
  generate.o\
  string.o\
  util.o\
  error.o

INCLUDES = \
  -I../include

$(TARGET):$(OBJS)
	ld -r -o $@ $(OBJS)

clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h *~
y.tab.h : minic.y
	bison --yacc -dv minic.y
y.tab.c : minic.y
	bison --yacc -dv minic.y
lex.yy.c : minic.l minic.y y.tab.h
	flex minic.l
y.tab.o: y.tab.c minic.h ../include/MEM.h
	$(CC) -c -g $*.c $(INCLUDES)
lex.yy.o: lex.yy.c minic.h ../include/MEM.h
	$(CC) -c -g $*.c $(INCLUDES)
.c.o:
	$(CC) $(CFLAGS) $*.c $(INCLUDES)
############################################################
create.o: create.c ../include/MEM.h minic.h \
  ../include/MVM_code.h ../include/MVM.h
minic.tab.o: minic.tab.c minic.h ../include/MEM.h \
  ../include/MVM_code.h ../include/MVM.h \
  ../include/share.h ../include/node.h
error.o: error.c ../include/MEM.h minic.h \
  ../include/MVM_code.h ../include/MVM.h \
  ../include/share.h
fix_tree.o: fix_tree.c ../include/MEM.h minic.h \
  ../include/MVM_code.h ../include/MVM.h \
  ../include/share.h
generate.o: generate.c ../include/MEM.h minic.h \
  ../include/MVM_code.h ../include/MVM.h \
  ../include/share.h
interface.o: interface.c ../include/MEM.h minic.h \
  ../include/MVM_code.h ../include/MVM.h \
  ../include/share.h
string.o: string.c ../include/MEM.h minic.h \
  ../include/MVM_code.h ../include/MVM.h \
  ../include/share.h
util.o: util.c ../include/MEM.h minic.h \
  ../include/MVM_code.h ../include/MVM.h \
  ../include/share.h
