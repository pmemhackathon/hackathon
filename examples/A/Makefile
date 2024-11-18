#
# Makefile for numa example
#
PROGS = numa
CFLAGS = -g -Wall -Werror -std=gnu99
LIBS = -lnuma

all: $(PROGS)

numa: numa.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

clean:
	$(RM) *.o a.out

clobber: clean
	$(RM) $(PROGS) numa

.PHONY: all clean clobber
