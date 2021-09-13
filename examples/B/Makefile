#
# Makefile for memkind example
#
PROGS = memkind
CFLAGS = -g -Wall -Werror -std=gnu99
LIBS = -lnuma

all: $(PROGS)

memkind: memkind.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS) -lmemkind

clean:
	$(RM) *.o a.out

clobber: clean
	$(RM) $(PROGS) memkind

.PHONY: all clean clobber
