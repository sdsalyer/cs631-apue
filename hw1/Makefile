# A slightly better makefile

PROG= bbcp
OBJS= bbcp.o
CFLAGS= -Wall -g

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

all: ${PROG}

depend:
	mkdep -- ${CFLAGS} *.c

${PROG}: ${OBJS}
	@echo $@ depends on $?
	${CC} ${OBJS} -o ${PROG} ${LDFLAGS}

clean:
	rm -f ${PROG} ${OBJS}
