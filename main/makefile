TARGET = minic
CC=gcc
OBJS = \
  ../compiler/compiler.o\
  ../share/share.o\
  ../memory/mem.o\
  ../mvm/mvm.o\
  ./main.o
  
CFLAGS = -c -g -Wall -Wswitch-enum -DDEBUG -DDKM_WINDOWS

INCLUDES = \
  -I/usr/local/include\
  -I../include
  
$(TARGET):$(OBJS)
	cd ../compiler; $(MAKE)
	cd ../share; $(MAKE);
	cd ../memory; $(MAKE);
	cd ../mvm; $(MAKE);
	$(CC) $(OBJS) -o $@ -lm

clean:
	rm lex back.php disassemble error.info -f *.o *~
.c.o:
	$(CC) $(CFLAGS) $*.c $(INCLUDES)
../memory/mem.o:
	cd ../memory; $(MAKE);
../share/share.o:
	cd ../share; $(MAKE);
../compiler/compiler.o:
	cd ../compiler; $(MAKE);
../mvm/mvm.o:
	cd ../mvm; $(MAKE);
###########################################################
main.o: main.c ../include/MC.h ../include/MVM_code.h ../include/MVM.h \
   ../include/MEM.h ../include/node.h