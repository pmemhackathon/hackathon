#
# Makefile for basic example
#
PROGS = basic
CFLAGS = -g -Wall -Werror -std=gnu99
LIBS = -lumf -ltbbmalloc

all: $(PROGS)

basic: basic.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

clean:
	$(RM) *.o a.out

clobber: clean
	$(RM) $(PROGS) basic 

.PHONY: all clean clobber
