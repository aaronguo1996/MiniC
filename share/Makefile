TARGET = share.o
CC=gcc
CFLAGS = -c -g -I../include -Wall -Wswitch-enum
OBJS = opcode.o \
    disassemble.o \
	util.o

$(TARGET):$(OBJS)
	ld -r -o $@ $(OBJS)
.c.o:
	$(CC) $(CFLAGS) -I../include $*.c
disassemble.o: disassemble.c ../include/share.h \
  ../include/MVM_code.h ../include/MVM.h
opcode.o: opcode.c ../include/share.h ../include/MVM_code.h \
  ../include/MVM.h
util.o: util.c ../include/MEM.h ../include/share.h \
  ../include/MVM_code.h ../include/MVM.h
clean:
	rm -f *.o *~