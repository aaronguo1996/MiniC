TARGET = mvm.o
CC=gcc
CFLAGS = -c -g -Wall -Wswitch-enum -DDEBUG
OBJS = execute.o \
  heap.o \
  native.o \
  nativeif.o
  
$(TARGET):$(OBJS)
	ld -r -o $@ $(OBJS)
.c.o:
	$(CC) $(CFLAGS) -I../include $*.c
execute.o: execute.c ../include/MEM.h mvm_pri.h \
 ../include/MVM_code.h ../include/MVM.h ../include/MVM_dev.h \
 ../include/share.h
heap.o: heap.c ../include/MEM.h mvm_pri.h \
 ../include/MVM_code.h ../include/MVM.h ../include/MVM_dev.h \
 ../include/share.h
native.o: native.c ../include/MEM.h mvm_pri.h \
 ../include/MVM_code.h ../include/MVM.h ../include/MVM_dev.h \
 ../include/share.h
nativeif.o: nativeif.c ../include/MEM.h mvm_pri.h \
 ../include/MVM_code.h ../include/MVM.h ../include/MVM_dev.h \
 ../include/share.h

clean:
	rm -f *.o *~