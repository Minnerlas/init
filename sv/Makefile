CC = cproc
CFLAGS = -I../include
IZLAZ = sv

all:
	${CC} ${CFLAGS} *.c -o ../build/${IZLAZ}

run: all
	../build/${BUILD}

dbg:
	gcc -g ${CFLAGS}  *.c -o ../build/${IZLAZ}

clean:
	rm -rvf ../build/*
