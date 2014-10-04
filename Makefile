CC=gcc
f=0
CFLAGS = -Wall -MMD -g -std=c99
OBJECTS = heap.o test.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = heap

${EXEC}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean: 
	rm -f ${EXEC} *.o *.d
.PHONY: clean
