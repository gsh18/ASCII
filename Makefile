##***************************************************##
##  GIANFRANCO DE SOUZA HARRES      - GRR: 20180103  ##
##  VINICIUS AUGUSTO DILAY DE PAULA - GRR: 20182597  ##
##***************************************************##
##                    MAKEFILE                       ##
##***************************************************##
##         Make para o ASCII - BOUDERDASH            ##
##***************************************************##


DEPS = defs.h

CC = gcc

CFLAGS = -Wall

BIB = -lncurses

all: daciolodash

daciolodash: main.o logic.o inic.o anim.o close.o
	$(CC) -o dacioloDash main.o logic.o inic.o anim.o close.o $(BIB)

logic.c: logic.h
inic.c:  inic.h
anim.c:  anim.h
close.c: close.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *~ *\# \#* *.o

purge: clean
	-rm -f dacioloDash
