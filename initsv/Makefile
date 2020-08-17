CC = tcc
CFLAGS = -I../include
GCCFLAGS =  -pthread
CCFLAGS =  -lpthread
IZLAZ = initsv

all:
	${CC} ${CFLAGS} ${CCFLAGS} *.c -o ../build/${IZLAZ}
 
run: all
	../build/${BUILD}

dbg:
	gcc -g ${CFLAGS} ${GCCFLAGS} *.c -o ../build/${IZLAZ}

clean:
	rm -rvf ../build/*
